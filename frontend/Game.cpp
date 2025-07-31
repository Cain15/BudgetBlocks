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
#include "../utils.h"
#include "../backend/CameraView.h"

// Vertices coordinates
GLfloat vertices[] = { //     COORDINATES     /        COLORS      /         TexCoord  //   face | height | side from front perspective
        -0.5f, -0.5f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f, // Front bottom left
        -0.5f, 0.5f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f, // Front top left
        0.5f, 0.5f, 0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f, // Front top right
        0.5f, -0.5f, 0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f, // Front bottom right
        -0.5f, -0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f, // Back bottom left
        -0.5f, 0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f, // Back top left
        0.5f, 0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f, // Back top right
        0.5f, -0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f, // Back bottom right
        -0.5f, -0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f, // Left bottom left
        -0.5f, 0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f, // Left top left
        -0.5f, 0.5f, 0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f, // Left top right
        -0.5f, -0.5f, 0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f, // Left bottom right
        0.5f, -0.5f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f, // Right bottom left
        0.5f, 0.5f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f, // Right top left
        0.5f, 0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f, // Right top right
        0.5f, -0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f, // Right bottom right
        -0.5f, 0.5f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f, // Top bottom left
        -0.5f, 0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f, // Top top left
        0.5f, 0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f, // Top top right
        0.5f, 0.5f, 0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f, // Top Bottom right
        -0.5f, -0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f, // Bottom bottom left
        -0.5f, -0.5f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f, // Bottom top left
        0.5f, -0.5f, 0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f, // Bottom top right
        0.5f, -0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f, // Bottom bottom right
};

// Indices for vertices order
GLuint indices[] = {0, 1, 2, // front upper triangle
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

float crosshairVertices[] = {
        // Verticale lijn (x = 0)
        0.0f, -0.015f, 0.0f, 0.015f,
        // Horizontale lijn (y = 0)
        -0.01f, 0.0f, 0.01f, 0.0f};


int Game::run() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }
    GLFWmonitor *primary = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(primary);
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
    GLFWwindow *window = glfwCreateWindow(width, height, "BudgetBlocks", NULL, NULL);
    // Error check if the window fails to create
    if (window == NULL) {
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
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *) 0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // Texture
    Texture block("../resources/default_grass_side.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    block.texUnit(shaderProgram, "tex0", 0);

    Shader crosshairShader("../frontend/shaders/crosshair.vert", "../frontend/shaders/crosshair.frag");

    unsigned int crossVAO, crossVBO;
    glGenVertexArrays(1, &crossVAO);
    glGenBuffers(1, &crossVBO);

    glBindVertexArray(crossVAO);
    glBindBuffer(GL_ARRAY_BUFFER, crossVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(crosshairVertices), crosshairVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *) 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    std::shared_ptr<CameraView> cameraView = world->getPlayerCamera();
    cameraView->setResolution(width, height);
    Camera camera(width, height, cameraView->getPosition());

    // Main while loop
    auto startTime = static_cast<float>(glfwGetTime());

    while (true) {
        if (glfwWindowShouldClose(window)) {
            break;
        }
        float deltaTime = static_cast<float>(glfwGetTime()) - startTime;
        float fps = 1.0f / deltaTime;
        startTime = static_cast<float>(glfwGetTime());

        world->update(deltaTime);

        // Specify the color of the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Tell OpenGL which Shader Program we want to use
        shaderProgram.Activate();

        handleInput(window);
        camera.Position = cameraView->getPosition();
        camera.Orientation = cameraView->getOrientation();
        camera.Up = cameraView->getUp();
        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

        // Binds texture so that is appears in rendering
        block.Bind();
        // Bind the VAO so OpenGL knows to use it
        VAO1.Bind();

        glm::vec3 blockCoordinate;
        // Draw blocks
        for (auto &blockPair: worldView->getBlocks()) {
            // Set the coordinate of the block;
            blockCoordinate = glm::vec3(blockPair.second.x, blockPair.second.y, blockPair.second.z);
            if (blockPair.first == BlockType::DIRT) {
                glUniform3fv(glGetUniformLocation(shaderProgram.ID, "BlockCoordinate"), 1,
                             glm::value_ptr(blockCoordinate));
                // Draw primitives, number of indices, datatype of indices, index of indices
                glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
            }
        }

        // Disable depth testing to draw on top
        glDisable(GL_DEPTH_TEST);

        // Activeer 2D shader
        crosshairShader.Activate();  // Gebruik een aparte Shader voor 2D
        glBindVertexArray(crossVAO);
        glLineWidth(2.0f);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDrawArrays(GL_LINES, 0, 4);
        glBindVertexArray(0);

        // Heractiveer depth test voor toekomstige renders
        glEnable(GL_DEPTH_TEST);

        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);
        // Take care of all GLFW events
        glfwPollEvents();
    }



    // Delete all the objects we've created
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    block.Delete();
    shaderProgram.Delete();
    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();
    return 0;
}

bool firstClick = true;
bool leftMousePressedLastFrame = false;
bool rightMousePressedLastFrame = false;

void Game::handleInput(GLFWwindow *window) {
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        world->handleInput(input::FORWARD);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        world->handleInput(input::BACKWARD);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        world->handleInput(input::LEFT);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        world->handleInput(input::RIGHT);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        world->handleInput(input::JUMP);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        world->handleInput(input::SNEAK);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        world->handleInput(input::SPRINT);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
        world->handleInput(input::UNSPRINT);
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }
    // Handles mouse inputs
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS || !firstClick) {
        // Hides mouse cursor
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        // Prevents camera from jumping on the first click
        if (firstClick) {
            glfwSetCursorPos(window, width / 2, height / 2);
            firstClick = false;
        }

        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        world->handleInput(input::CURSOR_POSITION, {static_cast<float>(mouseX), static_cast<float>(mouseY)});

        // Reset cursor to center
        glfwSetCursorPos(window, width / 2, height / 2);
    }

    int leftState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

// Detect rising edge (button just pressed this frame)
    if (leftState == GLFW_PRESS && !leftMousePressedLastFrame && !firstClick) {
        world->handleInput(input::LEFT_CLICK);  // Run once on click
    }

// Update for next frame
    leftMousePressedLastFrame = (leftState == GLFW_PRESS);

    int rightState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);

// Detect rising edge (button just pressed this frame)
    if (rightState == GLFW_PRESS && !rightMousePressedLastFrame && !firstClick) {
        world->handleInput(input::RIGHT_CLICK);  // Run once on click
    }

// Update for next frame
    rightMousePressedLastFrame = (rightState == GLFW_PRESS);
}
