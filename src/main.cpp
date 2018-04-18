#include <vector>
#include <string>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "cpu/image.hpp"
#include "gpu/image.hpp"
#include "gui/gui.hpp"
#include "raytracer/sphere.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
    const unsigned textureWidth = 1920;
    const unsigned textureHeight = 1080;
    vector<float> pixels;

    vector<Sphere> spheres{
    {
        .radius = .5f,
        .center = {0.f, 0.f, 1.f},
        .color = {0.f, 1.f, 0.f},
    },
    {
        .radius = .25f,
        .center = {.5f, .5f, .8f},
        .color = {1.f, 0.f, 0.f},
    },
    {
        .radius = .5f,
        .center = {.75f, 0.f, 1.1f},
        .color = {0.f, 0.f, 1.f},
    },
    };

    string command{"-h"};
    if (argc == 2)
    {
        command = argv[1];
    }
    if (command == "-h" || command == "--help")
    {
        cout << "Usage: " << argv[0] << " [-c|--cpu|g|--gpu|--help|-h]"
             << endl << endl
             << "--cpu, -c          Run raytracing using CPU" << endl
             << "--gpu, -g          Run raytracing using GPU (OpenCL)" << endl
             << endl;
        return 0;
    }
    else if (command == "-c" || command == "--cpu")
    {
        pixels = createImage(
            textureWidth,
            textureHeight,
            spheres
        );
    }
    else if (command == "-g" || command == "--gpu")
    {
        pixels = clImage(
            textureWidth,
            textureHeight,
            spheres
        );
    }
    else
    {
        cout << "Unknown command " << command
             << endl
             << "Use -h or --help to call help"
             << endl;
        return -1;
    }

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
