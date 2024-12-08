#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>
#include <GLFW/glfw3.h>


typedef struct {
	GLFWwindow* window;
	const char* win_title;
	int win_height, win_width;
	int center_posX, center_posY;	
} Window;

bool CreateWindow(Window* window, const char* title, int width, int height);
void TerminateWindow(Window* window);
void UpdateWindow(Window* window);



#endif // WINDOW_H
