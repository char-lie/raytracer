void textureBind(
    const unsigned textureWidth, const unsigned textureHeight,
    const float* pixels, GLuint& texture, GLuint& program,
    GLuint& vertex_buffer, GLint& orthogonalMatrixLocation,
    GLint& textureLocation, GLint& vposLocation);
void textureInit(
    const GLuint& texture, const GLint& textureLocation,
    const GLuint& vertexBuffer, const GLint& vposLocation);
