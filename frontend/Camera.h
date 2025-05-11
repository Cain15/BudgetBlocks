//
// Created by cain on 6/05/25.
//

#ifndef BUDGETBLOCKS_CAMERA_H
#define BUDGETBLOCKS_CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <GLFW/glfw3.h>

#include "Shader.h"

class Camera {
public:
    glm::vec3 Position;
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

    int width;
    int height;

    bool firstClick = true;

    float initialSpeed = 0.05f;
    float speed = initialSpeed;
    float sensitivity = 175.0f;

    float yaw = -90.0f;  // Facing toward negative Z
    float pitch = 0.0f;  // Level with the horizon


    Camera(int width, int height, glm::vec3 position);

    void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
    void Inputs(GLFWwindow* window);
};


#endif //BUDGETBLOCKS_CAMERA_H
