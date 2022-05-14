#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
  _program = glCreateProgram();
}

void ShaderProgram::addShader(Shader* shader)
{
  _shaders.resize(_shaders.size() + 1);
  _shaders[_shaders.size() - 1] = shader;
}

void ShaderProgram::destroy()
{
  glDeleteProgram(_program);
}

bool ShaderProgram::init()
{
  for (int i = 0; i < _shaders.size(); i++)
  {
    Shader shader = *_shaders[i];
    shader.init();
    glAttachShader(_program, shader.get());
    shader.destroy();
  }

  glLinkProgram(_program);

  int success;
  char infoLog[512];
  glGetProgramiv(_program, GL_LINK_STATUS, &success);

  if (!success)
  {
    glGetProgramInfoLog(_program, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << "\n";
    return false;
  }

  return true;
}

void ShaderProgram::use()
{
  glUseProgram(_program);
}
