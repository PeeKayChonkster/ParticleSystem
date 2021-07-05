#pragma once
#include <string>
#include <unordered_map>
#include "glm.hpp"

struct ShaderProgramSource
{
	std::string VertexShaderSource;
	std::string FragmentShaderSource;
};

class ShaderProgram
{
private:
	const std::string filepath;
	unsigned int openglID;
	std::unordered_map<std::string, int> uniformCache;

	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CreateShaderProgram(ShaderProgramSource source);
	unsigned int CompileShader(const std::string& source, unsigned int type);
	unsigned int GetUniformLocation(const std::string& name);
public:
	ShaderProgram(const std::string& file);
	~ShaderProgram();
	
	void SetUniform1i(const std::string& name, int v0);
	void SetUniform1f(const std::string& name, float v0);
	void SetUniform2f(const std::string& name, float v0, float v1);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4(const std::string& name, const glm::mat4 mat);

	void Bind() const;
	void Unbind() const;
};

