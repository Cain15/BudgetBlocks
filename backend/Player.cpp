//
// Created by cain on 25/04/25.
//

#include "Player.h"
#include <iostream>

glm::vec3 Player::getPosition() const {
    return Position;
}

void Player::forward() {
    std::cout << "Player moving forward" << std::endl;
    Position += speed * glm::normalize(glm::vec3(Orientation.x, 0.0f, Orientation.z));
    std::cout << "New position: (" << Position.x << ", " << Position.y << ", " << Position.z << ")" << std::endl;
}

void Player::moveHead(float mouseX, float mouseY) {
    float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
    float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

    // Update pitch and yaw
    pitch -= rotX; // Inverted Y
    yaw   += rotY;

    // Clamp pitch to avoid gimbal lock
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    // Update Orientation from yaw and pitch
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    Orientation = glm::normalize(direction);
}
