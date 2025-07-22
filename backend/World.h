//
// Created by cain on 25/04/25.
//

#ifndef BUDGETBLOCKS_WORLD_H
#define BUDGETBLOCKS_WORLD_H

#include <memory>
#include "Player.h"
#include "CameraView.h"
#include "../utils.h"

class World {
public:
    std::shared_ptr<Player> player = std::make_shared<Player>();

    void update(float deltaTime);

    void handleInput(input info, std::pair<float, float> mousePosition = {0.0f, 0.0f});

    std::shared_ptr<CameraView> getPlayerCamera() {
        return player->getCamera();
    }
private:
    float tickRate = 20.0f; // 20 ticks per second
    float tickInterval = 1.0f / tickRate; // Interval between ticks in seconds
    float accumulator = 0.0f; // Accumulator for time
};


#endif //BUDGETBLOCKS_WORLD_H
