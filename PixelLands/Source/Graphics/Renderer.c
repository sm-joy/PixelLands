#include "Renderer.h"
#include <GLFW/glfw3.h>

#include <stdio.h>

bool CreateRenderer(Renderer *renderer) {
	if (!renderer) return false;

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fprintf(stderr, "Failed to initialize GLAD");
        return false;
    }

	renderer->render_clear_flags = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
    glEnable(GL_DEPTH_TEST);
	
	return true;
}

void SetRenderClearColor(Color* color) {
	if (color) glClearColor(color->r, color->g, color->b, color->a);
	else glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void ClearRender(Renderer* renderer) {
    glClear(renderer->render_clear_flags);
}
