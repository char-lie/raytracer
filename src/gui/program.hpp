void createShaders(GLuint& vertexShader, GLuint& fragmentShader);
void createProgram(
    GLuint& program, const GLuint& vertexShader, const GLuint& fragmentShader);
void bindData(
    const GLuint& program, GLint& orthogonalMatrixLocation,
    GLint& textureLocation, GLint& vposLocation, GLuint& vertexBuffer);
