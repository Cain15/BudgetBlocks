//
// Created by cain on 25/04/25.
//

#ifndef BUDGETBLOCKS_PLAYER_H
#define BUDGETBLOCKS_PLAYER_H

#include <glm/glm.hpp>
#include "CameraView.h"
#include "memory"

class Player {
public:
    [[nodiscard]] glm::vec3 getPosition() const;

    [[nodiscard]] const glm::vec3& getOrientation() const {
        return Orientation;
    }

    std::shared_ptr<CameraView> getCamera() {
        return playercam;
    }

    void setPosition(const glm::vec3 &position);

    void addVerticalSpeed(float speed);

    void forward();

    void releaseForward();

    void backward();

    void releaseBackward();

    void left();

    void releaseLeft();

    void right();

    void releaseRight();

    void jump();
    void notJumping();
    [[nodiscard]] bool GetIsJumping() const {
        return isJumping;
    }

    void update(float deltaTime);

    void moveHead(float mouseX, float mouseY);
private:
    glm::vec3 Position = glm::vec3(0.0f, 2.0f, 0.0f);
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

    std::shared_ptr<CameraView> playercam = std::make_shared<CameraView>(0, 0, Position);

    bool firstClick = true;

    float verticalSpeed = 0.0f; // Vertical speed for jumping
    float jumpSpeed = sqrt(2.0f * 9.81f * 1.2f); // Initial jump speed (assuming 1 meter jump height)
    bool isJumping = false; // Flag to check if the player is jumping

    bool accelerating = false; // Flag to check if the player is accelerating
    float initialSpeed = 4.317f;
    float speed = 0.0f;
    float sensitivity = 150.0f;
    glm::vec3 speedDirection = glm::vec3(0.0f, 0.0f, 0.0f); // Direction of speed

    float yaw = 90.0f;  // Facing toward negative Z
    float pitch = 0.0f;  // Level with the horizon

    void updateCamera();

    bool forwardPressed = false;
    bool backwardPressed = false;
    bool leftPressed = false;
    bool rightPressed = false;

    void updateSpeedDirection();

    void keyRelease();
};


#endif //BUDGETBLOCKS_PLAYER_H
