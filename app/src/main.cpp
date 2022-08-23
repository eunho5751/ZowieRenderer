
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

constexpr const char* kWindowTtitle = "Zowie Renderer";
constexpr int kScreenWidth = 800;
constexpr int kScreenHeight = 600;

void WindowResizeCallback(GLFWwindow* pWindow, int width, int height);
void ProcessInput(GLFWwindow* pWindow);
void Render();

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(kScreenWidth, kScreenHeight, kWindowTtitle, nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, WindowResizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window);
        Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void WindowResizeCallback(GLFWwindow* pWindow, int width, int height)
{
    glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* pWindow)
{
    if (glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, true);
    }
}

void Render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

}