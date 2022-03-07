#ifndef OPENGL_H
#define OPENGL_H

#include <X11/Xlib.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

Window tab1open(Window abcd) {
   Display *d;
   Window w;
   XEvent e;
   const char *msg = "Hello, World!";
   int s;
 
   d = XOpenDisplay(NULL);
   if (d == NULL) {
      fprintf(stderr, "Cannot open display\n");
      exit(1);
   }
 
   s = DefaultScreen(d);
   w = XCreateSimpleWindow(d, abcd, 654, 695, 100, 100, 1,
                           BlackPixel(d, s), WhitePixel(d, s));
   XSelectInput(d, w, ExposureMask | KeyPressMask);
   XMapWindow(d, w);
 
   if (fork() == 0) while (1) {
      XNextEvent(d, &e);
      if (e.type == Expose) {
         XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 10, 10);
         XDrawString(d, w, DefaultGC(d, s), 10, 50, msg, strlen(msg));
      }
      if (e.type == KeyPress)
         break;
   }
 
   return w;
}

#endif // OPENGL_H