#ifndef HCOMPX_H_
#define HCOMPX_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <X11/X.h>
#include <X11/Xproto.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "xvfbwrapper.h"

//HComp display window
struct HCXDisp {
    Display* main;
    Window parent;
    Window vncview;
    struct Xvfb* xvfb;
};

/*
    1 (parent) - parent window to embed the server in
*/
struct HCXDisp openDisp(Window);

#ifdef __cplusplus
}
#endif

#endif