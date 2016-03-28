#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

Vertex cube_vertices[24] =
{
    Vertex(glm::vec3(-10.0f, -10.0f, -10.0f),  glm::vec2(1.0f, 1.0f)),
    Vertex(glm::vec3(10.0f, -10.0f, -10.0f),  glm::vec2(0.0f, 1.0f)),
    Vertex(glm::vec3(10.0f, 10.0f, -10.0f),  glm::vec2(0.0f, 0.0f)),
    Vertex(glm::vec3(-10.0f, 10.0f, -10.0f),  glm::vec2(1.0f, 0.0f)),

    Vertex(glm::vec3(-10.0f, -10.0f, 10.0f),  glm::vec2(1.0f, 1.0f)),
    Vertex(glm::vec3(10.0f, -10.0f, 10.0f),  glm::vec2(0.0f, 1.0f)),
    Vertex(glm::vec3(10.0f, 10.0f, 10.0f),  glm::vec2(0.0f, 0.0f)),
    Vertex(glm::vec3(-10.0f, 10.0f, 10.0f),  glm::vec2(1.0f, 0.0f)),

    Vertex(glm::vec3(-10.0f, -10.0f, -10.0f),  glm::vec2(1.0f, 1.0f)),
    Vertex(glm::vec3(-10.0f, -10.0f, 10.0f),  glm::vec2(0.0f, 1.0f)),
    Vertex(glm::vec3(-10.0f, 10.0f, 10.0f),  glm::vec2(0.0f, 0.0f)),
    Vertex(glm::vec3(-10.0f, 10.0f, -10.0f),  glm::vec2(1.0f, 0.0f)),

    Vertex(glm::vec3(10.0f, -10.0f, -10.0f),  glm::vec2(1.0f, 1.0f)),
    Vertex(glm::vec3(10.0f, -10.0f, 10.0f),  glm::vec2(0.0f, 1.0f)),
    Vertex(glm::vec3(10.0f, 10.0f, 10.0f),  glm::vec2(0.0f, 0.0f)),
    Vertex(glm::vec3(10.0f, 10.0f, -10.0f),  glm::vec2(1.0f, 0.0f)),

    Vertex(glm::vec3(-10.0f, -10.0f, -10.0f),  glm::vec2(1.0f, 1.0f)),
    Vertex(glm::vec3(-10.0f, -10.0f, 10.0f),  glm::vec2(0.0f, 1.0f)),
    Vertex(glm::vec3(10.0f, -10.0f, 10.0f),  glm::vec2(0.0f, 0.0f)),
    Vertex(glm::vec3(10.0f, -10.0f, -10.0f),  glm::vec2(1.0f, 0.0f)),

    Vertex(glm::vec3(-10.0f, 10.0f, -10.0f),  glm::vec2(1.0f, 1.0f)),
    Vertex(glm::vec3(-10.0f, 10.0f, 10.0f),  glm::vec2(0.0f, 1.0f)),
    Vertex(glm::vec3(10.0f, 10.0f, 10.0f),  glm::vec2(0.0f, 0.0f)),
    Vertex(glm::vec3(10.0f, 10.0f, -10.0f),  glm::vec2(1.0f, 0.0f))
};

unsigned int cube_indices[] =
{
    0, 1, 2,
    2, 3, 0,
    4, 5, 6,
    6, 7, 4,
    8, 9, 10,
    10, 11, 8,
    12, 13, 14,
    14, 15, 12,
    16, 17, 18,
    18, 19, 16,
    20, 21, 22,
    22, 23, 20
};
