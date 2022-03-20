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

struct HCXDisp openDisp(char* progp, Window parent) {
    struct Xvfb xs = initvfbDefault();
    startvfb(xs);
}
