#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "program.hpp"

static const char* vertexShader_text = R"texture_position(
#version 110
uniform mat4 MVP;
attribute vec2 vPos;
varying vec2 texcoord;
void main()
{
    gl_Position = MVP * vec4(vPos, 0.0, 1.0);
    texcoord = vPos;
}
)texture_position";

static const char* fragmentShader_text = R"texture_color(
#version 110
uniform sampler2D texture;
varying vec2 texcoord;
void main()
{
    gl_FragColor = vec4(texture2D(texture, texcoord).rgb, 1.0);
}
)texture_color";

void createShaders(GLuint& vertexShader, GLuint& fragmentShader)
{
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShader_text, NULL);
    glCompileShader(vertexShader);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShader_text, NULL);
    glCompileShader(fragmentShader);
}

void createProgram(
    GLuint& program, const GLuint& vertexShader, const GLuint& fragmentShader)
{
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
}

void bindData(
    const GLuint& program, GLint& orthogonalMatrixLocation,
    GLint& textureLocation, GLint& vposLocation, GLuint& vertexBuffer)
{
    const float vertices[4][2] =
    {
        { 0.f, 0.f },
        { 1.f, 0.f },
        { 1.f, 1.f },
        { 0.f, 1.f }
    };

    orthogonalMatrixLocation = glGetUniformLocation(program, "MVP");
    textureLocation = glGetUniformLocation(program, "texture");
    vposLocation = glGetAttribLocation(program, "vPos");

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}
