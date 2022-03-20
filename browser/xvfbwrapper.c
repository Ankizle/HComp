#include <stdlib.h>
#include <unistd.h>

#include <X11/Xlib.h>

#include "xvfbwrapper.h"

struct Xvfb initvfb(int width, int height, int colordepth) {
    struct Xvfb x;
    x.width = width;
    x.height = height;
    x.colordepth = colordepth;
}

struct Xvfb initvfbDefault() {
    return initvfb(800, 800, 24);
}

void startvfb(struct Xvfb) {
    // if (fork() != 0) return;
    // char* argv[] = {":1", NULL};
    execl("/usr/bin/Xvfb :1", NULL);
}