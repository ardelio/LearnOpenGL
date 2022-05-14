#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "ShaderProgram.h"
#include "Shape.h"
#include "Window.h"

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(1.0f, .5f, .2f, 1.0f);\n"
"}\0";

int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  Window window("Learn OpenGL", 800, 600);
  if (!window.init())
  {
    std::cout << "ERROR: Failed to init Window\n";
    return EXIT_FAILURE;
  };

  Shader vertexShader(GL_VERTEX_SHADER, vertexShaderSource);
  Shader fragmentShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

  ShaderProgram program;
  program.addShader(&vertexShader);
  program.addShader(&fragmentShader);

  if (!program.init())
  {
    window.destroy();
    std::cout << "ERROR: Failed to init ShaderProgram\n";
    return EXIT_FAILURE;
  }

  Shape shape({
      0.5f,  0.5f, 0.0f,  // top right
      0.5f, -0.5f, 0.0f,  // bottom right
      -0.5f, -0.5f, 0.0f,  // bottom left
      -0.5f,  0.5f, 0.0f   // top left 
    }, {
      0, 1, 3,  // first triangle
      1, 2, 3   // second triangle
    });

  window.render([&program, &shape]() {
    program.use();
    shape.draw();
    });

  shape.destroy();
  program.destroy();
  window.destroy();

  return EXIT_SUCCESS;
}