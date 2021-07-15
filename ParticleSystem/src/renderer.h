#pragma once
#include "shader_program.h"
#include <vector>

class Transform;
class Sprite;

class Renderer
{
private:
	unsigned int default_vb;
	unsigned int default_ib;
	unsigned int default_va;
	std::vector<const Sprite*> sprites;
	ShaderProgram default_shader;

	void AssembleData();
public:
	Renderer();
	~Renderer();
	void RegisterSprite(const Sprite* sprite);
	void Draw();
	void BindDefault();
};

