#include "EBO.h"

EBO::EBO(GLuint* pIndices, GLsizeiptr indicesLen) {
	glGenBuffers(1, &_eboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _eboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesLen, pIndices, GL_STATIC_DRAW);
}

EBO::~EBO() {
}

void EBO::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _eboId);
}

void EBO::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::free() {
	glDeleteBuffers(1, &_eboId);
}