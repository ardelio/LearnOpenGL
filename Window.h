#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <functional>

#ifndef LEARN_OPEN_GL_WINDOW_CLASS
#define LEARN_OPEN_GL_WINDOW_CLASS

class Window
{
public:
  Window(const char* title, int width, int height);
  bool init();
  void destroy();
  void render(std::function<void ()> callback);

private:
  const char* _title;
  int _width{};
  int _height{};
  GLFWwindow* _window{};

  void processInput();
};

#endif // !LEARN_OPEN_GL_WINDOW_CLASS
