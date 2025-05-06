//
// Created by cain on 6/05/25.
//

#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size) {
    // Generate the vertex buffer object
    glGenBuffers(1, &ID);
    // Bind the vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    // Copy the vertex data into the buffer
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() {
    glDeleteBuffers(1, &ID);
}
