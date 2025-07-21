//
// Created by cain on 25/04/25.
//

#ifndef BUDGETBLOCKS_PLAYER_H
#define BUDGETBLOCKS_PLAYER_H

#include <glm/glm.hpp>
#include "../frontend/Camera.h"
#include "memory"

class Player {
public:
    [[nodiscard]] glm::vec3 getPosition() const;

    std::shared_ptr<Camera> getCamera() {
        return playercam;
    }

    void forward();

    void moveHead(float mouseX, float mouseY);
private:
    glm::vec3 Position = glm::vec3(0.0f, 2.0f, 0.0f);
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

    std::shared_ptr<Camera> playercam = std::make_shared<Camera>(0, 0, Position);

    bool firstClick = true;

    float initialSpeed = 0.05f;
    float speed = initialSpeed;
    float sensitivity = 175.0f;

    float yaw = -90.0f;  // Facing toward negative Z
    float pitch = 0.0f;  // Level with the horizon
};


#endif //BUDGETBLOCKS_PLAYER_H
