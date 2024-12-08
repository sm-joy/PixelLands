#ifndef TEXTURE_H
#define TEXTURE_H


typedef struct {
    unsigned int texture_id;
	int width, height, nrChannels;
} Texture;

void Texture_Load(Texture* texture, const char* texture_path);
void Texture_Destroy(Texture* texture);

#endif // TEXTURE_H