#pragma once
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Vertex
{
    glm::vec3 pos;
    glm::vec2 tex;
    glm::vec3 normal;

    Vertex() {}
    Vertex(glm::vec3 pos, glm::vec2 tex)
    {
        this->pos = pos;
        this->tex = tex;
        this->normal = glm::vec3(0.0f, 0.0f, 0.0f);
    }

    Vertex(glm::vec3 pos, glm::vec2 tex, glm::vec3 normal)
    {
        this->pos = pos;
        this->tex = tex;
        this->normal = normal;
    }
};

class Object
{
public:
    GLuint VAO;
    GLuint VBO;
    GLuint IBO;
    Object() : VAO(NULL), VBO(NULL), IBO(NULL) {};
    virtual ~Object() {};
    void GenBuffers(unsigned int* indexes, unsigned int size_ind,
                    Vertex* vertices, unsigned int size_arr);
};

