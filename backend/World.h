//
// Created by cain on 25/04/25.
//

#ifndef BUDGETBLOCKS_WORLD_H
#define BUDGETBLOCKS_WORLD_H

#include <memory>
#include "Player.h"
#include "CameraView.h"
#include "../utils.h"
#include "Chunk.h"
#include "Block.h"
#include <unordered_map>
#include "WorldView.h"

struct ChunkCoordHash {
    std::size_t operator()(const ChunkCoord &coord) const {
        std::size_t hx = std::hash<int>()(coord.x);
        std::size_t hy = std::hash<int>()(coord.y);
        std::size_t hz = std::hash<int>()(coord.z);
        return hx ^ (hy << 1) ^ (hz << 2);
    }
};

class World {
public:
    explicit World(std::shared_ptr<WorldView>);

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

    std::unordered_map<ChunkCoord, std::unique_ptr<Chunk>, ChunkCoordHash> chunkMap;

    const Block &getBlock(int x, int y, int z) const;

    ChunkCoord PlayerChunkCoord = {0, 0, 0}; // The chunk the player is currently in

    void loadChunk(int x, int y, int z);

    ChunkCoord getChunkCoord(int x, int y, int z) {
        return {floorDiv(x,16), floorDiv(y,16), floorDiv(z,16)};
    }

    std::shared_ptr<WorldView> worldView;

    void updateWorldView();

    int floorDiv(int a, int b) {
        return (a >= 0) ? (a / b) : ((a - b + 1) / b);
    }

    int ceilFloat(float a) {
        if (a >= 0) {
            return ceilf(a);
        } else {
            return ceilf(a);
        }
    }

    int roundFloat(float a) {
        if (a >= 0) {
            return floorf(a + 0.5f);
        } else {
            return ceilf(a - 0.5f);
        }
    }

    int positive_mod(int a, int b) {
        return (a % b + b) % b;
    }

    float absolute(float a) {
        return (a >= 0) ? a : -a;
    }

    bool playerJumped = false;

    void placeBlock();

    void breakBlock();
};




#endif //BUDGETBLOCKS_WORLD_H
