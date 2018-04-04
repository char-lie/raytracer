#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "image.hpp"
#include "cl_image.hpp"
#include "gui.hpp"

using std::vector;

int main(void)
{
    const unsigned textureWidth = 1920;
    const unsigned textureHeight = 1080;
    // vector<float> pixels = createImage(textureWidth, textureHeight);
    vector<float> pixels = clImage(textureWidth, textureHeight);
    GLFWwindow* window = createWindow(
        640, 480, pixels.data(), textureWidth, textureHeight);

    while (!glfwWindowShouldClose(window))
    {
        int width, height;

        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        glfwSwapBuffers(window);

        glfwWaitEvents();
    }

    glfwTerminate();
    return 0;
}
