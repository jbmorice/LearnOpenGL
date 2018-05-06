#include "shader_program.h"
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>

ShaderProgram::ShaderProgram(const char* a_vertexShaderCodePath, const char* a_fragmentShaderCodePath) :
	m_vertexShaderCodePath(std::string(a_vertexShaderCodePath)),
	m_fragmentShaderCodePath(std::string(a_fragmentShaderCodePath))
{
	compile();
}

void ShaderProgram::compile()
{
	char result[MAX_PATH];
	std::cout << std::string(result, GetModuleFileName(nullptr, result, MAX_PATH)) << std::endl;

	// Retrieve shader code from files
	std::string vertexShaderCode;
	std::string fragmentShaderCode;
	std::ifstream vertexShaderFile;
	std::ifstream fragmentShaderFile;

	// Ensure ifstreams can throw exceptions
	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// Open files
		vertexShaderFile.open(m_vertexShaderCodePath);
		fragmentShaderFile.open(m_fragmentShaderCodePath);
		// Read their content into streams
		std::stringstream vertexShaderStream;
		std::stringstream fragmentShaderStream;
		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();
		// Close the files
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// Convert streams to strings
		vertexShaderCode = vertexShaderStream.str();
		fragmentShaderCode = fragmentShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Failed to read file : " << e.what() << std::endl;
		std::cin.ignore();
		return;
	}

	// Create an OpenGL object for the vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Attach our source and compile
	const char* vertexShaderSource = vertexShaderCode.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	// Check for compilation errors
	int vertexShaderCompRes;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderCompRes);

	if (!vertexShaderCompRes)
	{
		char vertexShaderInfoLog[512];
		glGetShaderInfoLog(vertexShader, 512, nullptr, vertexShaderInfoLog);
		std::cout << "Vertex shader compilation error :\n" << vertexShaderInfoLog << std::endl;
		std::cin.ignore();
		return;
	}

	// Same for the fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	const char* fragmentShaderSource = fragmentShaderCode.c_str();
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	// Check for compilation errors
	int fragmentShaderCompRes;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShaderCompRes);

	if (!fragmentShaderCompRes)
	{
		char fragmentShaderInfoLog[512];
		glGetShaderInfoLog(fragmentShader, 512, nullptr, fragmentShaderInfoLog);
		std::cout << "Fragment shader compilation error :\n" << fragmentShaderInfoLog << std::endl;
		std::cin.ignore();
		exit(EXIT_FAILURE);
	}

	// Create a shader program and link our shaders
	m_shaderProgramHandle = glCreateProgram();
	glAttachShader(m_shaderProgramHandle, vertexShader);
	glAttachShader(m_shaderProgramHandle, fragmentShader);
	glLinkProgram(m_shaderProgramHandle);

	// Check for linking errors
	int shaderProgramLinkRes;
	glGetProgramiv(m_shaderProgramHandle, GL_LINK_STATUS, &shaderProgramLinkRes);

	if (!shaderProgramLinkRes)
	{
		char shaderProgramInfoLog[512];
		glGetProgramInfoLog(m_shaderProgramHandle, 512, nullptr, shaderProgramInfoLog);
		std::cout << "Shader program linking error :\n" << shaderProgramInfoLog << std::endl;
		std::cin.ignore();
		exit(EXIT_FAILURE);
	}

	// OpenGL shader objects are not needed anymore and can be destroyed
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void ShaderProgram::use()
{
	glUseProgram(m_shaderProgramHandle);
}

void ShaderProgram::setBool(const char* a_name, bool a_value)
{
	glUniform1i(glGetUniformLocation(m_shaderProgramHandle, a_name), a_value);
}

void ShaderProgram::setInt(const char* a_name, int a_value)
{
	glUniform1i(glGetUniformLocation(m_shaderProgramHandle, a_name), (int)a_value);
}

void ShaderProgram::setFloat(const char* a_name, float a_value)
{
	glUniform1f(glGetUniformLocation(m_shaderProgramHandle, a_name), (int)a_value);
}

void ShaderProgram::release()
{
	glDeleteShader(m_shaderProgramHandle);
}
