#ifndef APPLICATION_H
#define APPLICATION_H

#include "../Graphics/Renderer.h"
#include "../Window/Window.h"
#include "../Utility/Clock.h"



typedef struct {
	Window window;
	Renderer renderer;
	Clock clock;
} Application;


void ApplicationInit(Application* app);
void ApplicationRun(Application* app);
void ApplicationShutdown(Application* app);


#endif // APPLICATION_H
