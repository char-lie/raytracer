#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "texture.hpp"
#include "program.hpp"
#include "gui.hpp"

GLFWwindow* createWindow(
    const unsigned width, const unsigned height,
    const float* pixels,
    const unsigned textureWidth, const unsigned textureHeight)
{
    GLFWwindow* window;
    GLuint texture;
    GLuint program;
    GLuint vertexBuffer;
    GLuint vertexShader;
    GLuint fragmentShader;
    GLint orthogonalMatrixLocation;
    GLint vposLocation;
    GLint textureLocation;

    if (!glfwInit())
    {
        return nullptr;
    }

    window = glfwCreateWindow(width, height, "Raytracing", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    createShaders(vertexShader, fragmentShader);
    createProgram(program, vertexShader, fragmentShader);
    bindData(
        program,
        orthogonalMatrixLocation, textureLocation, vposLocation, vertexBuffer);

    glUseProgram(program);

    const GLfloat orthogonalMatrix[4][4] = {
        { 2.f,  0.f,  0.f, 0.f},
        { 0.f,  2.f,  0.f, 0.f},
        { 0.f,  0.f,  2.f, 0.f},
        {-1.f, -1.f, -1.f, 1.f},
    };
    glUniformMatrix4fv(
        orthogonalMatrixLocation, 1, GL_FALSE, (GLfloat*)orthogonalMatrix);

    textureBind(
        textureWidth, textureHeight, pixels,
        texture, program, vertexBuffer,
        orthogonalMatrixLocation, textureLocation, vposLocation);
    textureInit(texture, textureLocation, vertexBuffer, vposLocation);

    return window;
}
