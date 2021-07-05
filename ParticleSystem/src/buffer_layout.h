#pragma once
#include <GL/glew.h>
#include <vector>

struct BufferLayoutElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_UNSIGNED_BYTE:	return 1;
		}
		//ASSERT(false);
		return 0;
	}
};

class BufferLayout
{
private:
	std::vector<BufferLayoutElement> elements;
	unsigned int stride;
public:
	BufferLayout() : stride(0) {}

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		elements.push_back({ GL_FLOAT, count, GL_FALSE });
		stride += BufferLayoutElement::GetSizeOfType(GL_FLOAT) * count;
	}	
	
	template<>
	void Push<unsigned int>(unsigned int count)
	{
		elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		stride += BufferLayoutElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}	
	
	template<>
	void Push<unsigned char>(unsigned int count)
	{
		elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
		stride += BufferLayoutElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	std::vector<BufferLayoutElement>& GetElements()
	{
		return elements;
	}

	unsigned int GetStride() const
	{
		return stride;
	}
};