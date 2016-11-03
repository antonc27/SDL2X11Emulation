//
// Created by Sebastian on 08.10.2016.
//

#ifndef WINDOWINTERNAL_H
#define WINDOWINTERNAL_H

#include "window.h"

typedef struct _WindowSdlIdMapper {
    Window window;
    Uint32 sdlWindowId;
    struct _WindowSdlIdMapper* next;
} WindowSdlIdMapper;

void initWindowStruct(WindowStruct* windowStruct, int x, int y, unsigned int width, unsigned int height,
                      Visual* visual, Colormap colormap, Bool inputOnly,
                      unsigned long backgroundColor, Pixmap backgroundPixmap);
Bool initScreenWindow(Display* display);
Window getWindowFromId(Uint32 sdlWindowId);
void destroyScreenWindow(Display* display);
void destroyWindow(Display* display, Window window, Bool freeParentData);
Window getContainingWindow(Window window, int x, int y);
Bool addChildToWindow(Window parent, Window child);
void removeChildFromParent(Window child);
Bool resizeWindowSurface(Window window);
void registerWindowMapping(Window window, Uint32 sdlWindowId);
Bool isParent(Window window1, Window window2);
WindowProperty* increasePropertySize(WindowProperty* properties, unsigned int currSize,
                                     unsigned int* newSize);
WindowProperty* findProperty(WindowProperty* properties, unsigned int numProperties, Atom property);
Bool mergeWindowDrawables(Window parent, Window child);
Window enqueueMapEvent(Display* display, Window window, Window parentWithSubstructureRedirect,
                       Bool searchForSRParent);
Window getParentWithEventBit(Window window, long eventBit);
void mapRequestedChildren(Display* display, Window window, Window subStructureRedirectParent);

#endif /* WINDOWINTERNAL_H */