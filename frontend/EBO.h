//
// Created by cain on 6/05/25.
//

#ifndef BUDGETBLOCKS_EBO_H
#define BUDGETBLOCKS_EBO_H

#include <glad/glad.h>

class EBO {
public:
    GLuint ID;
    EBO(GLuint* indices, GLsizeiptr size);

    void Bind();
    void Unbind();
    void Delete();
};


#endif //BUDGETBLOCKS_EBO_H
