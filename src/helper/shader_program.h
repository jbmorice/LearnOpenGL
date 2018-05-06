#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H
#pragma once

#include <string>

class ShaderProgram
{
private:
	std::string m_vertexShaderCodePath;
	std::string m_fragmentShaderCodePath;
	unsigned int m_shaderProgramHandle;

public:
	ShaderProgram() = default;
	ShaderProgram(const char* a_vertexShaderCodePath, const char* a_fragmentShaderCodePath);

	void compile();
	void use();

	void setBool(const char* a_name, bool a_value);
	void setInt(const char* a_name, int a_value);
	void setFloat(const char* a_name, float a_value);

	void release();
};

#endif