#ifndef EX1_3_SHADERS_1
#define EX1_3_SHADERS_1
#pragma once

#include "../../exercise_base.h"
#include "../../helper/shader_program.h"

class Ex1_3_Shaders_1 : public ExerciseBase
{
private:
	ShaderProgram m_shaderProgram;

	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_EBO;

	void prepare() override
	{
		// Prepare the shader
		// ==============================
		m_shaderProgram = ShaderProgram("./src/ex1_getting_started/ex1_3_shaders/shaders/shader_1.vert", "./src/ex1_getting_started/ex1_3_shaders/shaders/shader_1.frag");

		// Prepare the buffers
		// ==============================

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		float vertices[18] = {
			-0.5f, -0.5f, 0.0f,
			0.0f,  1.0f, 0.0f,
			0.5f, -0.5f, 0.0f,
			1.0f,  0.0f, 0.0f,
			0.0f,  0.5f, 0.0f,
			0.0f,  0.0f, 1.0f,
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &m_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

		unsigned int elements[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*) 0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*) (sizeof(float) * 3));
		glEnableVertexAttribArray(1);

		glBindBuffer(0, GL_ARRAY_BUFFER);
		glBindBuffer(0, GL_ELEMENT_ARRAY_BUFFER);
		glBindVertexArray(0);
	}

	void render() override
	{
		m_shaderProgram.use();
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	}

	void cleanup() override
	{
		m_shaderProgram.release();
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);
	}

public:
	Ex1_3_Shaders_1()
		: ExerciseBase("Exercise 1.3.1 - Shaders")
	{
	}
};

#endif