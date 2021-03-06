#include <cstdlib>
#include <cstring>
#include <ctime>
#include <sys/time.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <vector>
#include <math.h>
#include "matrix4.h"

#define		GLX_GLXEXT_PROTOTYPES
#include <GL/glxext.h>

// Define se a janela deve ser fullscreen
#define		Full

// Para o algoritmo de geração de terreno o lado do quadrado tem que ser potência de 2 mais um
#define		Side	129//513
#define		Size	0.0625

#define		Smooth		0.9
#define		Roughness	0.5
#define		Variation	5 * Size * pow(Side, Roughness)

#define		Walk	4
#define		Run		9

using std::vector;
using std::cout;
using std::endl;

typedef struct {
	GLfloat x;
	GLfloat y;
	GLfloat z;
} Position;

typedef struct {
	GLfloat r;
	GLfloat g;
	GLfloat b;
} Color;

static const char *szIdentityShaderVP = "#version 420 core\n"
										"in vec4 vVertex;"
										"in vec4 vColor;"
										"flat out vec4 fColor;"
										"smooth out float blend;"//
										"uniform mat4 pmat;"
										"uniform mat4 mvmat;"
										"void main() {"
										"	gl_Position = mvmat * vVertex;"
										"	fColor = vColor;"
										"	blend = clamp((200 - length(gl_Position)) / (200 - 1), 0.0, 1.0);"//
										"	gl_Position = pmat * gl_Position;"
										"}";
									
static const char *szIdentityShaderFP = "#version 420 core\n"
										"out vec4 fragColor;"
										"flat in vec4 fColor;"
										"smooth in float blend;"//
										"void main(void) {"
										"	fragColor = mix(vec4(0.0, 0.0, 1.0, 1.0), fColor, blend);"//
										"	fragColor = fColor;"
										"}";

Display					*dpy;
Window					root;
XVisualInfo				*vi;
Colormap				cmap;
XSetWindowAttributes	swa;
Window					win;
GLXContext				glc;
XWindowAttributes		gwa;
XEvent					xev;
GLXFBConfig				fbc;
Atom					delete_event;


GLint att[] = {
	GLX_X_RENDERABLE,	True,
	GLX_RENDER_TYPE,	GLX_RGBA_BIT,
	GLX_DRAWABLE_TYPE,	GLX_WINDOW_BIT,
	GLX_X_VISUAL_TYPE,	GLX_TRUE_COLOR,
	GLX_RED_SIZE,		8,
	GLX_GREEN_SIZE,		8,
	GLX_BLUE_SIZE,		8,
	GLX_DEPTH_SIZE,		24,
	GLX_STENCIL_SIZE,	8,
	GLX_DOUBLEBUFFER,	True,
	GLX_SAMPLE_BUFFERS,	1,
	GLX_SAMPLES,		8,
	None
};

PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB;
PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLDELETEBUFFERSPROC glDeleteBuffers;
PFNGLCREATESHADERPROC glCreateShader;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLDELETESHADERPROC glDeleteShader;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
PFNGLUNIFORM4FVPROC glUniform4fv;
PFNGLDELETEPROGRAMPROC glDeleteProgram;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
PFNGLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointer;


void diamond(Position *terrain, int x1, int z1, int x2, int z2, int diff) {
	int meio;
	int count = 2;
	Position *ponto;
	
	if (x1 == x2) {
		meio = (z2 - z1) / 2;
		
		ponto = &terrain[x1 * Side + z1 + meio];
		
		//cout << "x: " << x1 << " z: " << z1 + meio << endl;
		
		ponto->y = 0.0f;
		
		if (x1 - meio >= 0) {
			ponto->y += terrain[(x1 - meio) * Side + z1 + meio].y;
			count++;
		}
		
		if (x1 + meio < Side) {
			ponto->y += terrain[(x1 + meio) * Side + z1 + meio].y;
			count++;
		}
	} else {
		meio = (x2 - x1) / 2;
		
		ponto = &terrain[(x1 + meio) * Side + z1];
		
		//cout << "x: " << x1 + meio << " z: " << z1 << endl;
		
		ponto->y = 0.0f;
		
		if (z1 - meio >= 0) {
			ponto->y += terrain[(x1 + meio) * Side + z1 - meio].y;
			count++;
		}
		
		if (z1 + meio < Side) {
			ponto->y += terrain[(x1 + meio) * Side + z1 + meio].y;
			count++;
		}
	}
	
	ponto->y += terrain[x1 * Side + z1].y + terrain[x2 * Side + z2].y;
	ponto->y /= count;
	ponto->y += rand() % (2 * diff + 1) - diff;
}

void MidpointDisplacement(Position *terrain, int start, int end, int diff) {
	int tam = end - start - 1;
	
	for (; tam > 1; tam /= 2) {
		for (int x = start; x < end - 1; x += tam) {
			for (int z = start; z < end - 1; z += tam) {
				int meioX = x + tam / 2;
				int meioZ = z + tam / 2;
				Position *ponto = &terrain[meioX * Side + meioZ];
		
				ponto->y = terrain[x * Side + z].y + terrain[x * Side + z + tam].y + terrain[(x + tam) * Side + z].y + terrain[(x + tam) * Side + z + tam].y;
				ponto->y /= 4;
				if (tam == end - start - 1) {
					ponto->y += rand() % (2 * diff + 1) - diff;
				}
			}
		}
		
		//diff = rand() % (diff - diff / 2 + 1) + diff / 2;
		diff =  diff * pow(2, -Smooth);
		
		for (int x = start; x < end - 1; x += tam) {
			for (int z = start; z < end - 1; z += tam) {
				int meioX = x + tam / 2;
				int meioZ = z + tam / 2;
				
				diamond(terrain, x, z, x, z + tam, diff);
				diamond(terrain, x, z, x + tam, z, diff);
				diamond(terrain, x + tam, z, x + tam, z + tam, diff);
				diamond(terrain, x, z + tam, x + tam, z + tam, diff);
			}
		}
	}
}

void GenerateTerrain(Position *terrain) {
	terrain[0].y = 5.0f;
	terrain[Side - 1].y = -4.0f;
	terrain[(Side - 1) * Side].y = .0f;
	terrain[(Side - 1) * Side + Side - 1].y = 2.0f;
	
	MidpointDisplacement(terrain, 0, Side, Variation);
}

void CreateWindow(){
	dpy = XOpenDisplay(NULL);
	
	root = DefaultRootWindow(dpy);
	
	int count;
	GLXFBConfig *p_fbc = glXChooseFBConfig(dpy, DefaultScreen(dpy), att, &count);
	
	if (count != 1){
		cout << "Either more than one or no FBConfig found" << endl;
		cout << count << endl;
		
		/*for (int i = 0; i < count; i++) {
			std::cout << p_fbc[i].
		}*/
		
		XCloseDisplay(dpy);
		exit(1);
	}
	
	fbc = p_fbc[0];
	XFree(p_fbc);
	
	vi = glXGetVisualFromFBConfig(dpy, fbc);
	
	cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
	
	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask | PointerMotionMask | ButtonMotionMask | ButtonPressMask | StructureNotifyMask;
	
	win = XCreateWindow(dpy, root, 0, 0, 600, 600, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
	
	delete_event = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(dpy, win, &delete_event, 1);
	
	XMapWindow(dpy, win);
	XStoreName(dpy, win, "Simple X Window");
	
	//Create a XEvent to tell the Window Manager to show the window as fullscreen
#ifdef Full
	memset(&xev, 0, sizeof(xev));
	xev.type = ClientMessage;
	xev.xclient.window = win;
	xev.xclient.message_type = XInternAtom(dpy, "_NET_WM_STATE", False);
	xev.xclient.format = 32;
	xev.xclient.data.l[0] = 1;
	xev.xclient.data.l[1] = XInternAtom(dpy, "_NET_WM_STATE_FULLSCREEN", False);
	xev.xclient.data.l[2] = xev.xclient.data.l[3] = xev.xclient.data.l[4] = 0;
	
	//Send the XEvent that was just created
	XSendEvent (dpy, root, False, SubstructureRedirectMask | SubstructureNotifyMask, &xev);
#endif
	int context_attribs[] = {
		GLX_CONTEXT_MAJOR_VERSION_ARB,	4,
		GLX_CONTEXT_MINOR_VERSION_ARB,	1,
		GLX_CONTEXT_FLAGS_ARB,			GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		GLX_CONTEXT_PROFILE_MASK_ARB,	GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
		GLX_RENDER_TYPE,				GLX_RGBA_TYPE,
		None
	};
	
	glXCreateContextAttribsARB = (PFNGLXCREATECONTEXTATTRIBSARBPROC) glXGetProcAddressARB( (const GLubyte *) "glXCreateContextAttribsARB");
	glGenBuffers = (PFNGLGENBUFFERSPROC) glXGetProcAddressARB( (const GLubyte *) "glGenBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC) glXGetProcAddressARB( (const GLubyte *) "glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC) glXGetProcAddressARB( (const GLubyte *) "glBufferData");
	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC) glXGetProcAddressARB( (const GLubyte *) "glDeleteBuffers");
	glCreateShader = (PFNGLCREATESHADERPROC) glXGetProcAddressARB( (const GLubyte *) "glCreateShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC) glXGetProcAddressARB( (const GLubyte *) "glShaderSource");
	glCompileShader = (PFNGLCOMPILESHADERPROC) glXGetProcAddressARB( (const GLubyte *) "glCompileShader");
	glCreateProgram = (PFNGLCREATEPROGRAMPROC) glXGetProcAddressARB( (const GLubyte *) "glCreateProgram");
	glAttachShader = (PFNGLATTACHSHADERPROC) glXGetProcAddressARB( (const GLubyte *) "glAttachShader");
	glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC) glXGetProcAddressARB( (const GLubyte *) "glBindAttribLocation");
	glLinkProgram = (PFNGLLINKPROGRAMPROC) glXGetProcAddressARB( (const GLubyte *) "glLinkProgram");
	glDeleteShader = (PFNGLDELETESHADERPROC) glXGetProcAddressARB( (const GLubyte *) "glDeleteShader");
	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC) glXGetProcAddressARB( (const GLubyte *) "glGenVertexArrays");
	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC) glXGetProcAddressARB( (const GLubyte *) "glBindVertexArray");
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC) glXGetProcAddressARB( (const GLubyte *) "glEnableVertexAttribArray");
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC) glXGetProcAddressARB( (const GLubyte *) "glVertexAttribPointer");
	glUseProgram = (PFNGLUSEPROGRAMPROC) glXGetProcAddressARB( (const GLubyte *) "glUseProgram");
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) glXGetProcAddressARB( (const GLubyte *) "glGetUniformLocation");
	glUniform4fv = (PFNGLUNIFORM4FVPROC) glXGetProcAddressARB( (const GLubyte *) "glUniform4fv");
	glDeleteProgram = (PFNGLDELETEPROGRAMPROC) glXGetProcAddressARB( (const GLubyte *) "glDeleteProgram");
	glGetShaderiv = (PFNGLGETSHADERIVPROC) glXGetProcAddressARB( (const GLubyte *) "glGetShaderiv");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) glXGetProcAddressARB( (const GLubyte *) "glGetShaderInfoLog");
	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC) glXGetProcAddressARB( (const GLubyte *) "glUniformMatrix4fv");
	glVertexAttribIPointer = (PFNGLVERTEXATTRIBIPOINTERPROC) glXGetProcAddressARB( (const GLubyte *) "glVertexAttribIPointer");
	
	if (!glGenBuffers || !glBindBuffer || !glBufferData || !glDeleteBuffers || !glXCreateContextAttribsARB){
		cout << "Error getting gl functions address" << endl;
		
		XCloseDisplay(dpy);
		exit(1);
	}
	
	glc = glXCreateContextAttribsARB(dpy, fbc, 0, True, context_attribs);
	//glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
	
	if (glc == NULL){
		cout << "Failed to create a context" << endl;
		
		XCloseDisplay(dpy);
		exit(1);
	}
	
	if (glXIsDirect(dpy, glc)){
		cout << "Direct GLX rendering context obtained" << endl;
	}else{
		cout << "Indirect GLX rendering context obtained" << endl;
	}
	
	glXMakeCurrent(dpy, win, glc);
	
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.196f, 0.588f, 1.0f, 1.0f);
}

int main(){
	
	srand( time(NULL));
	
	CreateWindow();
	
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint program;
	GLint modelviewUniform;
	GLint projectionUniform;
	GLint testVal;
	
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	glShaderSource(vertexShader, 1, &szIdentityShaderVP, NULL);
	glShaderSource(fragmentShader, 1, &szIdentityShaderFP, NULL);
	
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);
	
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &testVal);
	if (testVal == GL_FALSE){
		cout << "Vertex Shader Error" << endl;
		
		char log[5000];
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &testVal);
		glGetShaderInfoLog(vertexShader, 5000, &testVal, log);
		
		cout << log << endl;
		exit(1);
	}
	
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &testVal);
	if (testVal == GL_FALSE){
		cout << "Fragment Shader Error" << endl;
		
		char log[5000];
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &testVal);
		glGetShaderInfoLog(fragmentShader, 5000, &testVal, log);
		
		cout << log << endl;
		exit(1);
	}
	
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	
	glBindAttribLocation(program, 0, "vVertex");
	glBindAttribLocation(program, 1, "vColor");
	
	glLinkProgram(program);
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	Position *terrain = (Position *) new Position[Side * Side];
	Color *color = (Color *) new Color[Side * Side];
	vector<GLuint> *index = new vector<GLuint>();
	
	GLfloat z_pos = -(Side / 2) * Size;
	
	for (int i = 0; i < Side; i++){
		GLfloat x_pos = -(Side / 2) * Size;
		
		for (int j = 0; j < Side; j++){
			terrain[i * Side + j].x = x_pos;
			terrain[i * Side + j].y = 0.0f; //static_cast<GLfloat>(rand() % 50) - 25.0f;
			terrain[i * Side + j].z = z_pos;
			
			color[i * Side + j].r = static_cast<GLfloat>(rand()) / RAND_MAX;
			color[i * Side + j].g = static_cast<GLfloat>(rand()) / RAND_MAX;
			color[i * Side + j].b = static_cast<GLfloat>(rand()) / RAND_MAX;
			
			x_pos += Size;
		}
		
		z_pos += Size;
	}
	
	GenerateTerrain(terrain);
	
	for (int z = 0; z < Side - 1; z++){
		for (int x = 0; x < Side - 1; x++){
			index->push_back((z * Side) + x);
			index->push_back((z * Side) + x + 1);
			index->push_back(((z + 1) * Side) + x);
			
			index->push_back((z * Side) + x + 1);
			index->push_back(((z + 1) * Side) + x + 1);
			index->push_back(((z + 1) * Side) + x);
		}
	}
	
	int size = index->size();
	
	GLuint vbo[2];
	GLuint vao;
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glGenBuffers(2, &vbo[0]);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, Side * Side * sizeof(Position), terrain, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, Side * Side * sizeof(Color), color, GL_STATIC_DRAW);
	
	GLuint index_buffer;
	
	glGenBuffers(1, &index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLuint), &(*index)[0], GL_STATIC_DRAW);
	
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
	
	/*
	GLuint vbo[3];
	GLuint vao;
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glGenBuffers(3, &vbo[0]);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat) * 3, triangle, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat) * 4, color, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), index, GL_STATIC_DRAW);
	
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
	*/
	
	Matrix4 modelview;
	Matrix4 projection;
	
	modelview.identity();
	modelview.translate(0, -2 - terrain[(Side / 2) * Side + Side / 2].y, 0);
	modelview.rotate(45, 0, 1, 0);
	/*modelview.translate(0, -40.0, 0);
	modelview.rotate(45, 0, 1, 0);
	modelview.translate(0, 0, 40);*/
	
	//modelview.translate(1.0, 1.0, 1.0);
	//modelview.scale(0.5, 0.5, 0.5);
	//std::cout << modelview << std::endl;
	
	//projection.setFrustum(-1, 1, -2, 2, 1, 100);
	
	glEnable(GL_DEPTH_TEST);
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	//std::cout << projection << std::endl;
	bool loop = true;
	
	int quant = size;
	float vert = 0;
	float hor = 0;
	int vertRot;
	int horRot;
	float xPos = 0;
	float yPos = 0;
	float zPos = 0;
	int vertTotal = 0;
	
	double fps = 0.0;
	double elapsedSeconds = 0.0;
	unsigned int last;
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	
	last = tv.tv_sec * 1000 + tv.tv_usec /1000;
	
	while (loop){
		vertRot = 0;
		horRot = 0;
		
		while (XPending(dpy) > 0){
			XNextEvent(dpy, &xev);
			
			switch (xev.type){
				case KeyPress:
					switch (XLookupKeysym(&xev.xkey, 0)){
						case (XK_space):
							//modelview.translate(0, 0, 1);
							
							/*if (quant == size)
								quant = 0;
							
							quant += 600;*/
							break;
						case (XK_w):
							if (xev.xkey.state & ShiftMask)
								vert = -Run;
							else
								vert = -Walk;
							break;
						case (XK_s):
							if (xev.xkey.state & ShiftMask)
								vert = Run;
							else
								vert = Walk;
							break;
						case (XK_a):
							if (xev.xkey.state & ShiftMask)
								hor = Run;
							else
								hor = Walk;
							break;
						case (XK_d):
							if (xev.xkey.state & ShiftMask)
								hor = -Run;
							else
								hor = -Walk;
							break;
						case (XK_Up):
							vertRot++;
							break;
						case (XK_Down):
							vertRot--;
							break;
						case (XK_Left):
							horRot++;
							break;
						case (XK_Right):
							horRot--;
							break;
						case (XK_Escape):
							loop = false;
							break;
					}
					//cout << (xev.xkey.state & Mod1Mask) << endl;
					break;
				case KeyRelease:
					switch (XLookupKeysym(&xev.xkey, 0)){
						case (XK_space):
							//modelview.translate(0, 0, 1);
							
							/*if (quant == size)
								quant = 0;
							
							quant += 600;*/
							break;
						case (XK_w):
							vert = 0;
							break;
						case (XK_s):
							vert = 0;
							break;
						case (XK_a):
							hor = 0;
							break;
						case (XK_d):
							hor = 0;
							break;
					}
					break;
				case ButtonPress:
					/*cout << xev.xbutton.time << endl;
					cout << xev.xbutton.button << endl;
					cout << xev.xbutton.x << ", " << xev.xbutton.y << endl << endl;*/
					break;
				case MotionNotify:
					/*static int lastX = 0;
					
					cout << xev.xmotion.time << endl;
					cout << xev.xmotion.x << ", " << xev.xmotion.y << endl << endl;*/
					break;
				case ClientMessage:
					if (xev.xclient.data.l[0] == delete_event)
						loop = false;
					break;
				case ConfigureNotify:					
					glViewport(0, 0, xev.xconfigure.width, xev.xconfigure.height);
					projection.setPerspective(60, static_cast<float>(xev.xconfigure.width) / xev.xconfigure.height, 1, 1000);
					break;
				default:
					break;
			}
		}
		
		vertTotal += vertRot;
		
		gettimeofday(&tv, NULL);
		
		unsigned int now = tv.tv_sec*1000 + tv.tv_usec / 1000;
		elapsedSeconds = double(now - last) / 1000.0;
		last = now;
		
		/*
		if (elapsedSeconds == 0){
			fps = 0.75 * fps + 0.25 * (1 / 100);
		} else {
			fps = 0.75 * fps + 0.25 * (1 / elapsedSeconds);
		}

		cout << fps << endl;
		*/
		
		//cout << elapsedSeconds << endl;
		/*
		float yHor;
		float zHor;
		
		yHor = cos(vertTotal * 3.14159265358979f / 180.0f);
		zHor = sqrt(2 - 2 * yHor * cos(vertTotal * 3.14159265358979f / 180.0f) - pow(yHor - 1, 2));
		*/
		modelview.rotate(vertRot - vertTotal, 1, 0, 0);
		modelview.rotate(horRot, 0, 1, 0);
		modelview.rotate(vertTotal, 1, 0, 0);
		modelview.translate(hor * elapsedSeconds, 0, vert * elapsedSeconds);
		
		//cout << glGetError() << endl;
		
		//modelview.rotate(0.1, 1, 0, 0);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glUseProgram(program);
		
		modelviewUniform = glGetUniformLocation(program, "mvmat");
		glUniformMatrix4fv(modelviewUniform, 1, GL_FALSE, &modelview[0]);
		
		projectionUniform = glGetUniformLocation(program, "pmat");
		glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, &projection[0]);
		
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, quant, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		
		glXSwapBuffers(dpy, win);
		
		//usleep(50000);
	}
	
	//Create a XEvent to tell the Window Manager to show the window as non-fullscreen
#ifdef Full
	memset(&xev, 0, sizeof(xev));
	xev.type = ClientMessage;
	xev.xclient.window = win;
	xev.xclient.message_type = XInternAtom(dpy, "_NET_WM_STATE", False);
	xev.xclient.format = 32;
	xev.xclient.data.l[0] = 0;
	xev.xclient.data.l[1] = XInternAtom(dpy, "_NET_WM_STATE_FULLSCREEN", False);
	xev.xclient.data.l[2] = xev.xclient.data.l[3] = xev.xclient.data.l[4] = 0;
	
	//Send the XEvent just created
	XSendEvent (dpy, root, False, SubstructureRedirectMask | SubstructureNotifyMask, &xev);
#endif
	glDeleteProgram(program);
	
	glXMakeCurrent(dpy, None, NULL);
	glXDestroyContext(dpy, glc);
	
	XDestroyWindow(dpy, win);	
	XCloseDisplay(dpy);
	
	cout << "final" << endl;
	
	//delete []terrain;
	//delete []color;
	//delete index;
	
	return 0;
}
