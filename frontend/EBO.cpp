//
// Created by cain on 6/05/25.
//

#include "EBO.h"

EBO::EBO(GLuint* indices, GLsizeiptr size) {
    // Generate the element buffer object
    glGenBuffers(1, &ID);
    // Bind the element buffer object
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    // Copy the index data into the buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::Bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete() {
    glDeleteBuffers(1, &ID);
}
