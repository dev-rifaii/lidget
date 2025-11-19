#define GLFW_EXPOSE_NATIVE_X11

#include "xbg.h"
#include <X11/Xlib.h>
#include <stdio.h>

void SetWindowAsBackground(void *windowHandle) {
    const XID windowId = *(XID *)windowHandle;
    const Window x11Window = windowId;
    Display *d = XOpenDisplay(NULL);

    if (!d) {
        fprintf(stderr, "Cannot open X display\n");
        return;
    }

    Window root = DefaultRootWindow(d);

    // Override redirect so WM ignores it
    XSetWindowAttributes attrs;
    attrs.override_redirect = True;
    XChangeWindowAttributes(d, x11Window, CWOverrideRedirect, &attrs);

    XReparentWindow(d, x11Window, root, 0, 0);

    // Resize to fill screen
    XWindowAttributes rootAttrs;
    XGetWindowAttributes(d, root, &rootAttrs);
    XMoveResizeWindow(d, x11Window, 0, 0, rootAttrs.width, rootAttrs.height);

    XMapWindow(d, x11Window);

    XLowerWindow(d, x11Window);

    XFlush(d);
}
