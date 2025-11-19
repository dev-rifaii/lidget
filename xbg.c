#define GLFW_EXPOSE_NATIVE_X11

#include "xbg.h"
#include <X11/Xlib.h>
#include <stdio.h>
#include <glfw3.h>
#include <glfw3native.h>

void SetWindowAsBackground(void *windowHandle) {
    XID windowId = *(XID *)windowHandle;
    Window x11Window = windowId;
    Display *d = XOpenDisplay(NULL);

    if (!d) {
        fprintf(stderr, "Cannot open X display\n");
        return;
    }

    Window root = DefaultRootWindow(d);

    XReparentWindow(d, x11Window, root, 0, 0);

    XSetWindowAttributes attrs;
    attrs.override_redirect = True;
    XChangeWindowAttributes(d, x11Window, CWOverrideRedirect, &attrs);

    XMoveResizeWindow(d, x11Window, 0, 0, 500, 500);
    XLowerWindow(d, x11Window); // Push behind all managed windows
    // Map window to make it visible
    XMapWindow(d, x11Window);

    XFlush(d);
}
