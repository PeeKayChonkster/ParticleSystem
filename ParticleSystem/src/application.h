#pragma once

#include <exception>


// Window parameters
#define WINDOW_WIDTH 640
#define	WINDOW_HEIGHT 480
#define WINDOW_TITLE "ParticleSystem"


// Error codes
#define INITIALIZATION_ERROR 1
#define WINDOW_CREATION_ERROR 2

class GLFWwindow;

class Application
{
private:
	static int Initialize();


public:
	static GLFWwindow* window;

	Application() = delete;
	Application(const Application& other) = delete;
	Application operator=(const Application& other) = delete;

	static int Run();
};

