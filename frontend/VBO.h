//
// Created by cain on 6/05/25.
//

#ifndef BUDGETBLOCKS_VBO_H
#define BUDGETBLOCKS_VBO_H

#include <glad/glad.h>

class VBO {
public:
    GLuint ID;
    VBO(GLfloat* vertices, GLsizeiptr size);

    void Bind();
    void Unbind();
    void Delete();
};


#endif //BUDGETBLOCKS_VBO_H
