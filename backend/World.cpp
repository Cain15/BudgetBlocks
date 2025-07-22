//
// Created by cain on 25/04/25.
//

#include "World.h"
#include <glm/glm.hpp>

void World::update(float deltaTime) {
    player->update(deltaTime);

    // Make gravity work
    if (player->getPosition().y > 2.0f) {
        player->addVerticalSpeed(- 9.81f * deltaTime); // Apply gravity
    } else {
        player->setPosition(glm::vec3(player->getPosition().x, 2.0f, player->getPosition().z));
        player->notJumping();
    }
}

void World::handleInput(input info, std::pair<float, float> mousePosition) {
    switch (info) {
        case input::FORWARD:
            player->forward();
            break;
        case input::BACKWARD:
            player->backward();
            break;
        case input::LEFT:
            player->left();
            break;
        case input::RIGHT:
            player->right();
            break;
        case input::JUMP:
            player->jump();
            break;
        case input::SNEAK:
            break;
        case input::SPRINT:
            // Handle sprint logic here
            break;
        case input::ESCAPE:
            // Handle escape logic here
            break;
        case input::LEFT_CLICK:
            // Handle left click logic here
            break;
        case input::RIGHT_CLICK:
            // Handle right click logic here
            break;
        case input::CURSOR_POSITION:
            player->moveHead(mousePosition.first, mousePosition.second);
            break;
    }
}
