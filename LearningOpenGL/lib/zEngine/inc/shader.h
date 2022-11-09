#ifndef SHADER_ZENGINE_CLASS_H
#define SHADER_ZENGINE_CLASS_H

#include <glad/glad.h>
#include <string>
#include <stdint.h>

class Shader {
public:
	Shader() = default;
	~Shader() = default;

	uint32_t compile(const char* vertexFile, const char* fragmentFile);

	void activate();
	void free();

	GLuint getId();

private:
	void checkErrors(unsigned int shader, const char* type);
	uint32_t readFile(const char* filename, std::string& rContents);

	GLuint _shaderId;
};
#endif