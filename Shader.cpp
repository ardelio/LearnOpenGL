#include "Shader.h"

Shader::Shader(int shaderType, const char* shaderSource)
{
  _shader = glCreateShader(shaderType);
  _shaderSource = shaderSource;
  _shaderType = shaderType;
}

unsigned int Shader::get()
{
  return _shader;
}

void Shader::destroy()
{
  glDeleteShader(_shader);
}

bool Shader::init()
{
  glShaderSource(_shader, 1, &_shaderSource, NULL);
  glCompileShader(_shader);

  int success;
  char infoLog[512];
  glGetShaderiv(_shader, GL_COMPILE_STATUS, &success);

  if (!success)
  {
    glGetShaderInfoLog(_shader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << "\n";
    return false;
  }

  return true;
}