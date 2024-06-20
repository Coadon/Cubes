#include <glad/glad.h>

#include "gfxobj.hpp"

struct VAO genVAO() {
    struct VAO self;
    glGenVertexArrays(1, &self.handle);
    return self;
}

void destroyVAO(VAO self) {
    glDeleteVertexArrays(1, &self.handle);
}

void bindVAO(VAO self) {
    glBindVertexArray(self.handle);
}

void unbindVAO() {
    glBindVertexArray(0);
}

void vaoAttrib(GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset) {
    switch (type) {
        case GL_BYTE:
        case GL_UNSIGNED_BYTE:
        case GL_SHORT:
        case GL_UNSIGNED_SHORT:
        case GL_INT:
        case GL_UNSIGNED_INT:
        case GL_INT_2_10_10_10_REV:
        case GL_UNSIGNED_INT_2_10_10_10_REV:
            glVertexAttribIPointer(index, size, type, stride, (void *) offset);
            break;
        default:
            glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void *) offset);
            break;
    }
    glEnableVertexAttribArray(index);
}

void vaoDisableAttrib(GLuint index) {
    glDisableVertexAttribArray(index);
}


struct GxBuf genGxBuf(GLint type, bool dynamic) {
    struct GxBuf self = {
        .type = type,
        .drawmode = static_cast<GLenum>(dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW),
    };
    glGenBuffers(1, &self.handle);
    return self;
}

void destroyGxBuf(struct GxBuf self) {
    glDeleteBuffers(1, &self.handle);
}

void bindGxBuf(struct GxBuf self) {
    glBindBuffer(self.type, self.handle);
}

void GxBufData(GxBuf self, GLsizeiptr size, const void* data) {
    bindGxBuf(self);
    glBufferData(self.type, size, data, self.drawmode);
}

