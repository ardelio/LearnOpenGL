#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include <vector>

#ifndef LEARN_OPEN_GL_SHADER_PROGRAM_CLASS
#define LEARN_OPEN_GL_SHADER_PROGRAM_CLASS

class ShaderProgram
{
public:
  ShaderProgram();
  void addShader(Shader* shader);
  void destroy();
  bool init();
  void use();
private:
  unsigned int _program;
  std::vector<Shader*> _shaders;
};

#endif // !LEARN_OPEN_GL_SHADER_PROGRAM_CLASS
