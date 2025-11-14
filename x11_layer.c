#include <X11/Xlib.h>
#include <X11/Xatom.h>

void set_override_redirect(Display *d, Window w) {
    XSetWindowAttributes attr = {0};
    attr.override_redirect = True;

    XChangeWindowAttributes(d, w, CWOverrideRedirect, &attr);
    XMapWindow(d, w);
    XFlush(d);
}

