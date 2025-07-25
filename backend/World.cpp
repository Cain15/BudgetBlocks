//
// Created by cain on 25/04/25.
//

#include "World.h"
#include <glm/glm.hpp>
#include <iostream>

void World::update(float deltaTime) {
    player->update(deltaTime);

    glm::vec3 playerPosition = player->getPosition();
    ChunkCoord currentChunkCoord = getChunkCoord(playerPosition.x, playerPosition.y, playerPosition.z);
    if (currentChunkCoord != PlayerChunkCoord) {
        // Player has moved to a different chunk, load the new chunk
        loadChunk(currentChunkCoord.x, currentChunkCoord.y, currentChunkCoord.z);
        PlayerChunkCoord = currentChunkCoord;
        updateWorldView();
    }

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

const Block &World::getBlock(int x, int y, int z) const {
    ChunkCoord coord{x / 16, y / 16, z / 16};
    auto it = chunkMap.find(coord);
    if (it == chunkMap.end()) {
        std::cerr << "Chunk not found at coordinates: "
                  << coord.x << ", " << coord.y << ", " << coord.z << std::endl;
        static Block airBlock{}; // or throw, depending on your design
        return airBlock;
    }

    auto mod = [](int a, int b) { return (a % b + b) % b; };
    return it->second->getBlock(mod(x, 16), mod(y, 16), mod(z, 16));
}

World::World(std::shared_ptr<WorldView> view) : worldView(std::move(view)) {
    loadChunk(0, 0, 0); // Load the initial chunk
    updateWorldView();
}

void World::loadChunk(int x, int y, int z) {
    if (chunkMap.find({x, y, z}) == chunkMap.end()) {
        chunkMap[{x, y, z}] = std::make_unique<Chunk>();
    }
    std::cout << "Loaded chunk at coordinates: " << x << ", " << y << ", " << z << std::endl;
}

void World::updateWorldView() {
    std::vector<std::pair<BlockType, BlockCoord>> blockList = chunkMap[PlayerChunkCoord]->getBlocks();

    for (auto &BlockPair : blockList) {
        BlockPair.second = BlockCoord{
            BlockPair.second.x + PlayerChunkCoord.x * CHUNK_SIZE,
            BlockPair.second.y + PlayerChunkCoord.y * CHUNK_SIZE,
            BlockPair.second.z + PlayerChunkCoord.z * CHUNK_SIZE
        };
    }

    worldView->setBlocks(blockList);
}
