#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<math.h>
#include<time.h>
#include<sys/time.h>
#include<X11/Xlib.h>
#include<GL/glx.h>
#include<GL/glu.h>

//This should be defined in order to use VBOs in Linux compiling under g++
//Strangely, when compiling using gcc it is not needed
#define		GL_GLEXT_PROTOTYPES
#include<GL/glext.h>

#define GLX_CONTEXT_MAJOR_VERSION_ARB       0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB       0x2092
#define		BUFFER_OFFSET(i)	((int *)NULL + (i))		//Used to calculate the offset in bytes of the VBOs
														//Should be int cause I used int for holding my indices where I use the offset

GLuint m_vertexBuffer;
GLuint m_colorBuffer;
GLuint m_indexBuffer;
typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
PFNGLGENBUFFERSPROC glGenBuffers = 0;
PFNGLBINDBUFFERPROC glBindBuffer = 0;
PFNGLBUFFERDATAPROC glBufferData = 0;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = 0;
//////////////////////////////////////////////////////////////////////////////////
//				GLOBAL IDENTIFIERS				//
//////////////////////////////////////////////////////////////////////////////////
Display                 *dpy;
Window                  root, win;
GLint                   att[]   = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
XVisualInfo             *vi;
GLXContext              glc;
Colormap                cmap;
XSetWindowAttributes    swa;
XWindowAttributes	wa;
XEvent			xev;
GLXFBConfig bestFbc;

float			TimeCounter, LastFrameTimeCounter, DT, prevTime = 0.0, FPS;
struct timeval		tv, tv0;
int			Frame = 1, FramesPerFPS;

GLfloat			rotation_matrix[16];
float			rot_z_vel = 50.0, rot_y_vel = 30.0;
//////////////////////////////////////////////////////////////////////////////////
//				DRAW A CUBE					//
//////////////////////////////////////////////////////////////////////////////////
void DrawCube(float size) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, 0);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, BUFFER_OFFSET(4)); }
//////////////////////////////////////////////////////////////////////////////////
//				ROTATE THE CUBE					//
//////////////////////////////////////////////////////////////////////////////////
void RotateCube() {
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 glRotatef(rot_y_vel*DT, 0.0, 1.0, 0.0);
 glRotatef(rot_z_vel*DT, 0.0, 0.0, 1.0);
 glMultMatrixf(rotation_matrix);
 glGetFloatv(GL_MODELVIEW_MATRIX, rotation_matrix); }
//////////////////////////////////////////////////////////////////////////////////
//				EXPOSURE FUNCTION				//
//////////////////////////////////////////////////////////////////////////////////
void ExposeFunc() {
 float	aspect_ratio;
 char	info_string[256];
 /////////////////////////////////
 //	RESIZE VIEWPORT		//
 /////////////////////////////////
 XGetWindowAttributes(dpy, win, &wa);
 glViewport(0, 0, wa.width, wa.height);
 aspect_ratio = (float)(wa.width) / (float)(wa.height);
 /////////////////////////////////////////
 //	SETUP PROJECTION & MODELVIEW	//
 /////////////////////////////////////////
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glFrustum(-.50*aspect_ratio, .50*aspect_ratio, -.50, .50, 1., 3.);

 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 gluLookAt(2., 0., 0., 0., 0., 0., 0., 0., 1.);
 glMultMatrixf(rotation_matrix);
 /////////////////////////////////
 //	DRAW CUBE		//
 /////////////////////////////////
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 DrawCube(1.0);
 /////////////////////////////////
 //	DISPLAY TIME, FPS etc.	//
 /////////////////////////////////
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glOrtho(0, (float)wa.width, 0, (float)wa.height, -1., 1.);

 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();

 glColor3f(1.0, 1.0, 1.0);

 sprintf(info_string, "%4.1f seconds * %4.1f fps at %i x %i", TimeCounter, FPS, wa.width, wa.height, rot_z_vel);
 glRasterPos2i(10, 10);
 glCallLists(strlen(info_string), GL_UNSIGNED_BYTE, info_string);

 sprintf(info_string, "<up,down,left,right> rotate cube * <F1> stop rotation ");
 glRasterPos2i(10, wa.height-32);
 glCallLists(strlen(info_string), GL_UNSIGNED_BYTE, info_string);
 /////////////////////////////////
 //	SWAP BUFFERS		//
 /////////////////////////////////
 glXSwapBuffers(dpy, win); }
//////////////////////////////////////////////////////////////////////////////////
//				CREATE A GL CAPABLE WINDOW			//
//////////////////////////////////////////////////////////////////////////////////
void CreateWindow() {

 if((dpy = XOpenDisplay(NULL)) == NULL) {
 	printf("\n\tcannot connect to x server\n\n");
	exit(0); }
 
 static int visual_attribs[] =
    {
      GLX_X_RENDERABLE    , True,
      GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
      GLX_RENDER_TYPE     , GLX_RGBA_BIT,
      GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
      GLX_RED_SIZE        , 8,
      GLX_GREEN_SIZE      , 8,
      GLX_BLUE_SIZE       , 8,
      GLX_ALPHA_SIZE      , 8,
      GLX_DEPTH_SIZE      , 24,
      GLX_STENCIL_SIZE    , 8,
      GLX_DOUBLEBUFFER    , True,
      //GLX_SAMPLE_BUFFERS  , 1,
      //GLX_SAMPLES         , 4,
      None
    };
 int fbcount;
  GLXFBConfig *fbc = glXChooseFBConfig( dpy, DefaultScreen( dpy ), 
                                        visual_attribs, &fbcount );
 int best_fbc = -1, worst_fbc = -1, best_num_samp = -1, worst_num_samp = 999;
 
  int i;
  for ( i = 0; i < fbcount; i++ )
  {
    XVisualInfo *vi = glXGetVisualFromFBConfig( dpy, fbc[i] );
    if ( vi )
    {
      int samp_buf, samples;
      glXGetFBConfigAttrib( dpy, fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf );
      glXGetFBConfigAttrib( dpy, fbc[i], GLX_SAMPLES       , &samples  );
 
      if ( best_fbc < 0 || samp_buf && samples > best_num_samp )
        best_fbc = i, best_num_samp = samples;
      if ( worst_fbc < 0 || !samp_buf || samples < worst_num_samp )
        worst_fbc = i, worst_num_samp = samples;
    }
    XFree( vi );
  }
  
  bestFbc = fbc[ best_fbc ];
 
  // Be sure to free the FBConfig list allocated by glXChooseFBConfig()
  XFree( fbc );
 
  // Get a visual
  vi = glXGetVisualFromFBConfig( dpy, bestFbc );

 root = DefaultRootWindow(dpy);
 
 if((vi = glXChooseVisual(dpy, 0, att)) == NULL) {
	printf("\n\tno matching visual\n\n");
	exit(0); }
	
 if((cmap = XCreateColormap(dpy, root, vi->visual, AllocNone)) == 0) {
 	printf("\n\tcannot create colormap\n\n");
	exit(0); }
	
 swa.event_mask = KeyPressMask;
 swa.colormap 	= cmap;
 win = XCreateWindow(dpy, root, 0, 0, 700, 700, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
 XStoreName(dpy, win, "OpenGL Animation");
 XMapWindow(dpy, win); }
//////////////////////////////////////////////////////////////////////////////////
//				SETUP GL CONTEXT				//
//////////////////////////////////////////////////////////////////////////////////
void SetupGL() {
 char		font_string[128];
 XFontStruct	*font_struct;
 /////////////////////////////////////////////////
 //	CREATE GL CONTEXT AND MAKE IT CURRENT	//
 /////////////////////////////////////////////////
  glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
  glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)glXGetProcAddressARB( (const GLubyte *) "glXCreateContextAttribsARB" );
  glGenBuffers = (PFNGLGENBUFFERSPROC) glXGetProcAddressARB( (const GLubyte *) "glGenBuffers");
  glBindBuffer = (PFNGLBINDBUFFERPROC) glXGetProcAddressARB( (const GLubyte *) "glBindBuffer");
  glBufferData = (PFNGLBUFFERDATAPROC) glXGetProcAddressARB( (const GLubyte *) "glBufferData");
  glDeleteBuffers = (PFNGLDELETEBUFFERSPROC) glXGetProcAddressARB( (const GLubyte *) "glDeleteBuffers");
  
  int context_attribs[] =
      {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
        GLX_CONTEXT_MINOR_VERSION_ARB, 1,
        //GLX_CONTEXT_FLAGS_ARB        , GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
        GLX_CONTEXT_PROFILE_MASK_ARB , GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
        None
      };
 
 if((glc = glXCreateContextAttribsARB(dpy, bestFbc, NULL, GL_TRUE, context_attribs)) == NULL) {
 	printf("\n\tcannot create gl context\n\n");
	exit(0); }

 glXMakeCurrent(dpy, win, glc);
 glEnable(GL_DEPTH_TEST);
 glClearColor(0.00, 0.00, 0.40, 1.00);
 /////////////////////////////////////////////////
 //	FIND A FONT				//
 /////////////////////////////////////////////////
 //for(int font_size = 14; font_size < 32; font_size += 2) {
 	sprintf(font_string, "-adobe-courier-*-r-normal--*");
	font_struct = XLoadQueryFont(dpy, font_string);
	printf("%d XLoadQueryFont(dpy, font_string);\n", glGetError());
	
	if(font_struct != NULL) //{
 		glXUseXFont(font_struct->fid, 32, 192, 32);		
		//break; } }
	printf("%d glXUseXFont(font_struct->fid, 32, 192, 32);\n", glGetError());
	
	GLfloat piramide[] = {0.0f, 0.5f, 0.0f,
						  -0.5f, -0.5f, 0.0f,
						  0.0f, -0.5f, -0.5f,
						  0.5f, -0.5f, 0.0f,
						  0.0f, -0.5f, 0.5f};
	
	GLfloat cor[] = 	{1.0f, 0.0f, 0.0f,
						 0.0f, 1.0f, 0.0f,
						 0.0f, 0.0f, 1.0f,
						 1.0f, 1.0f, 0.0f,
						 1.0f, 0.0f, 1.0f,};
	
	GLuint indices[] = {0, 1, 2, 3, 4, 1, 3, 2};
	
	glGenBuffers(1, &m_vertexBuffer);
	
	if (!m_vertexBuffer){
		printf("Erro VBO\n");
		exit(1);
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 15, &piramide[0], GL_STATIC_DRAW);
	
	glGenBuffers(1, &m_colorBuffer);
	
	if (!m_colorBuffer){
		printf("Erro VBO\n");
		exit(1);
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 15, &cor[0], GL_STATIC_DRAW);
	
	glGenBuffers(1, &m_indexBuffer);
	
	if (!m_indexBuffer){
		printf("Erro VBO\n");
		exit(1);
	}
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 9, &indices[0], GL_STATIC_DRAW);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	printf("%d glEnableClientState(GL_VERTEX_ARRAY);\n", glGetError());
	glEnableClientState(GL_COLOR_ARRAY);
	printf("%d glEnableClientState(GL_COLOR_ARRAY);\n", glGetError());
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	printf("%d glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);\n", glGetError());
	glVertexPointer(3, GL_FLOAT, 0, 0);
	printf("%d glVertexPointer(3, GL_FLOAT, 0, 0);\n", glGetError());
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
	printf("%d glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);\n", glGetError());
	glColorPointer(3, GL_FLOAT, 0, 0);
	printf("%d glColorPointer(3, GL_FLOAT, 0, 0);\n", glGetError());
 /////////////////////////////////////////////////
 //	INITIALIZE ROTATION MATRIX		//
 /////////////////////////////////////////////////
 glMatrixMode(GL_MODELVIEW);
	printf("%d glMatrixMode(GL_MODELVIEW);\n", glGetError());
 glLoadIdentity();
	printf("%d glLoadIdentity();\n", glGetError());
 glGetFloatv(GL_MODELVIEW_MATRIX, rotation_matrix);
	printf("%d glGetFloatv(GL_MODELVIEW_MATRIX, rotation_matrix);\n", glGetError()); }
//////////////////////////////////////////////////////////////////////////////////
//				TIME COUNTER FUNCTIONS				//
//////////////////////////////////////////////////////////////////////////////////
void InitTimeCounter() {
 gettimeofday(&tv0, NULL);
 FramesPerFPS = 30; }

void UpdateTimeCounter() {
 LastFrameTimeCounter = TimeCounter;
 gettimeofday(&tv, NULL);
 TimeCounter = (float)(tv.tv_sec-tv0.tv_sec) + 0.000001*((float)(tv.tv_usec-tv0.tv_usec));
 DT = TimeCounter - LastFrameTimeCounter; }

void CalculateFPS() {
 Frame ++;

 if((Frame%FramesPerFPS) == 0) {
	FPS = ((float)(FramesPerFPS)) / (TimeCounter-prevTime);
	prevTime = TimeCounter; } }
//////////////////////////////////////////////////////////////////////////////////
//				EXIT PROGRAM					//
//////////////////////////////////////////////////////////////////////////////////
void ExitProgram() {
 glXMakeCurrent(dpy, None, NULL);
 glXDestroyContext(dpy, glc);
 XDestroyWindow(dpy, win);
 XCloseDisplay(dpy);
 exit(0); }
//////////////////////////////////////////////////////////////////////////////////
//				CHECK EVENTS					//
//////////////////////////////////////////////////////////////////////////////////
void CheckKeyboard() {

 if(XCheckWindowEvent(dpy, win, KeyPressMask, &xev)) {
	char	*key_string = XKeysymToString(XKeycodeToKeysym(dpy, xev.xkey.keycode, 0));

	if(strncmp(key_string, "Left", 4) == 0) {
		rot_z_vel -= 200.0*DT; }

	else if(strncmp(key_string, "Right", 5) == 0) {
		rot_z_vel += 200.0*DT; }

	else if(strncmp(key_string, "Up", 2) == 0) {
		rot_y_vel -= 200.0*DT; }

	else if(strncmp(key_string, "Down", 4) == 0) {
		rot_y_vel += 200.0*DT; }

	else if(strncmp(key_string, "F1", 2) == 0) {
		rot_y_vel = 0.0; 
		rot_z_vel = 0.0; }

	else if(strncmp(key_string, "Escape", 5) == 0) {
		ExitProgram(); } } }
//////////////////////////////////////////////////////////////////////////////////
//				MAIN PROGRAM					//
//////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]){

 CreateWindow();
 SetupGL();
 InitTimeCounter();

 while(true) {
	//printf("%d", glGetError());
	UpdateTimeCounter();
	CalculateFPS();
	RotateCube();
	ExposeFunc(); 
	usleep(1000);
	CheckKeyboard(); } }
