//
// Created by cain on 25/04/25.
//

#include "Player.h"
#include <iostream>
#include <algorithm>

glm::vec3 Player::getPosition() const {
    return Position;
}

void Player::forward() {
    forwardPressed = true;
    accelerating = true;
    updateSpeedDirection();
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
    backwardPressed = true;
    accelerating = true;
    updateSpeedDirection();
}

void Player::left() {
    leftPressed = true;
    accelerating = true;
    updateSpeedDirection();
}

void Player::right() {
    rightPressed = true;
    accelerating = true;
    updateSpeedDirection();
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
    Position += speed * speedDirection * (deltaTime); // Apply horizontal speed to position
    if (accelerating && !isJumping) {
        speed = std::min(initialSpeed, speed + 4.317f * deltaTime); // Accelerate up to a maximum speed
    } else if (!isJumping){
        speed = std::max(0.0f, speed - 4.317f * deltaTime); // Gradually reduce speed when not accelerating
    }
    updateCamera();
}

void Player::notJumping() {
    isJumping = false;
    verticalSpeed = 0.0f; // Reset vertical speed when not jumping
}

void Player::addVerticalSpeed(float speed) {
    verticalSpeed += speed;
}

void Player::releaseForward() {
    forwardPressed = false;
    keyRelease();
}

void Player::updateSpeedDirection() {
    glm::vec3 forward = glm::vec3(Orientation.x, 0.0f, Orientation.z);
    if (glm::length(forward) > 0.0001f) {
        forward = glm::normalize(forward);
    }

    speedDirection = glm::vec3(0.0f);
    if (forwardPressed) {
        speedDirection += forward;
    }
    if (backwardPressed) {
        speedDirection = glm::vec3(speedDirection.x - forward.x, speedDirection.y - forward.y, speedDirection.z - forward.z); // Move backward in the opposite direction
    }

    glm::vec3 right = glm::normalize(glm::cross(Orientation, Up));
    if (leftPressed) {
        speedDirection -= right;
    }
    if (rightPressed) {
        speedDirection += right;
    }

    if (glm::length(speedDirection) > 0.0001f) {
        speedDirection = glm::normalize(speedDirection);
    }
}

void Player::releaseBackward() {
    backwardPressed = false;
    keyRelease();
}

void Player::keyRelease() {
    if (!forwardPressed && !backwardPressed && !leftPressed && !rightPressed) {
        accelerating = false; // Stop accelerating if no keys are pressed
    }
    updateSpeedDirection(); // Update speed direction based on current key states
}

void Player::releaseLeft() {
    leftPressed = false;
    keyRelease();
}

void Player::releaseRight() {
    rightPressed = false;
    keyRelease();
}