#define GLFW_INCLUDE_NONE
#define GLEW_STATIC

#include "renderer.h"
#include "application.h"
#include <assert.h>
#include <iostream>
#include "particles.h"
#include "object.h"
#include "particle_force.h"
#include "tools.h"
#include "gtc/matrix_transform.hpp"



GLFWwindow* Application::window = nullptr;
Renderer* Application::renderer = nullptr;
int Application::windowWidth = 0;
int Application::windowHeight = 0;
std::string Application::windowTitle = "";
std::chrono::time_point<std::chrono::steady_clock> Application::timePoint1, Application::timePoint2;
float Application::delta = 0.0f;


/** Callbacks **/
void ErrorCallback(int error, const char* description)
{
    std::cerr << "Error: " << error << "; Description: " << description << std::endl;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void WindowSizeCallback(GLFWwindow* window, int width, int height)
{
    Application::SetWindowSize(width, height);
    Application::renderer->AdjustVieportSize(window, width, height);
}


int Application::Run(int windowWidth, int windowHeight, std::string title)
{
    if (int err = Initialize(windowWidth, windowHeight, title) != 0) return err;
    
    Renderer newRenderer(window);
    renderer = &newRenderer;
    Particles particles(renderer);

    double mouseX, mouseY;

    Transform transform;
    transform.scale = glm::vec2(50.0f);

    glm::vec4 color1(1.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 color2(0.0f, 1.0f, 0.0f, 1.0f);

    ParticleForce force(glm::vec2(50.f, 50.f));

    particles.AddEffect(reinterpret_cast<ParticleEffect*>(&force));

    /*** MAIN LOOP ***/
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwGetCursorPos(window, &mouseX, &mouseY);

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
        {
            transform.position = glm::vec2(mouseX, mouseY);
            //particles.SetLayer(-1);
            particles.CreateParticle(transform, color1);
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
        {
            transform.position = glm::vec2(mouseX, mouseY);
           // particles.SetLayer(1);
            particles.CreateParticle(transform, color2);
        }

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            color1 = Tools::RandomColor(false);
            color2 = Tools::RandomColor(false);
        }

        particles.Update();

        renderer->Draw();


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        // Keep running
        glfwPollEvents();

        RefreshDelta();
    }

    glfwTerminate();
    return 0;
}


int Application::Initialize(int width, int height, std::string title)
{
    timePoint1 = std::chrono::steady_clock::now();

    srand(static_cast<unsigned>(time(0)));     // randomize

    glfwSetErrorCallback(ErrorCallback);
    if (!glfwInit())
    {
        std::cerr << "GLFW couldn't initialize!" << std::endl;
        glfwTerminate();
        return INITIALIZATION_ERROR;
    }

    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    windowWidth = width;
    windowHeight = height;
    windowTitle = title;

    window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), NULL, NULL);
    if (!window)
    {
        std::cerr << "Window creation failed! Possible problems with OpenGL context creation. Make sure you have all latest GPU drivers." << std::endl;
        glfwTerminate();
        return WINDOW_CREATION_ERROR;
    }


    glfwSetKeyCallback(window, KeyCallback);

    glfwSetWindowSizeCallback(window, WindowSizeCallback);

    glfwMakeContextCurrent(window);

    glfwSwapInterval(0);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "GLEW initialization failed!" << std::endl;
        glfwTerminate();
        return INITIALIZATION_ERROR;
    }


    return 0;
}

void Application::InvokeCallbacks()
{
}

void Application::RefreshDelta()
{
    timePoint2 = std::chrono::steady_clock::now();
    std::chrono::duration<float> duration = timePoint2 - timePoint1;
    delta = duration.count();
    timePoint1 = timePoint2;
}

