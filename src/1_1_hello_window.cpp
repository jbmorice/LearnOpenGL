#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

////////////////////////
// Callback functions
////////////////////////

// Callback function to print GLFW errors in console
void gflwErrorCallback(int error, const char* description)
{
	std::cout << description << std::endl;
}

// Callback function to adapt OpenGL viewport according to the GLFW window
void glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	// Set OpenGL viewport position and dimensions according to our window
	glViewport(0, 0, width, height);
}

////////////////////////
// Helper functions
////////////////////////

// Function called at the beginning of the render loop to handle inputs
void processInput(GLFWwindow* window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

////////////////////////
// Main
int main(int argc, char* argv[])
{
	// Set the GLFW error callback function
	glfwSetErrorCallback(gflwErrorCallback);

	// Initialize and configure GLFW for the version of OpenGL we target
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);

	if(window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		std::cin.ignore();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Initialize GLAD (retrieves all OpenGL function pointers)
	if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

		std::cin.ignore();
		return -1;
	}

	// Set the callback function to resize the viewport with the GLFW window
	glfwSetFramebufferSizeCallback(window, glfwFramebufferSizeCallback);

	// Start the render loop (won't stop running unless something tries to close the GLFW window)
	while(!glfwWindowShouldClose(window))
	{
		// Handle inputs
		processInput(window);

		// Rendering happens here
		// =====

		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// =====
		glfwSwapBuffers(window); // Swap the back and front buffers
		glfwPollEvents(); // Check if any event has been triggered and call the according callbacks
	}

	// Properly stop GLFW
	glfwTerminate();

	return 0;
}
