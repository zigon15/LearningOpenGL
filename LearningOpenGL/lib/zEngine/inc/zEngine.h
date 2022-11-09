#ifndef ZENGINE_CLASS_H
#define ZENGINE_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdint.h>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shader.h"

class ZEngine{
public:
  ZEngine(uint32_t windowHeight, uint32_t windowWidth);
  ~ZEngine();
  
  int32_t init(const char* windowname);
  int32_t loop();

  GLFWwindow* getWindow();

private:
  struct {
    uint32_t height;
    uint32_t width;
  } _windowSize;

  GLFWwindow* _window;
};

#endif