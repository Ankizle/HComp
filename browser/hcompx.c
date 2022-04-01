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
#include "xvfbwrapper.h"
#include "vnc.h"

struct HCXDisp openDisp(Window parent) {

    struct HCXDisp hx;
    hx.parent = parent;

    hx.main = XOpenDisplay(NULL);

    struct Xvfb xs = initvfbDefault();
    startvfb(&xs);
    hx.xvfb = &xs;

    openvnc(&hx);
    return hx;
}
