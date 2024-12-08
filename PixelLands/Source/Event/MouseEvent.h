#ifndef MOUSE_EVENT_H
#define MOUSE_EVENT_H

#include "Event.h"


typedef struct {
	Event base;
	int mouse_posX, mouse_posY;
} MouseMovedEvent;

typedef struct {
	Event base;
	int button_code;
} MouseButtonPressedEvent;


typedef struct {
	Event base;
	double scroll_XOffset, scroll_YOffset;
} MouseScrollEvent;


#endif // MOUSE_EVENT_H
