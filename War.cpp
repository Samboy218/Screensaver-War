#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <X11/Xlib.h>
#include <unistd.h>
#include <string.h>
#include "vroot.h"

// the size, in pixels, of each cell
#define CELL_H 5
#define CELL_W 5

//the speed to run at (FPS)
#define FPS_RUN 30

enum valid_colors {
    COLOR_BLACK, COLOR_RED,
    COLOR_GREEN, COLOR_BLUE,
    COLOR_YELLOW, COLOR_MAGENTA,
    COLOR_CYAN, COLOR_WHITE,
    NUM_COLORS
};

int main() 
{
    //Init xlib variables
    Display* dpy;
    Window root;
    GC g;
    XWindowAttributes wa;
    //seed random
    srandom(time(NULL));
    const char* colors[NUM_COLORS] = {"rgb:1d/1f/21", "rgb:cc/66/66", 
                                    "rgb:b5/bd/68", "rgb:81/a2/be",
                                    "rgb:f0/c6/74", "rgb:b2/94/bb", 
                                    "rgb:8a/be/b7", "rgb:c5/c8/c6"};
    XColor xcolors[NUM_COLORS];
    XColor xc, sc;

    //open display
    dpy = XOpenDisplay(getenv("DISPLAY"));

    //get root window
    root = DefaultRootWindow(dpy);

    //get window attributes
    XGetWindowAttributes(dpy, root, &wa);

    //create a graphical context
    g = XCreateGC(dpy, root, 0, NULL);

    //init colors
    for (int i = 0; i<NUM_COLORS; i++) 
    {
        XAllocNamedColor(dpy, 
                        DefaultColormapOfScreen(DefaultScreenOfDisplay(dpy)),
                        colors[i], 
                        &sc, &xc);
        xcolors[i] = sc;
    }

    //set foreground color
    XSetForeground(dpy, g, WhitePixelOfScreen(DefaultScreenOfDisplay(dpy)));

    //now we can make art
    int timeWait = CLOCKS_PER_SEC / FPS_RUN;
    clock_t now;
    clock_t previous = clock();
    
    while(1) 
    {
        now = clock();
        if ((now - previous) < timeWait)
        {
            usleep(timeWait - (now - previous));
        }
        previous = now;

        //Code for one frame here
        //all units decide on what they want to do
        allUnits.plan();
        //all units do their action (how to resolve conflicts?)
        allUnits.act();
        //draw the current state of each army
        allunits.draw();
    }
}
