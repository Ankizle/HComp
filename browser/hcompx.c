#include <string.h>
#include <errno.h>
#include <stdbool.h>

#include <X11/X.h>
#include <X11/Xproto.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <stdlib.h>
#include <unistd.h>

#include "hcompx.h"

struct HCXDisp openDisp(char* progp, Window parent) {
    if (fork() != 0) return;

    struct HCXDisp disp;
    disp.d = XOpenDisplay(NULL);
    disp.vi.screen = DefaultScreen(disp.d);

    Window w = XCreateSimpleWindow(disp.d, parent, 100, 100, 100, 100, 1, BlackPixel(disp.d, disp.vi.screen), WhitePixel(disp.d, disp.vi.screen));

    XSelectInput(disp.d, w, ExposureMask);
    XMapWindow(disp.d, w);

    XEvent e;
    for (;;) {
        XNextEvent(disp.d, &e);
    }

}
