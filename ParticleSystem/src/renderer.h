#pragma once
#include "shader_program.h"

class Transform;
class Sprite;

class Renderer
{
private:
	unsigned int default_vb;
	//unsigned int default_ib;
	unsigned int default_va;
	ShaderProgram default_shader;
public:
	Renderer();
	~Renderer();
	void RegisterSprite(Sprite sprite, Transform transform);
	void Draw();
	void BindDefault();
};

