#include "renderer.h"
#include "GL/glew.h"
#include "sprite.h"
#include "transform.h"
#include "buffer_layout.h"


Renderer::Renderer() : default_shader("res/shaders/basic.shader")
{
	default_shader.Bind();
 	glGenBuffers(1, &default_vb);
	glGenBuffers(1, &default_ib);
	glGenBuffers(1, &default_va);
	glBindVertexArray(default_va);
	glBindBuffer(GL_ARRAY_BUFFER, default_vb);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, default_ib);
	BufferLayout layout;
	glClearColor(1.0f, 0.1f, 0.1f, 1.0f);
	layout.Push<float>(3);	// position
	layout.Push<float>(4); // color
	//layout.Push<float>(2);	// uv
	unsigned int offset = 0;
	const auto& elements = layout.GetElements();
	for (int i = 0; i < elements.size(); i++)
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

void Renderer::RegisterSprite(const Sprite* sprite)
{
	// Need to use positions and textures
	sprites.push_back(sprite);
}

void Renderer::Draw()
{
	glBindVertexArray(default_va);
	AssembleData();
	glDrawElements(GL_TRIANGLES, sprites.size() * 6, GL_UNSIGNED_INT, 0);
}

void Renderer::BindDefault()
{
	glBindVertexArray(default_va);
	default_shader.Bind();
}

void Renderer::AssembleData()
{
	static std::vector<float> dataVert;
	static std::vector<unsigned int> dataInd;
	dataVert.clear();
	dataInd.clear();
	for (int i = 0; i < sprites.size(); i++)
	{
		float* spriteData = sprites[i]->GetData();
		for (int j = 0; j < ELEMENTS_IN_VERTEX; j++)
		{
			dataVert.push_back(*(spriteData + j));
		}
		for (int i = 0; i < sprites.size(); i++)
		{
			for (int j = 0; j < 6; j++)
			{
				dataInd.push_back(Sprite::indecies[j] + i * 4);
			}
		}
	}
	glBindVertexArray(default_va);
	//glBindBuffer(GL_ARRAY_BUFFER, default_vb);
	glBufferData(GL_ARRAY_BUFFER, sprites.size() * sizeof(float) * ELEMENTS_IN_VERTEX, &dataVert[0], GL_DYNAMIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, default_ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sprites.size() * sizeof(unsigned int) * 6, &dataInd[0], GL_DYNAMIC_DRAW);
}