#include "xbg.h"
#include <X11/Xlib.h>
#include <stdio.h>

void SetWindowAsBackground(void *windowHandle) {
    if (!windowHandle) {
        fprintf(stderr, "Invalid window handle!\n");
        return;
    }

    Display *d = XOpenDisplay(NULL);
    if (!d) {
        fprintf(stderr, "Cannot open X display\n");
        return;
    }

    printf("%p\n", windowHandle);

    Window rlwin = (Window)windowHandle;
    Window root = DefaultRootWindow(d);

    XReparentWindow(d, rlwin, root, 0, 0);

    XSetWindowAttributes attrs;
    attrs.override_redirect = True;
    XChangeWindowAttributes(d, rlwin, CWOverrideRedirect, &attrs);

    XMoveResizeWindow(d, rlwin, 0, 0, 500, 500);
    XLowerWindow(d, rlwin); // Push behind all managed windows

    // Map window to make it visible
    XMapWindow(d, rlwin);
    XFlush(d);
}
