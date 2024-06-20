#pragma once

#include "glad.h"
#include <cstddef>

/**
 * This files contains all the graphic objects
 * to work with and their methods.
 *
 * These includes VAO, VBO, and EBOs.
 * Do note GL is a uses the function paradigm.
 */

/**
 * Vertex Array Object
 */
struct VAO {
    GLuint handle;
};

/**
 * Generate VAO
 * */
VAO genVAO();

/**
 * Demolish
 * */
void destroyVAO(VAO self);

/**
 * Bind VAO
 * */
void bindVAO(VAO self);

void unbindVAO();

/**
 * Set attribute pointers for the BINDING VAO.
 * VAO and VBO MUST BE BOUND!
 * offset is in BYTES!
 */
void vaoAttrib(GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset);

void vaoDisableAttrib(GLuint index);

/**
 * Graphics Buffer Object.
 * Either VBO or EBO.
 */
struct GxBuf {
    GLuint handle;
    GLint type;
    GLenum drawmode;
};

/**
 * Generate FGraphics Buffer.
 * Type: GL_VERTEX_BUFFER, GL_VERTEX_ELEMENT_BUFFER
 * */
GxBuf genGxBuf(GLint type, bool dynamic);

void destroyGxBuf(GxBuf self);

void bindGxBuf(GxBuf self);

/**
 * Also binds.
 * */
void GxBufData(GxBuf self, GLsizeiptr size, const void* data);
