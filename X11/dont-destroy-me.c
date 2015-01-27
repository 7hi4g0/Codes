    /*
     * dont-destroy-me.c - WM_DELETE_WINDOW experiment.
     * Copyright (C) 2009 Michael B. Trausch <mike@trausch.us>
     *
     * Determines what happens when you click the �X� on a window in a
     * given window manager.
     */
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
     
    #include <X11/Xlib.h>
    #include <X11/Xatom.h>
     
    #define RETVAL_SUCCESS 0
    #define RETVAL_NO_X11_DISPLAY 1
     
    int
    main(int argc, char *argv[]) {
      Display *d = XOpenDisplay(NULL);
      int wm_close_count = 0;
      XEvent xev;
     
      if(d == NULL) {
        fprintf(stderr, "Unable to open DISPLAY. Cannot continue.\n");
        exit(RETVAL_NO_X11_DISPLAY);
      }
     
      Window w = XCreateSimpleWindow(d, DefaultRootWindow(d), 0, 0,
                                     400, 400, 0, 0, 0);
      fprintf(stdout, "Created window %ld.\n", w);
     
      Atom _wm_delete_window = XInternAtom(d, "WM_DELETE_WINDOW", False);
      XSetWMProtocols(d, w, &_wm_delete_window, 1);
      XMapWindow(d, w);
     
      memset(&xev, 0, sizeof(XEvent));
      while(1) {
        XNextEvent(d, &xev);
     
        if((xev.type == ClientMessage) &&
           (xev.xclient.data.l[0] == _wm_delete_window)) {
          if(++wm_close_count < 10) {
            fprintf(stdout, "Received a WM_DELETE_WINDOW message. Ignoring it.\n");
          } else {
            fprintf(stdout, "Closing on WM_DELETE_WINDOW.\n");
            break;
          }
        } else {
          fprintf(stdout, "Received an unhandled ClientMessage event.\n");
        }
      }
     
      XCloseDisplay(d);
      return(RETVAL_SUCCESS);
    }

