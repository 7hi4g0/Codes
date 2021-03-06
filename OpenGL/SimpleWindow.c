#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <X11/Xlib.h>

#define		GLX_GLXEXT_PROTOTYPES
#include <GL/glxext.h>

int main(){
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
		GLX_CONTEXT_FLAGS_ARB,			GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		GLX_CONTEXT_PROFILE_MASK_ARB,	GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
		GLX_RENDER_TYPE,				GLX_RGBA_TYPE,
		None
	};
	
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
	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glXSwapBuffers(dpy, win);
	
	sleep(1);
	
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glXSwapBuffers(dpy, win);
	
	sleep(1);
	
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
	glXMakeCurrent(dpy, None, NULL);
	glXDestroyContext(dpy, glc);
	
	XDestroyWindow(dpy, win);	
	XCloseDisplay(dpy);
	
	return 0;
}
