#pragma once
#include "exercise_base.h"
#include <string>
#include <iostream>

class Ex1_2_Hello_Triangle : public ExerciseBase
{
private:
	unsigned int m_shaderProgram;

	unsigned int m_VAO;
	unsigned int m_VBO;

	void prepare() override
	{
		// Prepare the shaders
		// ==============================

		// Create an OpenGL object for the vertex shader
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

		// Attach our source and compile
		glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
		glCompileShader(vertexShader);

		// Check for compilation errors
		int vertexShaderCompRes;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderCompRes);

		if(!vertexShaderCompRes)
		{
			char vertexShaderInfoLog[512];
			glGetShaderInfoLog(vertexShader, 512, nullptr, vertexShaderInfoLog);
			std::cout << "Vertex shader compilation error :\n" << vertexShaderInfoLog << std::endl;
			std::cin.ignore();
			exit(EXIT_FAILURE);
		}

		// Same for the fragment shader
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
		m_shaderProgram = glCreateProgram();
		glAttachShader(m_shaderProgram, vertexShader);
		glAttachShader(m_shaderProgram, fragmentShader);
		glLinkProgram(m_shaderProgram);

		// Check for linking errors
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

		// OpenGL shader objects are not needed anymore and can be destroyed
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// Prepare the vertex data and its attributes
		// ==============================
		// Create an OpenGL Vertex Array Object that will store the description of the content of
		// our Vertex Buffer Object
		glGenVertexArrays(1, &m_VAO);
		// Bind our Vertex Array Object
		glBindVertexArray(m_VAO);

		// Create an OpenGL buffer object to use as our Vertex Buffer Object
		glGenBuffers(1, &m_VBO);
		// Bind our Vertex Buffer Object to the GL_ARRAY_BUFFER slot
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		float vertices[9] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f,  0.5f, 0.0f
		};

		// Send the vertices data to this slot
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// Describe the vertex attributes (how the content of our vertex buffer is organized)
		//		index	   : 0 to bind it to "layout (location = 0)"
		//		size	   : 3 values per vertex (since it is a "vec3")
		//		type	   : of type float (since a "vec3" contains floats)
		//		normalized : do not normalize the data
		//		stride	   : space between vertices is the size of 3 floats
		//		offset	   : offset to where the data begins in the buffer
		//
		// This will register the Buffer Object currently bound to the GL_ARRAY_BUFFER slot as
		// associated to this Vertex Array Object
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*) 0);
		// Activate the vertex attribute we decribed fo "layout (location = 0)"
		glEnableVertexAttribArray(0);

		// Unbind the Vertex Buffer Object and the Vertex Array Object to avoid accidentally
		// modifying them later
		glBindBuffer(0, GL_ARRAY_BUFFER);
		glBindVertexArray(0);
	}

	void render() override
	{
		// Clear our color buffer to black before drawing
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Activate the shader program
		glUseProgram(m_shaderProgram);
		// Bind the VAO (and its subsequent VBO)
		glBindVertexArray(m_VAO);
		// (This could have been done only once during the preparation since we only have one
		// buffer to draw but for normal applications it will have to be done for every different
		// object to draw)

		// The draw call
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	void cleanup() override
	{
		glDeleteProgram(m_shaderProgram);
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
	}

public:
	Ex1_2_Hello_Triangle()
		: ExerciseBase("Exercise 1.2 - Hello Triangle")
	{
	}
};
