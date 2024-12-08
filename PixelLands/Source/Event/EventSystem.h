#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include <GLFW/glfw3.h>
#include <stdbool.h>


#define MAX_EVENT_HANDLERS 16

typedef enum {
    EVENT_NONE = 0,

    /* Window Events */
    EVENT_WINDOW_CLOSE,
    EVENT_WINDOW_RESIZE,
    EVENT_WINDOW_FOCUS,

    /* Input Events */
    EVENT_KEY_PRESS,
    EVENT_KEY_RELEASE,
    EVENT_MOUSE_PRESS,
    EVENT_MOUSE_RELEASE,
    EVENT_MOUSE_MOVE,
	EVENT_MOUSE_SCROLL,

    /* Application Events */
    EVENT_APP_START,
    EVENT_APP_STOP,
    EVENT_APP_UPDATE,
    EVENT_APP_RENDER,


    EVENT_MAX
} EventType;


typedef struct Event {
    EventType type;
    bool handled;
} Event;


typedef void (*EventHandler) (Event* event);


typedef struct {
    EventHandler handlers[EVENT_MAX][MAX_EVENT_HANDLERS];
    int handler_count[EVENT_MAX];
	bool is_processing;
} EventSystem;

bool InitEventSystem();
void ShutdownEventSystem();

Event* CreateEvent(EventType type);
void DestroyEvent(Event* event);
bool HasEventHandlers(EventType type);

void BindEventHandler(EventType type, EventHandler handler);
void UnbindEventHandler(EventType type, EventHandler handler);
void DispatchEvent(Event* event);



#endif // EVENT_SYSTEM_H
