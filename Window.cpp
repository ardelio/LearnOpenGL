#include "Window.h"

void onSetFrameBufferSize(GLFWwindow* window, int width, int height);

Window::Window(const char* title, int width, int height)
{
  _title = title;
  _width = width;
  _height = height;
}

void Window::destroy()
{
  glfwTerminate();
}

bool Window::init()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  _window = glfwCreateWindow(_width, _height, _title, NULL, NULL);

  if (_window == NULL)
  {
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(_window);
  glfwSetFramebufferSizeCallback(_window, onSetFrameBufferSize);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    glfwTerminate();
    return false;
  }

  return true;
}

void Window::render(std::function<void()> callback)
{
  while (!glfwWindowShouldClose(_window))
  {
    processInput();

    glClearColor(.2f, .3f, .3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    callback();

    glfwSwapBuffers(_window);
    glfwPollEvents();
  }
}

void Window::processInput()
{
  if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(_window, true);
}

void onSetFrameBufferSize(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}