#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shape.h"
#include <iostream>

Shape::Shape(std::vector<float> vertices)
{
  _vertices = vertices;
  _indices = {};
  init();
}

Shape::Shape(std::vector<float> vertices, std::vector<unsigned int> indices)
{
  _vertices = vertices;
  _indices = indices;
  init();
}

void Shape::destroy()
{
  glDeleteVertexArrays(1, &_vao);
  glDeleteBuffers(1, &_vbo);
  glDeleteBuffers(1, &_ebo);
}

void Shape::draw()
{
  glBindVertexArray(_vao);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  if (hasIndices())
    glDrawElements(GL_TRIANGLES, (int)_indices.size(), GL_UNSIGNED_INT, 0);
  else
    glDrawArrays(GL_TRIANGLES, 0, (int)_vertices.size());
}

bool Shape::hasIndices()
{
  return _indices.size() > 0;
}

void Shape::init()
{
  glGenVertexArrays(1, &_vao);

  // Create a Vertex Buffer Object. A VBO can store a large number of vertices in the GPUs memory.
  // A vertex shaders main purpose is to transform 3D coordinates into different 3D coordinates.
  // It also allows developers to do basic processing on the vertex attributes.
  glGenBuffers(1, &_vbo);

  if (hasIndices())
    glGenBuffers(1, &_ebo);

  glBindVertexArray(_vao);

  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), _vertices.data(), GL_STATIC_DRAW);

  if (hasIndices())
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), _indices.data(), GL_STATIC_DRAW);
  }

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}