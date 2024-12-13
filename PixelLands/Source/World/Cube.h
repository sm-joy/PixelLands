#ifndef CUBE_H
#define CUBE_H

#include <CGLM/call.h>
#include "../Graphics/Texture.h"

#define INVALID_BUFFER_OBJECT_ID 0


#define X_AXIS (vec3){1.0f, 0.0f, 0.0f}
#define Y_AXIS (vec3){0.0f, 1.0f, 0.0f}
#define Z_AXIS (vec3){0.0f, 0.0f, 1.0f}

typedef enum {
    FACE_NONE = 0,
    FACE_SIDE,
    FACE_TOP,
    FACE_BOTTOM
} TextureFace;

typedef struct {
    vec3 pos;
    mat4 model;
    Texture texture_side;
    Texture texture_bottom;
    Texture texture_top;
} Cube;

void Cube_Create(Cube* cube, vec3 pos);
void Cube_Rotate(Cube* cube, float angle, vec3 axis);
void Cube_Render(Cube* cube);
void Cube_Destroy(Cube* cube);
void Cube_AddTexture(Cube* cube, TextureFace face, const char* texture_path);

#endif // CUBE_H