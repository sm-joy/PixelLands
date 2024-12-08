#include "Window.h"
#include <stdio.h>
#include "../Event/Event.h" // IWYU pragma: export

static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

static void cursorPosCallback(GLFWwindow* glfwWindow, double xPos, double yPos) {
	Window* win = (Window*)glfwGetWindowUserPointer(glfwWindow);
	MouseMovedEvent event = {
		.base = {
			.handled = false,
			.type = EVENT_MOUSE_MOVE
		},
		.mouse_posX = xPos,
		.mouse_posY = yPos
	};

	DispatchEvent((Event*)&event);
}

static void windowPosClose(GLFWwindow* window) {
	WindowCloseEvent event = { 
		.type = EVENT_WINDOW_CLOSE, 
		.handled = false
	};
    DispatchEvent((Event*)&event);
}

static void mouseButtonCallback(GLFWwindow* glfwWindow, int button, int action, int mods) {
    Window* win = (Window*)glfwGetWindowUserPointer(glfwWindow);
     MouseButtonPressedEvent event = {
        .base = {
            .handled = false,
            .type = EVENT_MOUSE_PRESS
        },
        .button_code = button,
    };
    DispatchEvent((Event*)&event);
}


static void windowResizeCallback(GLFWwindow* glfwWindow, int width, int height) {
    Window* win = (Window*)glfwGetWindowUserPointer(glfwWindow);
    WindowResizeEvent event = {
        .base = {
            .handled = false,
            .type = EVENT_WINDOW_RESIZE
        },
        .width = width,
        .height = height
    };
    DispatchEvent((Event*)&event);
}

static void scrollCallback(GLFWwindow* glfwWindow, double xOffset, double yOffset) {
    Window* win = (Window*)glfwGetWindowUserPointer(glfwWindow);
    MouseScrollEvent event = {
        .base = {
            .handled = false,
            .type = EVENT_MOUSE_SCROLL
        },
        .scroll_XOffset = xOffset,
        .scroll_YOffset = yOffset
    };
    DispatchEvent((Event*)&event);
}

static void keyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods) {
    Window* win = (Window*)glfwGetWindowUserPointer(glfwWindow);
	if (action == GLFW_PRESS) {
		KeyPressedEvent event = {
			.key_base = {
				.base = {
					.handled = false,
					.type = EVENT_KEY_PRESS
				},
				.key_code = (KeyCode)key
			}
		};
		DispatchEvent((Event*)&event);
	}
	else if (action == GLFW_RELEASE) {
		KeyReleasedEvent event = {
			.key_base = {
				.base = {
					.handled = false,
					.type = EVENT_KEY_RELEASE
				},
				.key_code = (KeyCode)key
			}
		};
		DispatchEvent((Event*)&event);
	}
   
}

static void setGlfwCallBacks(Window* window) {
	glfwSetCursorPosCallback(window->window, cursorPosCallback);
	glfwSetWindowCloseCallback(window->window, windowPosClose);
	glfwSetMouseButtonCallback(window->window, mouseButtonCallback);
    glfwSetKeyCallback(window->window, keyCallback);
    glfwSetScrollCallback(window->window, scrollCallback);
    glfwSetWindowSizeCallback(window->window, windowResizeCallback);
    glfwSetFramebufferSizeCallback(window->window, framebufferResizeCallback);

}


bool CreateWindow(Window *window, const char *title, int width, int height) {
	if (!window || !title) return false;
	if (!(height > 0 && width > 0)) return false;

	window->center_posX = width / 2;
    window->center_posY = height / 2;

	if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	window->window = glfwCreateWindow(width, height, title, NULL, NULL);
	
	if (!window->window)
    {
        fprintf(stderr, "Failed to create GLFW window");
        return false;
    }

    glfwMakeContextCurrent(window->window);
    glViewport(0, 0, width, height);
	glfwSetWindowUserPointer(window->window, window);
	glfwSwapInterval(0);  // Disable vsync
    setGlfwCallBacks(window);


	return true;
}


void TerminateWindow(Window *window) {
	glfwDestroyWindow(window->window);
	glfwTerminate();
}

void UpdateWindow(Window *window) {
	glfwPollEvents();
    glfwSwapBuffers(window->window);
}
