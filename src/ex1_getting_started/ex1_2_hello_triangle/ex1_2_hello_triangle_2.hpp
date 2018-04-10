#ifndef EX1_2_HELLO_TRIANGLE_2
#define EX1_2_HELLO_TRIANGLE_2
#pragma once

#include "exercise_base.h"
#include <string>
#include <iostream>

class Ex1_2_Hello_Triangle_2 : public ExerciseBase
{
private:
	unsigned int m_shaderProgram;

	unsigned int m_VAOs[2];
	unsigned int m_VBOs[2];
	unsigned int m_EBO;

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

		// First triangle
		glGenVertexArrays(1, &m_VAOs[0]);
		glBindVertexArray(m_VAOs[0]);

		glGenBuffers(1, &m_VBOs[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[0]);

		float vertices1[9] = {
			-1.0f, -0.5f, 0.0f,
			-0.0f, -0.5f, 0.0f,
			-0.5f, 0.5f,  0.0f,
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

		glGenBuffers(1, &m_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

		int elements[6] = { 0, 1, 2 };

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(0, GL_ARRAY_BUFFER);
		glBindVertexArray(0);

		// Second triangle
		glGenVertexArrays(1, &m_VAOs[1]);
		glBindVertexArray(m_VAOs[1]);

		glGenBuffers(1, &m_VBOs[1]);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[1]);

		float vertices2[9] = {
			0.0f, -0.5f, 0.0f,
			1.0f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(0, GL_ARRAY_BUFFER);
		glBindBuffer(0, GL_ELEMENT_ARRAY_BUFFER);
		glBindVertexArray(0);
	}

	void render() override
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(m_shaderProgram);

		// Bind and draw first triangle
		glBindVertexArray(m_VAOs[0]);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		// And second
		glBindVertexArray(m_VAOs[1]);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	}

	void cleanup() override
	{
		glDeleteProgram(m_shaderProgram);
		glDeleteVertexArrays(2, m_VAOs);
		glDeleteBuffers(2, m_VBOs);
		glDeleteBuffers(1, &m_EBO);
	}

public:
	Ex1_2_Hello_Triangle_2()
		: ExerciseBase("Exercise 1.2.2 - Hello Triangle (two triangles, two buffers)")
	{
	}
};

#endif