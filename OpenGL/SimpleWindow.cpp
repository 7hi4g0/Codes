#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <vector>

#define		GLX_GLXEXT_PROTOTYPES
#include <GL/glxext.h>

using std::vector;

static const char *szIdentityShaderVP = "#version 410 core\n"
										"in vec4 vVertex;"
										"void main() "
										"{ gl_Position = vVertex; "
										"}";
									
static const char *szIdentityShaderFP = "#version 410 core\n"
										"precision mediump float;"
										"uniform vec4 vColor;"
										"void main(void) "
										"{ gl_FragColor = vColor;"
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

void CreateWindow(){
	dpy = XOpenDisplay(NULL);
	
	root = DefaultRootWindow(dpy);
	
	int count;
	GLXFBConfig *p_fbc = glXChooseFBConfig(dpy, DefaultScreen(dpy), att, &count);
	
	if (count != 1){
		printf("Either more than one or no FBConfig found\n");
		
		XCloseDisplay(dpy);
		exit(1);
	}
	
	fbc = p_fbc[0];
	XFree(p_fbc);
	
	vi = glXGetVisualFromFBConfig(dpy, fbc);
	
	cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
	
	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask;
	
	win = XCreateWindow(dpy, root, 0, 0, 600, 600, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
	
	delete_event = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(dpy, win, &delete_event, 1);
	
	XMapWindow(dpy, win);
	XStoreName(dpy, win, "Simple X Window");
	
	//Create a XEvent to tell the Window Manager to sohw the window as fullscreen
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
		//GLX_CONTEXT_FLAGS_ARB,			GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
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
	
	if (!glGenBuffers || !glBindBuffer || !glBufferData || !glDeleteBuffers){
		printf("fuck\n");
		
		XCloseDisplay(dpy);
		exit(1);
	}
	
	glc = glXCreateContextAttribsARB(dpy, fbc, 0, True, context_attribs);
	//glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
	
	if (glc == NULL){
		printf("Failed to create a context\n");
		
		XCloseDisplay(dpy);
		exit(1);
	}
	
	if (glXIsDirect(dpy, glc)){
		fprintf(stdout, "Direct GLX rendering context obtained\n");
	}
	
	glXMakeCurrent(dpy, win, glc);
	
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

int main(){
	
	CreateWindow();
	
	/*
	GLfloat *terrain = (GLfloat *) new float[61206];
	vector<GLuint> *index = new vector<GLuint>();
	
	GLfloat x_pos = -1.0f;
	GLfloat z_pos = -1.0f;
	
	for (int i = 0; i < 61206; i += 6){
		terrain[i] = x_pos += 0.02f;
		terrain[i + 1] = 0.0f;
		terrain[i + 2] = z_pos += 0.02f;
		terrain[i + 3] = 0.0f;
		terrain[i + 4] = 1.0f;
		terrain[i + 5] = 0.0f;
	}
	
	for (int z = 0; z < 100; z++){
		for (int x = 0; x < 100; x++){
			index->push_back((z * 101) + x);
			index->push_back(((z + 1) * 101) + x);
			index->push_back((z * 101) + x + 1);
			
			index->push_back(((z + 1) * 101) + x);
			index->push_back(((z + 1) * 101) + x + 1);
			index->push_back((z * 101) + x + 1);
		}
	}
	
	int size = index->size();
	
	GLuint vbo;
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 61206, terrain, GL_STATIC_DRAW);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	#define	OFFSET(i)	((char *)NULL + (i))
	glVertexPointer(3, GL_FLOAT, 3 * sizeof(GLfloat), 0);
	glColorPointer(3, GL_FLOAT, 3 * sizeof(GLfloat), OFFSET(3 * sizeof(GLfloat)));
	
	GLuint index_buffer;
	
	glGenBuffers(1, &index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, &(*index)[0], GL_STATIC_DRAW);
	
	delete []terrain;
	delete index;
	*/
	
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint program;
	GLint colorUniform;
	GLint testVal;
	
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	glShaderSource(vertexShader, 1, &szIdentityShaderVP, NULL);
	glShaderSource(fragmentShader, 1, &szIdentityShaderFP, NULL);
	
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);
	
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &testVal);
	if (testVal == GL_FALSE){
		printf("Erro no Vertex Shader\n");
		
		char log[5000];
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &testVal);
		glGetShaderInfoLog(vertexShader, 5000, &testVal, log);
		
		printf("%s\n",log);
		exit(1);
	}
	
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &testVal);
	if (testVal == GL_FALSE){
		printf("Erro no Fragment Shader\n");
		
		char log[5000];
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &testVal);
		glGetShaderInfoLog(fragmentShader, 5000, &testVal, log);
		
		printf("%s\n",log);
		exit(1);
	}
	
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	
	glBindAttribLocation(program, 0, "vVertex");
	
	glLinkProgram(program);
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	GLfloat triangle[] = {
		0.0f,	0.7f,
		-0.5f,	-0.3f,
		0.5f,	-0.3f
	};
	
	GLuint index[] = { 0, 1, 2 };
	
	GLuint vbo[2];
	GLuint vao;
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glGenBuffers(2, &vbo[0]);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat) * 2, triangle, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLuint), index, GL_STATIC_DRAW);
	
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
	
	bool loop = true;
	
	while (loop){
		XGetWindowAttributes(dpy, win, &gwa);
		
		glViewport(0, 0, gwa.width, gwa.height);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		GLfloat color[] = {
			1.0f,	1.0f,	0.0f,	1.0f
		};
		
		glUseProgram(program);
		
		colorUniform = glGetUniformLocation(program, "vColor");
		glUniform4fv(colorUniform, 1, color);
		
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		
		glXSwapBuffers(dpy, win);
		
		while (XPending(dpy) > 0){
			XNextEvent(dpy, &xev);
			
			switch (xev.type){
				case KeyPress:
					if (XLookupKeysym(&xev.xkey, 0) == XK_space){
						
					}
					break;
				case ClientMessage:
					if (xev.xclient.data.l[0] == delete_event)
						loop = false;
					break;
				default:
					break;
			}
		}
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
	
	return 0;
}
