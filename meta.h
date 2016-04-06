#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

int e = 20.0f;

Vertex cube_vertices[24] =
{
    Vertex(glm::vec3(-e, -e, -e),  glm::vec2(1.0f, 1.0f), glm::vec3(0, 0, -1)),
    Vertex(glm::vec3(e, -e, -e),  glm::vec2(0.0f, 1.0f),  glm::vec3(0, 0, -1)),
    Vertex(glm::vec3(e, e, -e),  glm::vec2(0.0f, 0.0f),   glm::vec3(0, 0, -1)),
    Vertex(glm::vec3(-e, e, -e),  glm::vec2(1.0f, 0.0f),  glm::vec3(0, 0, -1)),

    Vertex(glm::vec3(-e, -e, e),  glm::vec2(1.0f, 1.0f), glm::vec3(0, 0, 1)),
    Vertex(glm::vec3(e, -e, e),  glm::vec2(0.0f, 1.0f),  glm::vec3(0, 0, 1)),
    Vertex(glm::vec3(e, e, e),  glm::vec2(0.0f, 0.0f),   glm::vec3(0, 0, 1)),
    Vertex(glm::vec3(-e, e, e),  glm::vec2(1.0f, 0.0f),  glm::vec3(0, 0, 1)),

    Vertex(glm::vec3(-e, -e, -e),  glm::vec2(1.0f, 1.0f), glm::vec3(-1, 0, 0)),
    Vertex(glm::vec3(-e, -e, e),  glm::vec2(0.0f, 1.0f),  glm::vec3(-1, 0, 0)),
    Vertex(glm::vec3(-e, e, e),  glm::vec2(0.0f, 0.0f),   glm::vec3(-1, 0, 0)),
    Vertex(glm::vec3(-e, e, -e),  glm::vec2(1.0f, 0.0f),  glm::vec3(-1, 0, 0)),

    Vertex(glm::vec3(e, -e, -e),  glm::vec2(1.0f, 1.0f), glm::vec3(1, 0, 0)),
    Vertex(glm::vec3(e, -e, e),  glm::vec2(0.0f, 1.0f),  glm::vec3(1, 0, 0)),
    Vertex(glm::vec3(e, e, e),  glm::vec2(0.0f, 0.0f),   glm::vec3(1, 0, 0)),
    Vertex(glm::vec3(e, e, -e),  glm::vec2(1.0f, 0.0f),  glm::vec3(1, 0, 0)),

    Vertex(glm::vec3(-e, -e, -e),  glm::vec2(1.0f, 1.0f), glm::vec3(0, 1, 0)),
    Vertex(glm::vec3(-e, -e, e),  glm::vec2(0.0f, 1.0f),  glm::vec3(0, 1, 0)),
    Vertex(glm::vec3(e, -e, e),  glm::vec2(0.0f, 0.0f),   glm::vec3(0, 1, 0)),
    Vertex(glm::vec3(e, -e, -e),  glm::vec2(1.0f, 0.0f),  glm::vec3(0, 1, 0)),

    Vertex(glm::vec3(-e, e, -e),  glm::vec2(1.0f, 1.0f),  glm::vec3(0, -1, 0)),
    Vertex(glm::vec3(-e, e, e),  glm::vec2(0.0f, 1.0f),   glm::vec3(0, -1, 0)),
    Vertex(glm::vec3(e, e, e),  glm::vec2(0.0f, 0.0f),    glm::vec3(0, -1, 0)),
    Vertex(glm::vec3(e, e, -e),  glm::vec2(1.0f, 0.0f),   glm::vec3(0, -1, 0))
};

unsigned int cube_indices[] =
{
    0, 1, 2, //First side
    2, 3, 0,
    4, 5, 6, //Second side
    6, 7, 4,
    10, 9, 8, //Right
    10, 8, 11,
    12, 13, 14, //Left
    14, 15, 12,
    16, 17, 18, //Down
    18, 19, 16,
    20, 21, 22,  //Up
    22, 23, 20
};

int e_sun = 10.0f;

Vertex sun_vertices[24] =
{
    Vertex(glm::vec3(-e_sun, -e_sun, -e_sun),  glm::vec2(1.0f, 1.0f), glm::vec3(0, 0, -1)),
    Vertex(glm::vec3(e_sun, -e_sun, -e_sun),  glm::vec2(0.0f, 1.0f), glm::vec3(0, 0, -1)),
    Vertex(glm::vec3(e_sun, e_sun, -e_sun),  glm::vec2(0.0f, 0.0f),  glm::vec3(0, 0, -1)),
    Vertex(glm::vec3(-e_sun, e_sun, -e_sun),  glm::vec2(1.0f, 0.0f), glm::vec3(0, 0, -1)),

    Vertex(glm::vec3(-e_sun, -e_sun, e_sun),  glm::vec2(1.0f, 1.0f), glm::vec3(0, 0, 1)),
    Vertex(glm::vec3(e_sun, -e_sun, e_sun),  glm::vec2(0.0f, 1.0f), glm::vec3(0, 0, 1)),
    Vertex(glm::vec3(e_sun, e_sun, e_sun),  glm::vec2(0.0f, 0.0f),  glm::vec3(0, 0, 1)),
    Vertex(glm::vec3(-e_sun, e_sun, e_sun),  glm::vec2(1.0f, 0.0f), glm::vec3(0, 0, 1)),

    Vertex(glm::vec3(-e_sun, -e_sun, -e_sun),  glm::vec2(1.0f, 1.0f), glm::vec3(-1, 0, 0)),
    Vertex(glm::vec3(-e_sun, -e_sun, e_sun),  glm::vec2(0.0f, 1.0f), glm::vec3(-1, 0, 0)),
    Vertex(glm::vec3(-e_sun, e_sun, e_sun),  glm::vec2(0.0f, 0.0f),  glm::vec3(-1, 0, 0)),
    Vertex(glm::vec3(-e_sun, e_sun, -e_sun),  glm::vec2(1.0f, 0.0f), glm::vec3(-1, 0, 0)),

    Vertex(glm::vec3(e_sun, -e_sun, -e_sun),  glm::vec2(1.0f, 1.0f),glm::vec3(1, 0, 0)),
    Vertex(glm::vec3(e_sun, -e_sun, e_sun),  glm::vec2(0.0f, 1.0f), glm::vec3(1, 0, 0)),
    Vertex(glm::vec3(e_sun, e_sun, e_sun),  glm::vec2(0.0f, 0.0f),  glm::vec3(1, 0, 0)),
    Vertex(glm::vec3(e_sun, e_sun, -e_sun),  glm::vec2(1.0f, 0.0f), glm::vec3(1, 0, 0)),

    Vertex(glm::vec3(-e_sun, -e_sun, -e_sun),  glm::vec2(1.0f, 1.0f), glm::vec3(0, 1, 0)),
    Vertex(glm::vec3(-e_sun, -e_sun, e_sun),  glm::vec2(0.0f, 1.0f), glm::vec3(0, 1, 0)),
    Vertex(glm::vec3(e_sun, -e_sun, e_sun),  glm::vec2(0.0f, 0.0f),  glm::vec3(0, 1, 0)),
    Vertex(glm::vec3(e_sun, -e_sun, -e_sun),  glm::vec2(1.0f, 0.0f), glm::vec3(0, 1, 0)),

    Vertex(glm::vec3(-e_sun, e_sun, -e_sun),  glm::vec2(1.0f, 1.0f), glm::vec3(0, -1, 0)),
    Vertex(glm::vec3(-e_sun, e_sun, e_sun),  glm::vec2(0.0f, 1.0f),  glm::vec3(0, -1, 0)),
    Vertex(glm::vec3(e_sun, e_sun, e_sun),  glm::vec2(0.0f, 0.0f),   glm::vec3(0, -1, 0)),
    Vertex(glm::vec3(e_sun, e_sun, -e_sun),  glm::vec2(1.0f, 0.0f),   glm::vec3(0, -1, 0))
};

unsigned int sun_indices[] =
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
