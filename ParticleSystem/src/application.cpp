#define GLFW_INCLUDE_NONE
#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "application.h"
#include <assert.h>
#include <iostream>
#include "sprite.h"
#include "renderer.h"


GLFWwindow* Application::window = nullptr;

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

int Application::Run()
{
    if (int err = Initialize() != 0) return err;
  
    Renderer renderer;
    Sprite sprite1(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    Sprite sprite2(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
    sprite1.transform.scale *= 0.2f;
    sprite2.transform.scale *= 0.2f;
    sprite2.transform.position.x += 0.5f;
    renderer.RegisterSprite(&sprite1);
    renderer.RegisterSprite(&sprite2);


    /*** MAIN LOOP ***/
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        renderer.Draw();
        if (glfwGetKey(window, GLFW_KEY_D))
        {
            sprite1.transform.position.x += 0.01;
            sprite2.transform.position.x += 0.01;
        }
        if (glfwGetKey(window, GLFW_KEY_A))
        {
            sprite1.transform.position.x -= 0.01;
            sprite2.transform.position.x -= 0.01;
        }
        if (glfwGetKey(window, GLFW_KEY_W))
        {
            sprite1.transform.position.y += 0.01;
            sprite2.transform.position.y += 0.01;
        }
        if (glfwGetKey(window, GLFW_KEY_S))
        {
            sprite1.transform.position.y -= 0.01;
            sprite2.transform.position.y -= 0.01;
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        // Keep running
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

int Application::Initialize()
{
    glfwSetErrorCallback(ErrorCallback);
    if (!glfwInit())
    {
        std::cerr << "GLFW couldn't initialize!" << std::endl;
        glfwTerminate();
        return INITIALIZATION_ERROR;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (!window)
    {
        std::cerr << "Window creation failed! Possible problems with OpenGL context creation. Make sure you have all latest GPU drivers." << std::endl;
        glfwTerminate();
        return WINDOW_CREATION_ERROR;
    }

    glfwSetKeyCallback(window, KeyCallback);

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "GLEW initialization failed!" << std::endl;
        glfwTerminate();
        return INITIALIZATION_ERROR;
    }

    return 0;
}

