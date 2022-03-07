#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "openapp.h"

pid_t execute(const char* bin) {
    pid_t pid = fork();
    if (pid == 0) {
        char* const args[] = {"-displayfd", "1", NULL};
        system(bin);
        exit(0);
    } else return pid;
}

//https://stackoverflow.com/q/151407/18385579
void searchpids(Display* display, Window window, Atom atom, pid_t pid, unsigned long long* res) {
    Atom type;
    int format;
    unsigned long nItems;
    unsigned long bytesAfter;
    unsigned char* ppid = 0;
    if (Success == XGetWindowProperty(display, window, atom, 0, 1, False, XA_CARDINAL, &type, &format, &nItems, &bytesAfter, &ppid)) {
        if (ppid != 0) {
            //pid match
            if(pid == *((unsigned long*) ppid)) {
                *res = window;
                return;
            }
            XFree(ppid);
        }
    }

    Window wRoot;
    Window wParent;
    Window* wChild;
    unsigned nChildren;
    if (XQueryTree(display, window, &wRoot, &wParent, &wChild, &nChildren) != 0)
        for (unsigned i = 0; i < nChildren; i++) {
            searchpids(display, wChild[i], atom, pid, res);
            if (*res != 0) return;
        }
}

unsigned long long runprog(const char* path) {
    pid_t pid = execute(path);
    usleep(3e5); //not best practice, but wait for the window to instantiate in the sub program
    Display* display = XOpenDisplay(0);
    unsigned long long sto = 0;
    searchpids(display, XDefaultRootWindow(display), XInternAtom(display, "_NET_WM_PID", True), pid, &sto);
    return sto;
}