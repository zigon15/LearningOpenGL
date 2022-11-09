#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <zEngine.h>

static constexpr uint32_t WINDOW_HEIGHT = 800;
static constexpr uint32_t WINDOW_WIDTH = 800;
static const char* WINDOW_NAME = "Learning OpenGL";

// Vertices coordinates
GLfloat vertices[] =
{ //               COORDINATES                  /     COLORS           //
	-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower left corner
	 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower right corner
	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.6f,  0.32f, // Upper corner
	-0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner left
	 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner right
	 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f  // Inner down
};

// Indices for vertices order
GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
};

int main(){
	uint32_t res;

	ZEngine zEngine{ WINDOW_HEIGHT, WINDOW_WIDTH };
	res = zEngine.init(WINDOW_NAME);
	if (res != 0) {
		std::cout << "Failed to create GLFW window!" << std::endl;
		return -1;
	}

	GLFWwindow* window = zEngine.getWindow();
	
	// Create shader program
	Shader shaderProgram{};
	res = shaderProgram.compile(
		"resources/shaders/defaultVert.glsl", 
		"resources/shaders/defaultFrag.glsl"
	);

	if (res != 0) {
		std::cout << "Shader Progam Failed to Compile!!" << std::endl;
		return res;
	}

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.linkAttribute(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.linkAttribute(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	VAO1.unbind();
	VBO1.unbind();
	EBO1.unbind();

	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.getId(), "scale");

	// Main while loop
	while (!glfwWindowShouldClose(window)){
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);

		// Tell OpenGL which Shader Program we want to use
		shaderProgram.activate();

		glUniform1f(uniID, 0.5f);

		// Bind the VAO so OpenGL knows to use it
		VAO1.bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Delete all the objects created
	VAO1.free();
	VBO1.free();
	EBO1.free();
	shaderProgram.free();

	return 0;
}