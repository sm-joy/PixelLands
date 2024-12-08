#include "Texture.h"
#include <stdbool.h>
#include <stdio.h>
#include <GLAD/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <STB_IMAGE/stb_image.h>


static bool texture_stb_vflip = false;

void Texture_Load(Texture* texture, const char* texture_path) {
    if (!texture || !texture_path) return;

    if (!texture_stb_vflip) {
        stbi_set_flip_vertically_on_load(1);
        texture_stb_vflip = true;
    }

    unsigned char* data = stbi_load(texture_path, &texture->width, &texture->height, &texture->nrChannels, 0);
    if (!data) {
        fprintf(stderr, "Failed to load texture");
        return;
    }

    glGenTextures(1, &texture->texture_id);
    glBindTexture(GL_TEXTURE_2D, texture->texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum formate = (texture->nrChannels == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, formate, texture->width, texture->height, 0, formate, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);
}

void Texture_Destroy(Texture* texture) {
    if (!texture) return;
    if (texture->texture_id == 0) return;
    glDeleteTextures(1, &texture->texture_id);
    texture->texture_id = 0;
}