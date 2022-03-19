#ifndef HCOMPX_H_
#define HCOMPX_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <X11/X.h>
#include <X11/Xproto.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

//HComp display window
struct HCXDisp {
    Display* d;
    Display* hd;
    XVisualInfo vi;
};

/*
    1 (progp) - program [to execute] path
    2 (parent) - parent window to embed the server in
*/
struct HCXDisp openDisp(char*, Window);

#ifdef __cplusplus
}
#endif

#endif