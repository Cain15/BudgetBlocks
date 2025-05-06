//
// Created by cain on 6/05/25.
//

#ifndef BUDGETBLOCKS_VAO_H
#define BUDGETBLOCKS_VAO_H

#include <glad/glad.h>
#include "VBO.h"

class VAO {
public:
    GLuint ID;
    VAO();

    void LinkAttrib(VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
    void Bind();
    void Unbind();
    void Delete();
};


#endif //BUDGETBLOCKS_VAO_H
