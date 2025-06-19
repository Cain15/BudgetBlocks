//
// Created by cain on 25/04/25.
//

#include "Game.h"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

// Vertices coordinates
GLfloat vertices[] =
        { //     COORDINATES     /        COLORS      /         TexCoord  //   face | height | side from front perspective
                -0.5f, -0.5f, 0.5f,    0.83f, 0.70f, 0.44f,	    0.0f, 0.0f, // Front bottom left
                -0.5f, 0.5f,  0.5f,    0.83f, 0.70f, 0.44f,	    0.0f, 1.0f, // Front top left
                0.5f,  0.5f,  0.5f,    0.83f, 0.70f, 0.44f,	    1.0f, 1.0f, // Front top right
                0.5f,  -0.5f, 0.5f,    0.83f, 0.70f, 0.44f,	    1.0f, 0.0f, // Front bottom right
                -0.5f, -0.5f, -0.5f,    0.83f, 0.70f, 0.44f,	0.0f, 0.0f, // Back bottom left
                -0.5f, 0.5f,  -0.5f,    0.83f, 0.70f, 0.44f,	0.0f, 1.0f, // Back top left
                0.5f,  0.5f,  -0.5f,    0.83f, 0.70f, 0.44f,	1.0f, 1.0f, // Back top right
                0.5f, -0.5f,  -0.5f,    0.83f, 0.70f, 0.44f,	1.0f, 0.0f, // Back bottom right
                -0.5f, -0.5f, -0.5f,    0.83f, 0.70f, 0.44f,	0.0f, 0.0f, // Left bottom left
                -0.5f, 0.5f,  -0.5f,    0.83f, 0.70f, 0.44f,	0.0f, 1.0f, // Left top left
                -0.5f, 0.5f,  0.5f,    0.83f, 0.70f, 0.44f,	    1.0f, 1.0f, // Left top right
                -0.5f, -0.5f, 0.5f,    0.83f, 0.70f, 0.44f,	    1.0f, 0.0f, // Left bottom right
                0.5f,  -0.5f, 0.5f,    0.83f, 0.70f, 0.44f,	    0.0f, 0.0f, // Right bottom left
                0.5f,  0.5f,  0.5f,    0.83f, 0.70f, 0.44f,	    0.0f, 1.0f, // Right top left
                0.5f,  0.5f,  -0.5f,    0.83f, 0.70f, 0.44f,	1.0f, 1.0f, // Right top right
                0.5f, -0.5f,  -0.5f,    0.83f, 0.70f, 0.44f,	1.0f, 0.0f, // Right bottom right
                -0.5f, 0.5f,  0.5f,    0.83f, 0.70f, 0.44f,	    0.0f, 0.0f, // Top bottom left
                -0.5f, 0.5f,  -0.5f,    0.83f, 0.70f, 0.44f,	0.0f, 1.0f, // Top top left
                0.5f,  0.5f,  -0.5f,    0.83f, 0.70f, 0.44f,	1.0f, 1.0f, // Top top right
                0.5f,  0.5f,  0.5f,    0.83f, 0.70f, 0.44f,	    1.0f, 0.0f, // Top Bottom right
                -0.5f, -0.5f, -0.5f,    0.83f, 0.70f, 0.44f,	0.0f, 0.0f, // Bottom bottom left
                -0.5f, -0.5f, 0.5f,    0.83f, 0.70f, 0.44f,	    0.0f, 1.0f, // Bottom top left
                0.5f,  -0.5f, 0.5f,    0.83f, 0.70f, 0.44f,	    1.0f, 1.0f, // Bottom top right
                0.5f, -0.5f,  -0.5f,    0.83f, 0.70f, 0.44f,	1.0f, 0.0f, // Bottom bottom right
        };

// Indices for vertices order
GLuint indices[] =
        {
                0, 1, 2, // front upper triangle
                0, 2, 3, // front lower trianglee
                7, 6, 5, // Back upper triangle
                7, 5, 4, // Back lower triangle
                8, 9, 10, // Left upper triangle
                8, 10, 11, // Left lower triangled
                12, 13, 14, // Right upper triangle
                12, 14, 15, // Right lower triangle
                16, 17, 18, // Top upper triangle
                16, 18, 19, // Top lower triangle
                20, 21, 22, // Bottom upper triangle
                20, 22, 23 // Bottom lower triangle
        };

int Game::run() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primary);
    width = mode->width;
    height = mode->height;

    // Initialize GLFW
    glfwInit();

    // Tell GLFW what version of OpenGL we are using
    // In this case we are using OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell GLFW we are using the CORE profile
    // So that means we only have the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
    GLFWwindow* window = glfwCreateWindow(width, height, "BudgetBlocks", NULL, NULL);
    // Error check if the window fails to create
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Introduce the window into the current context
    glfwMakeContextCurrent(window);

    //Load GLAD so it configures OpenGL
    gladLoadGL();
    // Specify the viewport of OpenGL in the Window
    // In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
    glViewport(0, 0, width, height);



    // Generates Shader object using shaders default.vert and default.frag
    Shader shaderProgram("../frontend/shaders/default.vert", "../frontend/shaders/default.frag");



    // Generates Vertex Array Object and binds it
    VAO VAO1;
    VAO1.Bind();

    // Generates Vertex Buffer Object and links it to vertices
    VBO VBO1(vertices, sizeof(vertices));
    // Generates Element Buffer Object and links it to indices
    EBO EBO1(indices, sizeof(indices));

    // Links VBO attributes such as coordinates and colors to VAO
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // Texture
    Texture popCat("../resources/default_grass_side.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    popCat.texUnit(shaderProgram, "tex0", 0);

    // Original code from the tutorial
    /*Texture popCat("pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    popCat.texUnit(shaderProgram, "tex0", 0);*/

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    // Main while loop
    auto startTime = static_cast<float>(glfwGetTime());

    while (!glfwWindowShouldClose(window))
    {
        float deltaTime = static_cast<float>(glfwGetTime()) - startTime;
        float fps = 1.0f / deltaTime;
        startTime = static_cast<float>(glfwGetTime());

        world->update(deltaTime);

        std::cout << "FPS: " << fps << std::endl;
        // Specify the color of the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Tell OpenGL which Shader Program we want to use
        shaderProgram.Activate();

        camera.Inputs(window);
        handleInput(window);
        coordinates playerpos = world->player->getPosition();
        camera.Position = glm::vec3(playerpos.x, playerpos.y, playerpos.z + 2.0f);
        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

        // Binds texture so that is appears in rendering
        popCat.Bind();
        // Bind the VAO so OpenGL knows to use it
        VAO1.Bind();

        glm::vec3 blockCoordinate;
        // Draw blocks

        // Set the coordinate of the block;
        blockCoordinate = glm::vec3((float) 0.0f , 0.0f, 0.0f);
        glUniform3fv(glGetUniformLocation(shaderProgram.ID, "BlockCoordinate"), 1, glm::value_ptr(blockCoordinate));
        // Draw primitives, number of indices, datatype of indices, index of indices
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);



        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);
        // Take care of all GLFW events
        glfwPollEvents();
    }



    // Delete all the objects we've created
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    popCat.Delete();
    shaderProgram.Delete();
    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();
    return 0;
}

void Game::handleInput(GLFWwindow *window) {

}
