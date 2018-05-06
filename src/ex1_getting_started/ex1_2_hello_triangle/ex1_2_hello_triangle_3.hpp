#ifndef EX1_2_HELLO_TRIANGLE_3
#define EX1_2_HELLO_TRIANGLE_3

#pragma once
#include "exercise_base.h"
#include <string>
#include <iostream>

class Ex1_2_Hello_Triangle_3 : public ExerciseBase
{
private:
	unsigned int m_shaderProgram1;
	unsigned int m_shaderProgram2;

	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_EBO;

	void prepare() override
	{
		// Prepare the shaders
		// ==============================

		// First shader program
		// ---------------
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

		const char* fragmentShaderSource1 = "\
			#version 330 core\n\
			out vec4 FragColor;\n\
			\n\
			void main()\n\
			{\n\
				FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n\
			}\n\
		";

		glShaderSource(fragmentShader, 1, &fragmentShaderSource1, nullptr);
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

		m_shaderProgram1 = glCreateProgram();
		glAttachShader(m_shaderProgram1, vertexShader);
		glAttachShader(m_shaderProgram1, fragmentShader);
		glLinkProgram(m_shaderProgram1);

		int shaderProgramLinkRes;
		glGetProgramiv(m_shaderProgram1, GL_LINK_STATUS, &shaderProgramLinkRes);

		if (!shaderProgramLinkRes)
		{
			char shaderProgramInfoLog[512];
			glGetProgramInfoLog(m_shaderProgram1, 512, nullptr, shaderProgramInfoLog);
			std::cout << "Shader program linking error :\n" << shaderProgramInfoLog << std::endl;
			std::cin.ignore();
			exit(EXIT_FAILURE);
		}

		// We do not delete the vertex shader since it the same
		glDeleteShader(fragmentShader);
		
		// Second shader program with another fragment shader
		// ---------------
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		const char* fragmentShaderSource2 = "\
			#version 330 core\n\
			out vec4 FragColor;\n\
			\n\
			void main()\n\
			{\n\
				FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n\
			}\n\
		";

		glShaderSource(fragmentShader, 1, &fragmentShaderSource2, nullptr);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShaderCompRes);

		if (!fragmentShaderCompRes)
		{
			char fragmentShaderInfoLog[512];
			glGetShaderInfoLog(fragmentShader, 512, nullptr, fragmentShaderInfoLog);
			std::cout << "Fragment shader compilation error :\n" << fragmentShaderInfoLog << std::endl;
			std::cin.ignore();
			exit(EXIT_FAILURE);
		}

		m_shaderProgram2 = glCreateProgram();
		glAttachShader(m_shaderProgram2, vertexShader);
		glAttachShader(m_shaderProgram2, fragmentShader);
		glLinkProgram(m_shaderProgram2);

		glGetProgramiv(m_shaderProgram2, GL_LINK_STATUS, &shaderProgramLinkRes);

		if (!shaderProgramLinkRes)
		{
			char shaderProgramInfoLog[512];
			glGetProgramInfoLog(m_shaderProgram2, 512, nullptr, shaderProgramInfoLog);
			std::cout << "Shader program linking error :\n" << shaderProgramInfoLog << std::endl;
			std::cin.ignore();
			exit(EXIT_FAILURE);
		}

		// Now delete both
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

		glGenBuffers(1, &m_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

		int elements[6] = { 0, 1, 2, 3, 4, 5 };

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*) 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(0, GL_ARRAY_BUFFER);
		glBindBuffer(0, GL_ELEMENT_ARRAY_BUFFER);
		glBindVertexArray(0);
	}

	void render(float a_deltaTime) override
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(m_VAO);

		glUseProgram(m_shaderProgram1);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glUseProgram(m_shaderProgram2);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*) (sizeof(unsigned int) * 3));
	}

	void cleanup() override
	{
		glDeleteProgram(m_shaderProgram1);
		glDeleteProgram(m_shaderProgram2);
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);
	}

public:
	Ex1_2_Hello_Triangle_3()
		: ExerciseBase("Exercise 1.2.3 - Hello Triangle (two triangles, one buffer, two shaders)")
	{
	}
};

#endif