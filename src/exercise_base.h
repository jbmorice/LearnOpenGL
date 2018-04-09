#ifndef EXERCISE_BASE_H
#define EXERCISE_BASE_H
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ExerciseBase
{
protected:
	GLFWwindow * m_window;
	int m_windowWidth, m_windowHeight;
	const char* m_windowName;

	// Callback function to print GLFW errors in console
	static void gflwErrorCallback(int error, const char* description);

	// Callback function to adapt OpenGL viewport according to the GLFW window
	static void glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height);

	// Function called at the beginning of the main loop to handle inputs
	virtual void processInput(GLFWwindow* window);

	virtual void prepare() = 0;
	virtual void render() = 0;
	virtual void cleanup() = 0;

public:
	ExerciseBase() = default;

	ExerciseBase(const char* a_windowName, const int a_windowWidth = 800, const int a_windowHeight = 600)
		: m_windowName(a_windowName),
		  m_windowWidth(a_windowWidth),
		  m_windowHeight(a_windowHeight)
	{
	}

	void run();

	virtual ~ExerciseBase() = default;
};

#endif