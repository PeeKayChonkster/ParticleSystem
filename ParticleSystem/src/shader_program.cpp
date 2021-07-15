#include "shader_program.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>
#include <iostream>

ShaderProgram::ShaderProgram(const std::string& file)
	: filepath(file)
{
	const ShaderProgramSource source = ParseShader(file);
	openglID = CreateShaderProgram(source);
	glUseProgram(openglID);
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(openglID);
}

void ShaderProgram::Bind() const
{
	glUseProgram(openglID);
}

void ShaderProgram::Unbind() const
{
	glUseProgram(0);
}

ShaderProgramSource ShaderProgram::ParseShader(const std::string& filepath)
{
	ShaderProgramSource source;
	std::fstream stream(filepath);
	enum ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (std::getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}
	stream.close();
	return { ss[0].str(), ss[1].str() };
}

unsigned int ShaderProgram::CompileShader(const std::string& source, unsigned int type)
{
	unsigned int shader = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);
	int  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	return shader;
}

unsigned int ShaderProgram::CreateShaderProgram(ShaderProgramSource source)
{
	unsigned int vertexShader = CompileShader(source.VertexShaderSource, GL_VERTEX_SHADER);
	unsigned int fragmentShader = CompileShader(source.FragmentShaderSource, GL_FRAGMENT_SHADER);
	unsigned int ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	int success;
	char infoLog[512];
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return ID;
}

void ShaderProgram::SetUniform1i(const std::string& name, int v0)
{
	glUniform1i(GetUniformLocation(name), v0);
}

void ShaderProgram::SetUniform1f(const std::string& name, float v0)
{
	glUniform1f(GetUniformLocation(name), v0);
}

void ShaderProgram::SetUniform2f(const std::string& name, float v0, float v1)
{
	glUniform2f(GetUniformLocation(name), v0, v1);
}

void ShaderProgram::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void ShaderProgram::SetUniformMat3(const std::string& name, const glm::mat3 mat)
{
	glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::SetUniformMat4(const std::string& name, const glm::mat4 mat)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

unsigned int ShaderProgram::GetUniformLocation(const std::string& name)
{
	if (uniformCache.find(name) != uniformCache.end())
		return uniformCache[name];

	int location = glGetUniformLocation(openglID, name.c_str());
	if (location != -1)
		uniformCache[name] = location;
	return location;
}