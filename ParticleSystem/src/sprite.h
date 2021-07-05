#pragma once

class Sprite
{
private:
	static const float vertices[16];
	unsigned char* texture = nullptr;
public:
	Sprite();
	~Sprite();

	static const float* GetVertices();
};