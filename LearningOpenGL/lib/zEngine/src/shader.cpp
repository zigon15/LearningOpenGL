#include "shader.h"

#include <string>
#include <stdint.h>
#include <fstream>
#include <sstream>
#include <iostream>

uint32_t Shader::compile(const char* vertexFile, const char* fragmentFile) {
	std::string vertexShaderCode;
	std::string fragmentShaderCode;
	uint32_t res = 0;

	res = readFile(vertexFile, vertexShaderCode);
	if (res != 0){
		return res;
	}

	res = readFile(fragmentFile, fragmentShaderCode);
	if (res != 0) {
		return res;
	}

	const char* vertexSource = vertexShaderCode.c_str();
	const char* fragmentSource = fragmentShaderCode.c_str();

	// Create, attach and compile vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	checkErrors(vertexShader, "VERTEX");

	// Create, attach and compile fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	checkErrors(fragmentShader, "FRAGMENT");

	// Create shader program
	_shaderId = glCreateProgram();
	glAttachShader(_shaderId, vertexShader);
	glAttachShader(_shaderId, fragmentShader);
	glLinkProgram(_shaderId);

	// Checks if shaders linked succesfully
	checkErrors(_shaderId, "PROGRAM");

	// Vertex and fragment shader no longer needed
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return 0;
}

void Shader::activate(){
	glUseProgram(_shaderId);
}

void Shader::free(){
	glDeleteProgram(_shaderId);
}

void Shader::checkErrors(unsigned int shader, const char* type){
	GLint hasCompiled;
	char infoLog[1024];

	if (type != "PROGRAM"){
		// Compliation error
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE){
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}else{
		// Linker error
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE){
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}

uint32_t Shader::readFile(const char* filename, std::string& rContents) {
	std::ifstream in(filename, std::ios::binary);

	// Check if opened file succesfully
	if (in) {
		// Resize string to hold file contens
		in.seekg(0, std::ios::end);
		rContents.resize(in.tellg());

		// Read file
		in.seekg(0, std::ios::beg);
		in.read(&rContents[0], rContents.size());

		// Close file
		in.close();
		return 0;
	}else {
		return 1;
	}
}

GLuint Shader::getId() {
	return _shaderId;
}