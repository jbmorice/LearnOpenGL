#ifndef EX1_3_SHADERS
#define EX1_3_SHADERS
#pragma once

#include "exercise_base.h"
#include <iostream>
#include <complex>

class Ex1_3_Shaders : public ExerciseBase
{
private:
	unsigned int m_shaderPrograms[3];
	unsigned int m_currentShaderProgram;

	unsigned int m_VAOs[2];
	unsigned int m_VBOs[2];
	unsigned int m_EBO;

	void prepare() override
	{
		// Prepare the shaders
		// ==============================

		// First shader program with fixed color output from vertex shader
		// ---------------
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Add out member and fill it
		const char* vertexShaderSource1 = "\
			#version 330 core\n\
			layout (location = 0) in vec3 aPos;\n\
			\n\
			out vec4 vertexColor;\
			\n\
			void main()\n\
			{\n\
				gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n\
				vertexColor = vec4(0.5f, 0.0f, 0.0f, 1.0f);\n\
			}\n\
		";

		glShaderSource(vertexShader, 1, &vertexShaderSource1, nullptr);
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

		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Add in member corresponding to the vertex shader
		const char* fragmentShaderSource1 = "\
			#version 330 core\n\
			in vec4 vertexColor;\n\
			\n\
			out vec4 FragColor;\n\
			\n\
			void main()\n\
			{\n\
				FragColor = vertexColor;\n\
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

		m_shaderPrograms[0] = glCreateProgram();
		glAttachShader(m_shaderPrograms[0], vertexShader);
		glAttachShader(m_shaderPrograms[0], fragmentShader);
		glLinkProgram(m_shaderPrograms[0]);

		int shaderProgramLinkRes;
		glGetProgramiv(m_shaderPrograms[0], GL_LINK_STATUS, &shaderProgramLinkRes);

		if (!shaderProgramLinkRes)
		{
			char shaderProgramInfoLog[512];
			glGetProgramInfoLog(m_shaderPrograms[0], 512, nullptr, shaderProgramInfoLog);
			std::cout << "Shader program linking error :\n" << shaderProgramInfoLog << std::endl;
			std::cin.ignore();
			exit(EXIT_FAILURE);
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// Second shader program with dynamic color through uniform in fragment shader
		// ---------------
		vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const char* vertexShaderSource2 = "\
			#version 330 core\n\
			layout (location = 0) in vec3 aPos;\n\
			\n\
			void main()\n\
			{\n\
				gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n\
			}\n\
		";

		glShaderSource(vertexShader, 1, &vertexShaderSource2, nullptr);
		glCompileShader(vertexShader);

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderCompRes);

		if (!vertexShaderCompRes)
		{
			char vertexShaderInfoLog[512];
			glGetShaderInfoLog(vertexShader, 512, nullptr, vertexShaderInfoLog);
			std::cout << "Vertex shader compilation error :\n" << vertexShaderInfoLog << std::endl;
			std::cin.ignore();
			exit(EXIT_FAILURE);
		}

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Add uniform member
		const char* fragmentShaderSource2 = "\
			#version 330 core\n\
			uniform vec4 vertexColor;\n\
			\n\
			out vec4 FragColor;\n\
			\n\
			void main()\n\
			{\n\
				FragColor = vertexColor;\n\
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

		m_shaderPrograms[1] = glCreateProgram();
		glAttachShader(m_shaderPrograms[1], vertexShader);
		glAttachShader(m_shaderPrograms[1], fragmentShader);
		glLinkProgram(m_shaderPrograms[1]);

		glGetProgramiv(m_shaderPrograms[1], GL_LINK_STATUS, &shaderProgramLinkRes);

		if (!shaderProgramLinkRes)
		{
			char shaderProgramInfoLog[512];
			glGetProgramInfoLog(m_shaderPrograms[1], 512, nullptr, shaderProgramInfoLog);
			std::cout << "Shader program linking error :\n" << shaderProgramInfoLog << std::endl;
			std::cin.ignore();
			exit(EXIT_FAILURE);
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// Third shader program with color attributes in vertex buffer going through vertex shader
		// ---------------
		vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Add a new attribute like the position and pass it to fragment shader
		const char* vertexShaderSource3 = "\
			#version 330 core\n\
			layout (location = 0) in vec3 aPos;\n\
			layout (location = 1) in vec3 aCol;\n\
			\n\
			out vec3 vertexColor;\n\
			\n\
			void main()\n\
			{\n\
				gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n\
				vertexColor = aCol;\n\
			}\n\
		";

		glShaderSource(vertexShader, 1, &vertexShaderSource3, nullptr);
		glCompileShader(vertexShader);

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderCompRes);

		if (!vertexShaderCompRes)
		{
			char vertexShaderInfoLog[512];
			glGetShaderInfoLog(vertexShader, 512, nullptr, vertexShaderInfoLog);
			std::cout << "Vertex shader compilation error :\n" << vertexShaderInfoLog << std::endl;
			std::cin.ignore();
			exit(EXIT_FAILURE);
		}

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Get color attribute from vertex shader and use it
		const char* fragmentShaderSource3 = "\
			#version 330 core\n\
			in vec3 vertexColor;\n\
			\n\
			out vec4 FragColor;\n\
			\n\
			void main()\n\
			{\n\
				FragColor = vec4(vertexColor, 1.0f);\n\
			}\n\
		";

		glShaderSource(fragmentShader, 1, &fragmentShaderSource3, nullptr);
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

		m_shaderPrograms[2] = glCreateProgram();
		glAttachShader(m_shaderPrograms[2], vertexShader);
		glAttachShader(m_shaderPrograms[2], fragmentShader);
		glLinkProgram(m_shaderPrograms[2]);

		glGetProgramiv(m_shaderPrograms[2], GL_LINK_STATUS, &shaderProgramLinkRes);

		if (!shaderProgramLinkRes)
		{
			char shaderProgramInfoLog[512];
			glGetProgramInfoLog(m_shaderPrograms[2], 512, nullptr, shaderProgramInfoLog);
			std::cout << "Shader program linking error :\n" << shaderProgramInfoLog << std::endl;
			std::cin.ignore();
			exit(EXIT_FAILURE);
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// Prepare the vertex data and its attributes
		// ==============================

		// Generate the handles
		glGenVertexArrays(2, m_VAOs);
		glGenBuffers(2, m_VBOs);

		// VAO for the first two shader programs
		// ---------------

		glBindVertexArray(m_VAOs[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[0]);

		float vertices1[9] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f,  0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

		glGenBuffers(1, &m_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

		int elements[3] = { 0, 1, 2 };

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(0, GL_ARRAY_BUFFER);
		glBindVertexArray(0);

		// VAO for the third shader program
		// ---------------

		glBindVertexArray(m_VAOs[1]);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[1]);

		// Add 3 floats for the color values after the 3 floats for position (interleaved)
		float vertices2[18] = {
			-0.5f, -0.5f, 0.0f,
			 0.0f,  1.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 1.0f,  0.0f, 0.0f,
			 0.0f,  0.5f, 0.0f,
			 0.0f,  0.0f, 1.0f,
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

		// Remember to change the stride
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*) 0);
		glEnableVertexAttribArray(0);
		// Add and enable the color attribute (corresponding to the "layout (location = ...)"
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*) (sizeof(float) * 3));
		glEnableVertexAttribArray(1);

		glBindBuffer(0, GL_ARRAY_BUFFER);
		glBindBuffer(0, GL_ELEMENT_ARRAY_BUFFER);
		glBindVertexArray(0);

		// Set the first shader as default
		m_currentShaderProgram = m_shaderPrograms[0];
	}

	void render(float a_deltaTime) override
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(m_currentShaderProgram);

		// Special code for the second shader program
		if(m_currentShaderProgram == m_shaderPrograms[1])
		{
			float time = glfwGetTime();
			float green = std::sin(time) / 2.0f + 0.5f;

			// Look for our uniform handle in the currently bound shader program
			int vertexColorLocation = glGetUniformLocation(m_currentShaderProgram, "vertexColor");
			// Use the handle to update the value
			glUniform4f(vertexColorLocation, 0.0f, green, 0.0f, 1.0f);
		}

		// Bind the right buffer to the right shader
		if(m_currentShaderProgram == m_shaderPrograms[2])
		{
			// For the third shader program
			glBindVertexArray(m_VAOs[1]);
		}
		else
		{
			// Fo the two first shader programs
			glBindVertexArray(m_VAOs[0]);
		}

		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	}

	void cleanup() override
	{
		for(int i = 0; i < 3; i++)
		{
			glDeleteProgram(m_shaderPrograms[i]);
		}

		glDeleteVertexArrays(2, m_VAOs);
		glDeleteBuffers(2, m_VBOs);
		glDeleteBuffers(1, &m_EBO);
	}

	void processInput(GLFWwindow* window) override
	{
		ExerciseBase::processInput(m_window);

		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		{
			m_currentShaderProgram = m_shaderPrograms[0];
		}

		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		{
			m_currentShaderProgram = m_shaderPrograms[1];
		}

		if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		{
			m_currentShaderProgram = m_shaderPrograms[2];
		}
	}

public:
	Ex1_3_Shaders()
		: ExerciseBase("Exercise 1.3 - Shaders")
	{
	}
};

#endif