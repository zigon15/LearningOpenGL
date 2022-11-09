#ifndef VBO_ZENGINE_CLASS_H
#define VBO_ZENGINE_CLASS_H

#include <glad/glad.h>
#include <stdint.h>

class VBO {
public:
  VBO(GLfloat* vertices, GLsizeiptr verticesLen);
  ~VBO();

  void bind();
  void unbind();

  void free();

private:
  GLuint _vboId;
};

#endif