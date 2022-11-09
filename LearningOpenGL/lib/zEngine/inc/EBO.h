#ifndef EBO_ZENGINE_CLASS_H
#define EBO_ZENGINE_CLASS_H

#include <glad/glad.h>
#include <stdint.h>

class EBO {
public:
  EBO(GLuint* pIndices, GLsizeiptr indicesLen);
  ~EBO();

  void bind();
  void unbind();

  void free();

private:
  GLuint _eboId;
};

#endif