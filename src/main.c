#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <stdio.h>

int main(void) {
	// Initialize the library
	if (!glfwInit()) {
		return -1;
	}

	// Create a windowed mode window and its OpenGL context
	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello GLFW", NULL, NULL);
	if (!window) {
		// Window or OpenGL context creation failed
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window)) {
		// Render here
        	glClear(GL_COLOR_BUFFER_BIT);
	
		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	// terminate when application exits
	glfwTerminate();
	return 0;
}