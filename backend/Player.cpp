//
// Created by cain on 25/04/25.
//

#include "Player.h"
#include <iostream>

glm::vec3 Player::getPosition() const {
    return Position;
}

void Player::forward() {
    if (isJumping) {
        // If the player is jumping, you have less momentum
        Position += 0.1f * speed * glm::normalize(glm::vec3(Orientation.x, 0.0f, Orientation.z));
    } else {
        Position += speed * glm::normalize(glm::vec3(Orientation.x, 0.0f, Orientation.z));
    }
}

void Player::moveHead(float mouseX, float mouseY) {
    int height = playercam->getResolution().second;
    int width = playercam->getResolution().first;
    float rotX = sensitivity * (float) (mouseY - (height / 2)) / height;
    float rotY = sensitivity * (float) (mouseX - (width / 2)) / width;

    // Update pitch and yaw
    pitch -= rotX; // Inverted Y
    yaw += rotY;

    // Clamp pitch to avoid gimbal lock
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    // Update Orientation from yaw and pitch
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    Orientation = glm::normalize(direction);
    updateCamera();
}

void Player::updateCamera() {
    playercam->setPosition(Position);
    playercam->setOrientation(Orientation);
    playercam->setUp(Up);
}

void Player::backward() {
    Position -= speed * glm::normalize(glm::vec3(Orientation.x, 0.0f, Orientation.z));
}

void Player::left() {
    Position += 0.8f * speed * -glm::normalize(glm::cross(Orientation, Up));
}

void Player::right() {
    Position += 0.8f * speed * glm::normalize(glm::cross(Orientation, Up));
}

void Player::jump() {
    if (!isJumping) {
        verticalSpeed = jumpSpeed; // Set the initial vertical speed for the jump
        isJumping = true; // Set the jumping flag to true
    }
}

void Player::setPosition(const glm::vec3 &position) {
    Position = position;
    updateCamera();
}

void Player::update(float deltaTime) {
    Position += glm::vec3(0.0f, verticalSpeed * deltaTime, 0.0f); // Apply vertical speed to position
    updateCamera();
}

void Player::notJumping() {
    isJumping = false;
    verticalSpeed = 0.0f; // Reset vertical speed when not jumping
}

void Player::addVerticalSpeed(float speed) {
    verticalSpeed += speed;
}
