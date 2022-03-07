#include <X11/Xlib.h>
#include <stdio.h>
#include <unistd.h>
#include "spawntab.h"

void spawntab(unsigned long long tabid, unsigned long long broid) {

   printf("%d %d\n", tabid, broid);

   Display* display = XOpenDisplay(0);
   
   sleep(3);
   XUnmapWindow(display, tabid);

   sleep(3);
   XReparentWindow(display, tabid, broid, 0, 0);
   XMapWindow(display, tabid);
}