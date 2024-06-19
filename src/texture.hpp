#pragma once

#include <string>

struct Texture {
    unsigned int handle;

    int width, height, comps;
};

bool loadTexture(char const *path, struct Texture &texture);

bool loadTexture(char const *path, std::string folder, struct Texture &texture);

void bindTexture(unsigned int slot, struct Texture &texture);

void bindTexture(struct Texture &texture);

void unbindTexture(unsigned int slot);

void setActiveTextureSlot(unsigned int slot);

static void initTextureService();
