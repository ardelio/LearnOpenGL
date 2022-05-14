#include <vector>

#ifndef LEARN_OPEN_GL_SHAPE_CLASS
#define LEARN_OPEN_GL_SHAPE_CLASS

class Shape
{
public:
  Shape(std::vector<float> vertices);
  Shape(std::vector<float> vertices, std::vector<unsigned int> indices);
  void destroy();
  void draw();
private:
  unsigned int _vao, _vbo, _ebo;
  std::vector<float> _vertices;
  std::vector<unsigned int> _indices;

  bool hasIndices();
  void init();
};

#endif // !LEARN_OPEN_GL_SHAPE_CLASS


