#include "renderer.h"
#include "GL/glew.h"
#include "particle.h"
#include "transform.h"
#include "buffer_layout.h"
#include <algorithm>
#include "gtc/matrix_transform.hpp"
#include "application.h"


Renderer::Renderer(GLFWwindow* window) : window(window), default_shader("res/shaders/basic.shader")
{
	projection = glm::ortho(0.0f, (float)Application::GetWindowWidth(), (float)Application::GetWindowHeight(), 0.0f);
	default_shader.Bind();
	default_shader.SetUniformMat4("projection", projection);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

 	glGenBuffers(1, &default_vb);
	glGenBuffers(1, &default_ib);
	glGenBuffers(1, &default_va);
	glBindVertexArray(default_va);
	glBindBuffer(GL_ARRAY_BUFFER, default_vb);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, default_ib);

	BufferLayout layout;
	//glClearColor(1.0f, 0.1f, 0.1f, 1.0f);
	layout.Push<float>(3);	// position
	layout.Push<float>(4); // color
	//layout.Push<float>(2);	// uv
	unsigned int offset = 0;
	const auto& elements = layout.GetElements();
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto &element = elements[i];
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
		glEnableVertexAttribArray(i);
		//onst auto& exAttribArray(i);
		offset += element.count * BufferLayoutElement::GetSizeOfType(element.type);
	}
}

Renderer::~Renderer()
{
	glDeleteBuffers(1, &default_vb);
	glDeleteBuffers(1, &default_va);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Renderer::RegisterParticle(const Particle* particle)
{
	// Need to use positions and textures
	particles.push_back(particle);
}

void Renderer::UnregisterParticle(const Particle* particle)
{
	auto iter = std::find(particles.begin(), particles.end(), particle);
	particles.erase(iter);
}

void Renderer::Draw()
{
	AssembleData();
	glDrawElements(GL_TRIANGLES, particles.size() * 6, GL_UNSIGNED_INT, 0);
}

void Renderer::BindDefault()
{
	glBindVertexArray(default_va);
	default_shader.Bind();
}

void Renderer::AssembleData()
{
	if (particles.size() > 0)
	{
		static std::vector<float> dataVert;
		static std::vector<unsigned int> dataInd;
		std::sort(particles.begin(), particles.end(), [](const Particle* a, const Particle* b) { return a->GetLayer() < b->GetLayer(); });
		dataVert.clear();
		dataInd.clear();

		auto iter = particles.end();

		for(unsigned int i = 0; i < particles.size(); i++)
		{
			float* spriteData = particles[i]->GetData();
			for (int j = 0; j < ELEMENTS_IN_VERTEX; j++)
			{
				dataVert.push_back(*(spriteData + j));
				if (j < 6)
				{
					dataInd.push_back(Particle::indecies[j] + i * 4);
				}
			}
		}
		glBindVertexArray(default_va);
		//glBindBuffer(GL_ARRAY_BUFFER, default_vb);
		glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(float) * ELEMENTS_IN_VERTEX, &dataVert[0], GL_DYNAMIC_DRAW);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, default_ib);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, particles.size() * sizeof(unsigned int) * 6, &dataInd[0], GL_DYNAMIC_DRAW);
	}
}

void Renderer::AdjustVieportSize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f);
	default_shader.Bind();
	default_shader.SetUniformMat4("projection", projection);
}