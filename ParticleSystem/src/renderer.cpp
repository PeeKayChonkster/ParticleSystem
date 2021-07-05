#include "renderer.h"
#include "GL/glew.h"
#include "sprite.h"
#include "transform.h"
#include "buffer_layout.h"

Renderer::Renderer() : default_shader("res/shader/basic.shader")
{
	glGenBuffers(1, &default_vb);
	//glGenBuffers(1, &default_ib);
	glGenBuffers(1, &default_va);
	glBindVertexArray(default_va);
	glBindBuffer(GL_ARRAY_BUFFER, default_vb);
	BufferLayout layout;
	layout.Push<float>(2);	// position
	layout.Push<float>(2);	// uv
	unsigned int offset = 0;
	const auto& elements = layout.GetElements();
	for (int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements [i] ;
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
		glEnableVertexAttribArray(i);
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

void Renderer::RegisterSprite(Sprite sprite, Transform transform)
{
	// Need to use positions and textures
	glBindVertexArray(default_va);
	glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), Sprite::GetVertices(), GL_STATIC_DRAW);
}

void Renderer::Draw()
{
}

void Renderer::BindDefault()
{
	glBindVertexArray(default_va);
	default_shader.Bind();
}
