#include "object.h"

void Object::GenBuffers(unsigned int* indexes, unsigned int size_ind,
                        Vertex* vertices, unsigned int size_arr)
{
    glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

    glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, size_arr * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &this->IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_ind * sizeof(int), indexes, GL_STATIC_DRAW);
}
