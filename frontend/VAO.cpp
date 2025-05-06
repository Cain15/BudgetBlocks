//
// Created by cain on 6/05/25.
//

#include "VAO.h"

VAO::VAO() {
    // Generate the vertex array object
    glGenVertexArrays(1, &ID);
}

void VAO::LinkAttrib(VBO &vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset) {
    vbo.Bind();
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    vbo.Unbind();
}

void VAO::Bind() {
    // Bind the vertex array object
    glBindVertexArray(ID);
}

void VAO::Unbind() {
    // Unbind the vertex array object
    glBindVertexArray(0);
}

void VAO::Delete() {
    // Delete the vertex array object
    glDeleteVertexArrays(1, &ID);
}