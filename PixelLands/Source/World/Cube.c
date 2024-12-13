#include "Cube.h"
#include <GLAD/glad.h>

static unsigned int g_vao = INVALID_BUFFER_OBJECT_ID, g_vbo = INVALID_BUFFER_OBJECT_ID, g_ebo = INVALID_BUFFER_OBJECT_ID;
static bool g_is_cube_bound = false;

void Cube_Create(Cube* cube, vec3 pos) {
    if (!cube) return;

    glm_vec3_copy(pos, cube->pos);

    static const float vertices[] = {
        // Front
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  

        // Back
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  

        // Right
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

        // Left
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  

        // Top
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  

        // Bottom
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f   
    };

    static const unsigned int indices[] = {
        // Front
        0, 1, 2,
        2, 3, 0,

        // Back
        4, 6, 5,
        6, 4, 7,

        // Right
        8, 9, 10,
        10, 11, 8,

        // Left
        12, 14, 13,
        14, 12, 15,

        // Top
        16, 17, 18,
        18, 19, 16,

        // Bottom
        20, 22, 21,
        22, 20, 23
    };

    if (g_vao == INVALID_BUFFER_OBJECT_ID || g_vbo == INVALID_BUFFER_OBJECT_ID || g_ebo == INVALID_BUFFER_OBJECT_ID) {
        glGenVertexArrays(1, &g_vao);
        glGenBuffers(1, &g_vbo);
        glGenBuffers(1, &g_ebo);

        glBindVertexArray(g_vao); 
        glBindBuffer(GL_ARRAY_BUFFER, g_vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_ebo);
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    glmc_mat4_identity(cube->model);
    glmc_translate(cube->model, cube->pos);
}

void Cube_Rotate(Cube* cube, float angle, vec3 axis) {
    if (!cube) return;
    glmc_rotate(cube->model, glm_rad(angle), axis);
}

void Cube_Render(Cube* cube) {
    if (!g_is_cube_bound) {
        glBindVertexArray(g_vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_ebo);
        g_is_cube_bound = true;
    }


    // Sides face
    glBindTexture(GL_TEXTURE_2D, cube->texture_side.texture_id);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(0 * sizeof(unsigned int)));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(6 * sizeof(unsigned int)));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(12 * sizeof(unsigned int)));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(18 * sizeof(unsigned int)));

    // Top face
    glBindTexture(GL_TEXTURE_2D, cube->texture_top.texture_id);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(24 * sizeof(unsigned int)));

    // Bottom face
    glBindTexture(GL_TEXTURE_2D, cube->texture_bottom.texture_id);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(30 * sizeof(unsigned int)));
    glBindTexture(GL_TEXTURE_2D, 0);
}


void Cube_Destroy(Cube* cube) {
    if (g_vao != INVALID_BUFFER_OBJECT_ID) {
        glDeleteVertexArrays(1, &g_vao);
        g_vao = INVALID_BUFFER_OBJECT_ID;
    }
    if (g_vbo != INVALID_BUFFER_OBJECT_ID) {
        glDeleteBuffers(1, &g_vbo);
        g_vbo = INVALID_BUFFER_OBJECT_ID;
    }
    if (g_ebo != INVALID_BUFFER_OBJECT_ID) {
        glDeleteBuffers(1, &g_ebo);
        g_ebo = INVALID_BUFFER_OBJECT_ID;
    }

    Texture_Destroy(&cube->texture_side);
    Texture_Destroy(&cube->texture_top);
    Texture_Destroy(&cube->texture_bottom);
}

void Cube_AddTexture(Cube* cube, TextureFace face, const char* texture_path) {  
    switch (face) {
        case FACE_SIDE: Texture_Load(&cube->texture_side, texture_path);
        case FACE_TOP: Texture_Load(&cube->texture_top, texture_path);
        case FACE_BOTTOM: Texture_Load(&cube->texture_bottom, texture_path);
        case FACE_NONE: default : return;
    }
}