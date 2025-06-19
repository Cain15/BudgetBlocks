//
// Created by cain on 25/04/25.
//

#include "Player.h"

coordinates Player::getPosition() const {
    return position;
}

void Player::move(float deltaX, float deltaY, float deltaZ) {
    position.x += deltaX;
    position.y += deltaY;
    position.z += deltaZ;
}
