#ifndef WINDOW_EVENT_H 
#define WINDOW_EVENT_H

#include "Event.h"

typedef struct {
    Event base;
    int width, height;
} WindowResizeEvent;

typedef struct {
	Event base;
    int x_pos, y_pos;
} WindowMovedEvent;


typedef Event WindowCloseEvent;

typedef Event WindowFocusEvent;

typedef Event WindowLostFocusEvent;


#endif // WINDOW_EVENT_H
