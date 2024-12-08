#include "EventSystem.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static EventSystem g_event_system = {0};

bool InitEventSystem() {
    memset(&g_event_system, 0, sizeof(EventSystem));
    return true;
}

void ShutdownEventSystem() {
    memset(&g_event_system, 0, sizeof(EventSystem));
}


void BindEventHandler(EventType type, EventHandler handler) {
    if (g_event_system.handler_count[type] < MAX_EVENT_HANDLERS) {
        g_event_system.handlers[type][g_event_system.handler_count[type]] = handler;
        g_event_system.handler_count[type]++;
    } else {
        fprintf(stderr, "Maximum event handlers reached for event type %d!\n", type);
    }
}


void DispatchEvent(Event* event) {

	if (g_event_system.is_processing) return;
	g_event_system.is_processing = true;

    for (int i = 0; i < g_event_system.handler_count[event->type]; i++) {
        g_event_system.handlers[event->type][i](event);
		event->handled = true;
		break;
    }

	g_event_system.is_processing = false;
}

void UnbindEventHandler(EventType type, EventHandler handler) {
    if (type <= EVENT_NONE || type >= EVENT_MAX) return;

    for (int i = 0; i < g_event_system.handler_count[type]; i++) {
        if (g_event_system.handlers[type][i] == handler) {
            
            for (int j = i; j < g_event_system.handler_count[type] - 1; j++) {
                g_event_system.handlers[type][j] = g_event_system.handlers[type][j + 1];
            }
            g_event_system.handler_count[type]--;
            return;
        }
    }
}

/* Event* CreateEvent(EventType type) { */
/*     Event* event = calloc(1, sizeof(Event)); */
/*     if (!event) { */
/*         return NULL; */
/*     } */

/*     event->type = type; */    
/* 	return event; */
/* } */

/* void DestroyEvent(Event* event) { */
/*     if (event) { */
/*         free(event); */
/*     } */
/* } */

bool HasEventHandlers(EventType type) {
    return g_event_system.handler_count[type] > 0;
}
