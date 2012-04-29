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

using std::vector;
using std::cout;
using std::endl;

static const char *szIdentityShaderVP = "#version 410 core\n"
										"in vec4 vVertex;"
										"in vec4 vColor;"
										"flat out vec4 fColor;"
										"uniform mat4 pmat;"
										"uniform mat4 mvmat;"
										"void main() "
										"{ gl_Position = pmat * mvmat * vVertex; "
										"fColor = vColor;"
										"}";
									
static const char *szIdentityShaderFP = "#version 410 core\n"
										"flat in vec4 fColor;"
										"void main(void) "
										"{ gl_FragColor = fColor;"
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

void CreateWindow(){
	dpy = XOpenDisplay(NULL);
	
	root = DefaultRootWindow(dpy);
	
	int count;
	GLXFBConfig *p_fbc = glXChooseFBConfig(dpy, DefaultScreen(dpy), att, &count);
	
	if (count != 1){
		cout << "Either more than one or no FBConfig found" << endl;
		
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
	/*
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
	*/
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
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
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
	
	GLfloat *terrain = (GLfloat *) new GLfloat[30603];
	GLfloat *color = (GLfloat *) new GLfloat[30603];
	vector<GLuint> *index = new vector<GLuint>();
	
	GLfloat z_pos = -500.0f;
	
	for (int i = 0; i < 101; i++){
		GLfloat x_pos = -500.0f;
		
		for (int j = 0; j < 101; j++){
			terrain[(i*101 + j)*3] = x_pos;
			terrain[(i*101 + j)*3 + 1] = 0.0f;
			terrain[(i*101 + j)*3 + 2] = z_pos;
			
			color[(i*101 + j)*3] = static_cast<GLfloat>(rand()) / RAND_MAX;
			color[(i*101 + j)*3 + 1] = static_cast<GLfloat>(rand()) / RAND_MAX;
			color[(i*101 + j)*3 + 2] = static_cast<GLfloat>(rand()) / RAND_MAX;
			
			x_pos += 10.0f;
		}
		
		z_pos += 10.0f;
	}
	
	for (int z = 0; z < 100; z++){
		for (int x = 0; x < 100; x++){
			index->push_back((z * 101) + x);
			index->push_back((z * 101) + x + 1);
			index->push_back(((z + 1) * 101) + x);
			
			index->push_back((z * 101) + x + 1);
			index->push_back(((z + 1) * 101) + x + 1);
			index->push_back(((z + 1) * 101) + x);
		}
	}
	
	int size = index->size();
	
	GLuint vbo[2];
	GLuint vao;
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glGenBuffers(2, &vbo[0]);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 30603 * sizeof(GLfloat), terrain, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, 30603 * sizeof(GLfloat), color, GL_STATIC_DRAW);
	
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
	modelview.rotate(45, 0, 1, 0);
	modelview.translate(0, -2, 0);
	/*modelview.translate(0, -40.0, 0);
	modelview.rotate(45, 0, 1, 0);
	modelview.translate(0, 0, 40);*/
	
	//modelview.translate(1.0, 1.0, 1.0);
	//modelview.scale(0.5, 0.5, 0.5);
	//std::cout << modelview << std::endl;
	
	//projection.setFrustum(-1, 1, -2, 2, 1, 100);
	
	glEnable(GL_DEPTH_TEST);
	
	//std::cout << projection << std::endl;
	bool loop = true;
	
	int quant = size;
	float vert = 0;
	float hor = 0;
	
	double elapsedSeconds = 0;
	unsigned int last;
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	
	last = tv.tv_sec * 1000 + tv.tv_usec /1000;
	
	while (loop){
		
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
								vert = -3;
							else
								vert = -1.4;
							break;
						case (XK_s):
							if (xev.xkey.state & ShiftMask)
								vert = 3;
							else
								vert = 1.4;
							break;
						case (XK_a):
							if (xev.xkey.state & ShiftMask)
								hor = 3;
							else
								hor = 1.4;
							break;
						case (XK_d):
							if (xev.xkey.state & ShiftMask)
								hor = -3;
							else
								hor = -1.4;
							break;
						case (XK_Escape):
							loop = false;
							break;
					}
					cout << (xev.xkey.state & Mod1Mask) << endl;
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
					projection.setPerspective(60, static_cast<float>(xev.xconfigure.width) / xev.xconfigure.height, 1, 100);
					break;
				default:
					break;
			}
		}
		
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
		
		gettimeofday(&tv, NULL);
		
		unsigned int now = tv.tv_sec*1000 + tv.tv_usec / 1000;
		elapsedSeconds = double(now - last) / 1000.0;
		last = now;
		
		//cout << elapsedSeconds << endl;
		
		modelview.translate(hor * elapsedSeconds, 0, vert * elapsedSeconds);
		
		//usleep(50000);
	}
	
	//Create a XEvent to tell the Window Manager to show the window as non-fullscreen
	/*
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
	*/
	glDeleteProgram(program);
	
	glXMakeCurrent(dpy, None, NULL);
	glXDestroyContext(dpy, glc);
	
	XDestroyWindow(dpy, win);	
	XCloseDisplay(dpy);
	
	delete []terrain;
	delete index;
	
	return 0;
}
