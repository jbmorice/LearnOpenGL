#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H
#pragma once

#include <string>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class ShaderProgram
{
private:
	std::string m_vertexShaderCodePath;
	std::string m_fragmentShaderCodePath;
	unsigned int m_shaderProgramHandle;

public:
	ShaderProgram() = default;
	ShaderProgram(const char* a_vertexShaderCodePath, const char* a_fragmentShaderCodePath);

	unsigned int getHandle() const;

	void setBool(const char* a_name, bool a_value);
	void setInt(const char* a_name, int a_value);
	void setFloat(const char* a_name, float a_value);
	void setMatrix4x4f(const char* a_name, glm::mat4x4& a_matrix);

	void compile();
	void use();

	void release();
};

#endif