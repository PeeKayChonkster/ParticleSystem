#pragma once

#include <exception>
#include <vector>
#include <string>


// Window parameters
#define WINDOW_WIDTH 640
#define	WINDOW_HEIGHT 480
#define WINDOW_TITLE "ParticleSystem"


// Error codes
#define INITIALIZATION_ERROR 1
#define WINDOW_CREATION_ERROR 2

struct GLFWwindow;
class Object;

class Application
{
private:
	static float delta;

	static int windowWidth;
	static int windowHeight;
	static std::string windowTitle;

	static int Initialize(int windowWidth, int windowHeight, std::string title);
	static void InvokeCallbacks();
	static void RefreshDelta();
public:
	static GLFWwindow* window;


	Application() = delete;
	Application(const Application& other) = delete;
	Application operator=(const Application& other) = delete;

	static int Run(int windowWidth, int windowHeight, std::string title);

	static inline int GetWindowWidth() { return windowWidth; }
	static inline int GetWindowHeight() { return windowHeight; }
};

