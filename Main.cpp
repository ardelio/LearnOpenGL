#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>

#include "FileUtils.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Shape.h"
#include "Window.h"

const std::string vertexShaderSource = readFileIntoString("./shaders/shader.vert");
const std::string fragmentShaderSource = readFileIntoString("./shaders/shader.frag");

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

  Shader vertexShader(GL_VERTEX_SHADER, vertexShaderSource.c_str());
  Shader fragmentShader(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str());

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

  Shape secondShape({
    -.5f, .5f, .0f,
    -.25f, .5f, .0f,
    .0f, .25f, .0f,
    });

  window.render([&program, &shape, &secondShape]() {
    program.use();
    shape.draw();
    secondShape.draw();
    });

  shape.destroy();
  program.destroy();
  window.destroy();

  return EXIT_SUCCESS;
}