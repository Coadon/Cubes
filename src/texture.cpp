#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include "stb/std_image.h"
#include "common.hpp"
#include "texture.hpp"

bool loadTexture(char const *path, struct Texture &texture) {
    glGenTextures(1, &texture.handle);

    u8 *data =
        stbi_load(path, &texture.width, &texture.height, &texture.comps, 0);

    if (!data) {
        LOGGER.error("Texture failed to load at path: {}", path);
        stbi_image_free(data);
        return 0;
    }

    GLenum format;
    switch (texture.comps) {
    case 1:
        format = GL_RED;
        break;
    case 3:
        format = GL_RGB;
        break;
    case 4:
        format = GL_RGBA;
        break;
    default:
        LOGGER.error("Texture have an unfamiliar color channels count '{0}' at path: {1}", texture.comps, path);
        stbi_image_free(data);
        return 0;
    }

    glBindTexture(GL_TEXTURE_2D, texture.handle);
    glTexImage2D(GL_TEXTURE_2D, 0, format, texture.width, texture.height, 0,
                 format, GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);

    return true;
}

bool loadTexture(const char *path, std::string folder, struct Texture &texture) {
    return loadTexture((folder + "/" + path).c_str(), texture);
}

void bindTexture(unsigned int slot, struct Texture &texture) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, texture.handle);
}

void bindTexture(struct Texture &texture) {
    glBindTexture(GL_TEXTURE_2D, texture.handle);
}

void unbindTexture(unsigned int slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void setActiveTextureSlot(unsigned int slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
}

static void initTextureService() {
    // Make sure stb flips the images loaded cause they are flipped
    // by nature
    stbi_set_flip_vertically_on_load(true);
}

