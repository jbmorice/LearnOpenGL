#include "exercise_base.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../thirdparty/stb/stb_image.h"

void ExerciseBase::gflwErrorCallback(int error, const char* description)
{
	std::cout << description << std::endl;
}

void ExerciseBase::glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	// Set OpenGL viewport position and dimensions according to our window
	glViewport(0, 0, width, height);
}

void ExerciseBase::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void ExerciseBase::run()
{
	// Set the GLFW error callback function
	glfwSetErrorCallback(gflwErrorCallback);

	// Initialize and configure GLFW for the version of OpenGL we target
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window
	m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, m_windowName, nullptr, nullptr);

	if (m_window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		std::cin.ignore();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(m_window);

	// Initialize GLAD (retrieves all OpenGL function pointers)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

		std::cin.ignore();
		exit(EXIT_FAILURE);
	}

	// Set the callback function to resize the viewport with the GLFW window
	glfwSetFramebufferSizeCallback(m_window, glfwFramebufferSizeCallback);

	prepare();

	float oldTime = 0.0f;
	
	// Start the render loop (won't stop running unless something tries to close the GLFW window)
	while (!glfwWindowShouldClose(m_window))
	{
		float currentTime = (float) glfwGetTime();
		float deltaTime = currentTime - oldTime;
		oldTime = currentTime;

		// Handle inputs
		processInput(m_window);

		// Rendering happens here
		// =====

		render(deltaTime);

		// =====
		glfwSwapBuffers(m_window); // Swap the back and front buffers
		glfwPollEvents(); // Check if any event has been triggered and call the according callbacks
	}

	cleanup();

	// Properly stop GLFW
	glfwTerminate();
}