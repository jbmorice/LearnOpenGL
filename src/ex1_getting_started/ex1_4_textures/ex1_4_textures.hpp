#ifndef EX1_4_TEXTURES
#define EX1_4_TEXTURES
#pragma once

#include "../../exercise_base.h"
#include "../../helper/shader_program.h"
#include "../../thirdparty/stb/stb_image.h"

class Ex1_4_Textures : public ExerciseBase
{
private:
	unsigned int m_crateTexture;

	ShaderProgram m_shaderProgram;

	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_EBO;

	void prepare() override
	{
		// Prepare the shader
		// ==============================
		m_shaderProgram = ShaderProgram("./src/ex1_getting_started/ex1_4_textures/shaders/shader.vert", "./src/ex1_getting_started/ex1_4_textures/shaders/shader.frag");

		// Prepare the buffers
		// ==============================

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		float vertices[] = {
			 0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f,		1.0f, 1.0f, 0.0f,	0.0f, 1.0f
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &m_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

		unsigned int elements[] = { 0, 1, 3, 1, 2, 3 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));
		glEnableVertexAttribArray(2);

		glBindBuffer(0, GL_ARRAY_BUFFER);
		glBindBuffer(0, GL_ELEMENT_ARRAY_BUFFER);
		glBindVertexArray(0);

		// Prepare the texture
		// ==============================
		int width;
		int height;
		int nbChannels;
		unsigned char* data = stbi_load("./resources/container.jpg", &width, &height, &nbChannels, 0);

		if (!data)
		{
			std::cout << "Failed to load image" << std::endl;
			std::cin.ignore();
			return;
		}

		glGenTextures(1, &m_crateTexture); // Generate OpenGL m_crateTexture handle
		glBindTexture(GL_TEXTURE_2D, m_crateTexture); // Bind it to a slot

		// Set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D,			// Target slot
			0,						// Mipmap level
			GL_RGB,				// Storage format on GPU
			width,
			height,
			0,						// Should always be 0
			GL_RGB,				// Source format
			GL_UNSIGNED_BYTE,		// Source datatype
			data
		);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0); // Unbind for safety (not useful here)

		stbi_image_free(data);
	}

	void render() override
	{
		glBindTexture(GL_TEXTURE_2D, m_crateTexture);
		m_shaderProgram.use();
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void cleanup() override
	{
		m_shaderProgram.release();
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);
		glDeleteTextures(1, &m_crateTexture);
	}

public:
	Ex1_4_Textures()
		: ExerciseBase("Exercise 1.3.1 - Shaders")
	{
	}
};

#endif