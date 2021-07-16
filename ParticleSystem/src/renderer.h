#pragma once
#include "shader_program.h"
#include <vector>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

struct Transform;
class Particle;

class Renderer
{
private:
	GLFWwindow* window;
	glm::mat4 projection;

	unsigned int default_vb;
	unsigned int default_ib;
	unsigned int default_va;

	std::vector<const Particle*> particles;
	ShaderProgram default_shader;

	void AssembleData();
public:
	Renderer(GLFWwindow* window);
	~Renderer();
	void RegisterParticle(const Particle* particle);
	void UnregisterParticle(const Particle* particle);
	void Draw();
	void BindDefault();
	void AdjustVieportSize(GLFWwindow* window, int width, int height);
};

