#ifndef EX1_2_HELLO_TRIANGLE_1
#define EX1_2_HELLO_TRIANGLE_1
#pragma once

#include "exercise_base.h"
#include <string>
#include <iostream>

class Ex1_2_Hello_Triangle_1 : public ExerciseBase
{
private:
	unsigned int m_shaderProgram;

	unsigned int m_VAO;
	unsigned int m_VBO;

	void prepare() override
	{
		// Prepare the shaders
		// ==============================

		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const char* vertexShaderSource = "\
			#version 330 core\n\
			layout (location = 0) in vec3 aPos;\n\
			\n\
			void main()\n\
			{\n\
				gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n\
			}\n\
		";

		glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
		glCompileShader(vertexShader);

		int vertexShaderCompRes;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderCompRes);

		if (!vertexShaderCompRes)
		{
			char vertexShaderInfoLog[512];
			glGetShaderInfoLog(vertexShader, 512, nullptr, vertexShaderInfoLog);
			std::cout << "Vertex shader compilation error :\n" << vertexShaderInfoLog << std::endl;
			std::cin.ignore();
			exit(EXIT_FAILURE);
		}

		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		const char* m_fragmentShaderSource = "\
			#version 330 core\n\
			out vec4 FragColor;\n\
			\n\
			void main()\n\
			{\n\
				FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n\
			}\n\
		";

		glShaderSource(fragmentShader, 1, &m_fragmentShaderSource, nullptr);
		glCompileShader(fragmentShader);

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

		m_shaderProgram = glCreateProgram();
		glAttachShader(m_shaderProgram, vertexShader);
		glAttachShader(m_shaderProgram, fragmentShader);
		glLinkProgram(m_shaderProgram);

		int shaderProgramLinkRes;
		glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &shaderProgramLinkRes);

		if (!shaderProgramLinkRes)
		{
			char shaderProgramInfoLog[512];
			glGetProgramInfoLog(m_shaderProgram, 512, nullptr, shaderProgramInfoLog);
			std::cout << "Shader program linking error :\n" << shaderProgramInfoLog << std::endl;
			std::cin.ignore();
			exit(EXIT_FAILURE);
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// Prepare the vertex data and its attributes
		// ==============================
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		// Added vertices
		float vertices[18] = {
			-1.0f, -0.5f, 0.0f,
			-0.0f, -0.5f, 0.0f,
			-0.5f, 0.5f,  0.0f,

			0.0f, -0.5f, 0.0f,
			1.0f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(0, GL_ARRAY_BUFFER);
		glBindVertexArray(0);
	}

	void render() override
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(m_shaderProgram);
		glBindVertexArray(m_VAO);

		// Draw 3 more vertices
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void cleanup() override
	{
		glDeleteProgram(m_shaderProgram);
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
	}

public:
	Ex1_2_Hello_Triangle_1()
		: ExerciseBase("Exercise 1.2.1 - Hello Triangle (two triangles, one buffer)")
	{
	}
};

#endif