#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/Xatom.h>

#include "xvfbwrapper.h"

struct Xvfb initvfb() {
    struct Xvfb x;
    return x;
}

struct Xvfb initvfbDefault() {
    return initvfb(800, 800, 24);
}

void startvfb(struct Xvfb* xv) {
    popen("/usr/bin/Xvfb :1", "r"); //init Xvfb server
    popen("DISPLAY=:1 /usr/bin/fluxbox", "r"); //init the window manager
    popen("/usr/bin/x11vnc -display :1 -bg -forever -nopw -quiet -listen localhost -xkb", "r"); //init x11vnc
    sleep(1);
    (*xv).output = XOpenDisplay(":1");
}