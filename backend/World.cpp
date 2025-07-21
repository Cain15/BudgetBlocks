//
// Created by cain on 25/04/25.
//

#include "World.h"
#include <glm/glm.hpp>

void World::update(float deltaTime) {

}

void World::handleInput(input info, std::pair<float, float> mousePosition) {
    switch (info) {
        case input::FORWARD:
            player->forward();
            break;
        case input::BACKWARD:
            break;
        case input::LEFT:
            break;
        case input::RIGHT:
            break;
        case input::JUMP:
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
