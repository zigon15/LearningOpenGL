#include <zEngine.h>

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ZEngine::ZEngine(uint32_t windowHeight, uint32_t windowWidth):
	_windowSize{ windowHeight, windowWidth }, _window{nullptr}
{

}

ZEngine::~ZEngine() {
	// Free up any allocated resources
	if (_window) {
		glfwDestroyWindow(_window);
	}

	glfwTerminate();
}

int32_t ZEngine::init(const char* windowName) {
  glfwInit();
    
	// OpenGL 3.3 with core functions only
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window
	_window = glfwCreateWindow(
		_windowSize.width, _windowSize.height, windowName, NULL, NULL
	);

	// Check windows was created successfully
	if (_window == nullptr) {
		glfwTerminate();
		return 1;
	}
	
	// Introduce window into current context
	glfwMakeContextCurrent(_window);

	// Load GLAD and create the OpenGL viewport
	gladLoadGL();
	glViewport(0, 0, _windowSize.width, _windowSize.height);

	return 0;
}

int32_t ZEngine::loop() {
	// Specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	// Clean the back buffer and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Swap the back buffer with the front buffer
	glfwSwapBuffers(_window);

	// Take care of all GLFW events
	glfwPollEvents();

	return glfwWindowShouldClose(_window);
}

GLFWwindow* ZEngine::getWindow() {
	return _window;
}