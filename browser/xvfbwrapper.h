#ifndef XVFB_WRAPPER_H_
#define XVFB_WRAPPER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <X11/Xlib.h>

struct Xvfb {
    Display* output;
};

struct Xvfb initvfb();
struct Xvfb initvfbDefault();
void startvfb(struct Xvfb*);

#ifdef __cplusplus
}
#endif

#endif