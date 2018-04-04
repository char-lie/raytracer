#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "texture.hpp"

void textureBind(
    const unsigned textureWidth, const unsigned textureHeight,
    const float* pixels, GLuint& texture, GLuint& program,
    GLuint& vertexBuffer, GLint& orthogonalMatrixLocation,
    GLint& textureLocation, GLint& vposLocation)
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_FLOAT, pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void textureInit(
    const GLuint& texture, const GLint& textureLocation,
    const GLuint& vertexBuffer, const GLint& vposLocation)
{
    glUniform1i(textureLocation, 0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glEnableVertexAttribArray(vposLocation);
    glVertexAttribPointer(vposLocation, 2, GL_FLOAT, GL_FALSE,
                          sizeof(float) * 2, (void*) 0);
}
