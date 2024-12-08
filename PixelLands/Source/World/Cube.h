#ifndef CUBE_H
#define CUBE_H

#include <CGLM/call.h>

#define X_AXIS (vec3){1.0f, 0.0f, 0.0f}
#define Y_AXIS (vec3){0.0f, 1.0f, 0.0f}
#define Z_AXIS (vec3){0.0f, 0.0f, 1.0f}

typedef struct {
    vec3 pos;
    mat4 model;
} Cube;

void Cube_Create(Cube* cube, vec3 pos);
void Cube_Rotate(Cube* cube, float angle, vec3 axis);
void Cube_Render(Cube* cube);

#endif // CUBE_H