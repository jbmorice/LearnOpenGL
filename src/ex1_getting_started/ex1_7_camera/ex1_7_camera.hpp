#ifndef EX1_7_CAMERA
#define EX1_7_CAMERA
#pragma once

#include "../../exercise_base.h"
#include "../../helper/shader_program.h"
#include "../../helper/camera.h"

#include <vector>

class Ex1_7_Camera : public ExerciseBase
{
private:
	unsigned int m_crateTexture;
	unsigned int m_smileyTexture;

	ShaderProgram m_shaderProgram;

	unsigned int m_VAO;
	unsigned int m_VBO;

	glm::mat4x4 m_model;
	glm::mat4x4 m_view;
	glm::mat4x4 m_projection;

	std::vector<glm::vec3> m_cubePositions;

	Camera m_camera;

	bool m_firstMouse = true;
	float m_lastX = m_windowWidth / 2;
	float m_lastY = m_windowHeight / 2;

	void prepare() override
	{
		//Callbacks
		// ==============================
		// Store a pointer to this object in glfw to use as a reference in the static callback functions
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetWindowUserPointer(m_window, this);

		// Set mouse callbacks for camera
		glfwSetCursorPosCallback(m_window, glfwCursorPosCallback);
		glfwSetScrollCallback(m_window, glfwScrollCallback);

		// Prepare the shader
		// ==============================
		m_shaderProgram = ShaderProgram("./src/ex1_getting_started/ex1_6_coordinate_systems/shaders/shader.vert", "./src/ex1_getting_started/ex1_6_coordinate_systems/shaders/shader.frag");

		// Asign texture samplers to texture units
		m_shaderProgram.use();
		m_shaderProgram.setInt("mainTexture", 0);
		m_shaderProgram.setInt("secondaryTexture", 1);

		// Prepare the buffers
		// ==============================

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		float vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
		glEnableVertexAttribArray(1);

		glBindBuffer(0, GL_ARRAY_BUFFER);
		glBindVertexArray(0);

		// Prepare the textures
		// ==============================
		// Crate texture
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

		glTexImage2D(GL_TEXTURE_2D,	// Target slot
			0,						// Mipmap level
			GL_RGB,					// Storage format on GPU
			width,
			height,
			0,						// Should always be 0
			GL_RGB,					// Source format
			GL_UNSIGNED_BYTE,		// Source datatype
			data
		);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0); // Unbind for safety (not useful here)

		stbi_image_free(data);

		// Smiley texture
		stbi_set_flip_vertically_on_load(true);
		data = stbi_load("./resources/awesomeface.png", &width, &height, &nbChannels, 0);

		if (!data)
		{
			std::cout << "Failed to load image" << std::endl;
			std::cin.ignore();
			return;
		}

		glGenTextures(1, &m_smileyTexture); // Generate OpenGL m_crateTexture handle
		glBindTexture(GL_TEXTURE_2D, m_smileyTexture); // Bind it to a slot

		// Set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D,	// Target slot
			0,						// Mipmap level
			GL_RGB,					// Storage format on GPU
			width,
			height,
			0,						// Should always be 0
			GL_RGBA,				// Source format
			GL_UNSIGNED_BYTE,		// Source datatype
			data
		);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0); // Unbind for safety (not useful here)

		stbi_image_free(data);

		// Camera
		// ==============================
		m_camera = glm::vec3(0.0f, 0.0f, 3.0f);

		// Cubes
		// ==============================
		m_cubePositions = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		// Enable depth testing
		glEnable(GL_DEPTH_TEST);
	}

	void processInput(GLFWwindow* window) override
	{
		ExerciseBase::processInput(m_window);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			m_camera.processKeyboard(Camera::Movement::FORWARD, m_deltaTime);
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			m_camera.processKeyboard(Camera::Movement::BACKWARD, m_deltaTime);
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			m_camera.processKeyboard(Camera::Movement::LEFT, m_deltaTime);
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			m_camera.processKeyboard(Camera::Movement::RIGHT, m_deltaTime);
		}
	}

	static void glfwCursorPosCallback(GLFWwindow* a_window, double a_xpos, double a_ypos)
	{
		Ex1_7_Camera* ptr = (Ex1_7_Camera*)glfwGetWindowUserPointer(a_window);

		if (ptr->m_firstMouse)
		{
			ptr->m_lastX = a_xpos;
			ptr->m_lastY = a_ypos;
			ptr->m_firstMouse = false;
		}

		float xoffset = a_xpos - ptr->m_lastX;
		float yoffset = ptr->m_lastY - a_ypos;
		ptr->m_lastX = a_xpos;
		ptr->m_lastY = a_ypos;

		ptr->m_camera.processMousePosition(xoffset, yoffset);
	}

	static void glfwScrollCallback(GLFWwindow* a_window, double a_xoffset, double a_yoffset)
	{
		Ex1_7_Camera* ptr = (Ex1_7_Camera*)glfwGetWindowUserPointer(a_window);
		ptr->m_camera.processMouseScroll(a_xoffset, a_yoffset);
	}

	void render(float a_deltaTime) override
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Bind the textures to their units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_crateTexture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_smileyTexture);

		m_shaderProgram.use();
		glBindVertexArray(m_VAO);

		m_view = m_camera.getViewMatrix();
		m_shaderProgram.setMatrix4x4f("view", m_view);

		m_projection = m_camera.getPerspectiveProjectionMatrix(getWindowWidth(), getWindowHeight());
		m_shaderProgram.setMatrix4x4f("projection", m_projection);

		for (int i = 0; i < m_cubePositions.size(); i++)
		{
			// Update matrices
			m_model = glm::mat4x4(1.0f);
			m_model = glm::translate(m_model, m_cubePositions[i]);
			m_model = glm::rotate(m_model, i * glm::radians(20.0f), glm::vec3(1.0f, 0.3f, 0.5f));

			m_shaderProgram.setMatrix4x4f("model", m_model);

			// Render
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}

	void cleanup() override
	{
		glfwSetWindowUserPointer(m_window, nullptr);
		m_shaderProgram.release();
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteTextures(1, &m_crateTexture);
		glDeleteTextures(1, &m_smileyTexture);
	}

public:
	Ex1_7_Camera()
		: ExerciseBase("Exercise 1.7 - Camera")
	{
	}
};

#endif