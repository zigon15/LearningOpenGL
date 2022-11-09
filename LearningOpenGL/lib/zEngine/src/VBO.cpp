#include "VBO.h"

VBO::VBO(GLfloat* pVertices, GLsizeiptr verticesLen) {
  glGenBuffers(1, &_vboId);
  glBindBuffer(GL_ARRAY_BUFFER, _vboId);
  glBufferData(GL_ARRAY_BUFFER, verticesLen, pVertices, GL_STATIC_DRAW);
}

VBO::~VBO() {
}

void VBO::bind() {
  glBindBuffer(GL_ARRAY_BUFFER, _vboId);
}

void VBO::unbind() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::free() {
  glDeleteVertexArrays(1, &_vboId);
}