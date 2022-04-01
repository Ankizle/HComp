#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <X11/Xlib.h>
#include <X11/Xmd.h>
#include <X11/keysym.h>
#include <X11/Xatom.h>

#include "hcompx.h"

void openvnc(struct HCXDisp* hx) {
    // Display* maind = (*hx).main;
    // int screen = XDefaultScreen((*hx).main);
    // Window w = XCreateSimpleWindow(
    //     maind,
    //     (*hx).parent,
    //     10, 10, 1000, 1000, 1, 
    //     BlackPixel(maind, screen), WhitePixel(maind, screen)
    // );

    // (*hx).vncview = w; //allow for parent process to access vnc viewer window
    
    // XSelectInput(maind, w, ExposureMask | KeyPressMask);
    // XMapWindow(maind, w);

    if (fork() != 0) return;

    system("vncviewer :0");

}
