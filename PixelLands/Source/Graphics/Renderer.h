#ifndef RENDERER_H
#define RENDERER_H

#include <GLAD/glad.h>
#include "../Utility/Color.h"
#include <stdbool.h>


typedef struct Renderer {
	GLenum render_clear_flags;
} Renderer;

bool CreateRenderer(Renderer* renderer);
void ClearRender(Renderer* renderer);
void SetRenderClearColor(Color* color);

#endif // RENDERER_H
