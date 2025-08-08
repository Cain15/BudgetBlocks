//
// Created by cain on 25/04/25.
//

#ifndef BUDGETBLOCKS_PLAYER_H
#define BUDGETBLOCKS_PLAYER_H

#include <glm/glm.hpp>
#include "CameraView.h"
#include "memory"

struct HitBox {
    glm::vec3 min; // Minimum corner of the bounding box
    glm::vec3 max; // Maximum corner of the bounding box
    float getWidth() const {
        return max.x - min.x;
    }

    float getHeight() const {
        return max.y - min.y;
    }

    HitBox(const glm::vec3 &min, const glm::vec3 &max) : min(min), max(max) {}
};

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

    void updateHitBox();

    void moveHead(float mouseX, float mouseY);

    HitBox hitBox = HitBox(glm::vec3(-0.25f, 0.01f, -0.25f), glm::vec3(0.25f, 1.8f, 0.25f)); // Player's hitbox
private:
    glm::vec3 Position = glm::vec3(0.0f, 1.8f, 0.0f);
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

    glm::vec3 lastPosition = Position;
public:
    const glm::vec3 &getLastPosition() const;

private:
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
