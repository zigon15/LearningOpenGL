#include "VAO.h"

VAO::VAO() {
  glGenVertexArrays(1, &_vaoId);
}

VAO::~VAO() {
}

void VAO::linkAttribute(
  VBO& rVBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset
) {
  rVBO.bind();
  glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
  glEnableVertexAttribArray(layout);
  rVBO.unbind();
}

void VAO::bind() {
  glBindVertexArray(_vaoId);
}

void VAO::unbind() {
  glBindVertexArray(0);
}

void VAO::free() {
  glDeleteVertexArrays(1, &_vaoId);
}