#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#ifndef LEARN_OPEN_GL_SHADER_CLASS
#define LEARN_OPEN_GL_SHADER_CLASS

class Shader
{
public:
  Shader(int shaderType, const char* shaderSource);
  unsigned int get();
  bool init();
  void destroy();

private:
  unsigned int _shader;
  const char* _shaderSource;
  int _shaderType;
};

#endif // !LEARN_OPEN_GL_SHADER_CLASS
