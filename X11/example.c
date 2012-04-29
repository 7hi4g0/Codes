#include<stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
 
int main (int ArgC, char **ArgV)
{
    Display *cdisDisplay;
    int ciScreenNum;
    Screen *cscrScreenPtr;
    XWMHints *xwmhHints;
    XClassHint  *xchClass;
    XTextProperty xtpWinName, xtpIconName;
    XSizeHints *xshSize;
    char *pcIconName = "Icon Name?", *pcWinName = "Window Name?", *pcProgName = "Test App";
    XEvent xeEvent;
    Window Handle;
     
    cdisDisplay = XOpenDisplay(NULL);
    if (cdisDisplay == NULL)
    {//Failed to connect to an X Server
        printf("\nFailed to connect to the display\n");
        return 0;
    }
    else
    {
        ciScreenNum = DefaultScreen(cdisDisplay);
        cscrScreenPtr = DefaultScreenOfDisplay(cdisDisplay);
    }
     
    Handle = XCreateSimpleWindow(cdisDisplay, RootWindow(cdisDisplay, ciScreenNum), 0, 0, 200, 200, 0, BlackPixel(cdisDisplay, ciScreenNum), WhitePixel(cdisDisplay, ciScreenNum));
     
    //Allocate space for the hints
    xshSize = XAllocSizeHints();
    xwmhHints = XAllocWMHints();
    xchClass = XAllocClassHint();
     
    xshSize->flags = PPosition | PSize;
     
    XStringListToTextProperty(&pcWinName, 1, &xtpWinName);
    XStringListToTextProperty(&pcIconName, 1, &xtpIconName);
     
    xwmhHints->initial_state = NormalState;
    xwmhHints->input = True;
    xwmhHints->flags = StateHint | InputHint;
     
    xchClass->res_name = pcProgName;
    xchClass->res_class = "Base Win";
    
    Atom wmDelete=XInternAtom(cdisDisplay, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(cdisDisplay, Handle, &wmDelete, 1);
    
    XSetWMProperties(cdisDisplay, Handle, &xtpWinName, &xtpIconName, 0, NULL, xshSize, xwmhHints, xchClass);
 
    XSelectInput(cdisDisplay, Handle, ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask);
    XMapWindow(cdisDisplay, Handle); //Show the window
    
    int loop = 1;
    
    while (loop)
    {
        XNextEvent(cdisDisplay, &xeEvent);
         
        switch (xeEvent.type)
        {
            case  (ConfigureNotify) :
            {
                printf("Window moved or resized!\n");
                break;
            }
            case (ButtonPress) :
            {
                printf("Mouse button %d pressed!\n", xeEvent.xbutton.button);
                break;
            }
            case (ClientMessage) :
            {
                printf("Window killed!\n");
                loop = 0;
                break;
            }
            default :
            {
                printf("Unknown event: %d (discarding)\n", xeEvent.type);
                break;
            }
        }
    }
}
