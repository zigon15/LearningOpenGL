#ifndef VAO_ZENGINE_CLASS_H
#define VAO_ZENGINE_CLASS_H

#include <glad/glad.h>
#include <stdint.h>
#include "VBO.h"

class VAO {
public:
  VAO();
  ~VAO();
  
  void linkAttribute(
    VBO& rVBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset
  );

  void bind();
  void unbind();

  void free();

private:
  GLuint _vaoId;
};

#endif