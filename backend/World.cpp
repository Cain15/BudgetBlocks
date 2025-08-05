//
// Created by cain on 25/04/25.
//

#include "World.h"
#include <glm/glm.hpp>
#include <iostream>
#include <stb/stb_perlin.h>

void World::update(float deltaTime) {
    player->update(deltaTime);

    glm::vec3 playerPosition = player->getPosition();
    if (playerPosition.x < 0.0f) {
        playerPosition.x = 0.0f; // Prevent player from going out of bounds
        player->setPosition(
                glm::vec3(0.0f, playerPosition.y, playerPosition.z)); // Prevent player from going out of bounds
    }
    if (playerPosition.y < 0.0f) {
        playerPosition.y = 0.0f; // Prevent player from going out of bounds
        player->setPosition(
                glm::vec3(playerPosition.x, 0.0f, playerPosition.z)); // Prevent player from going out of bounds
        player->notJumping(); // Reset jump state if player is below ground
    }
    if (playerPosition.z < 0.0f) {
        playerPosition.z = 0.0f; // Prevent player from going out of bounds
        player->setPosition(
                glm::vec3(playerPosition.x, playerPosition.y, 0.0f)); // Prevent player from going out of bounds
    }
    ChunkCoord currentChunkCoord = getChunkCoord(playerPosition.x, playerPosition.z);
    if (currentChunkCoord != PlayerChunkCoord) {
        // Player has moved to a different chunk, load the new chunk
        loadChunk(currentChunkCoord.x, currentChunkCoord.z);
        loadChunk(currentChunkCoord.x + 1, currentChunkCoord.z);
        loadChunk(currentChunkCoord.x, currentChunkCoord.z + 1);
        loadChunk(currentChunkCoord.x + 1, currentChunkCoord.z + 1);
        if (currentChunkCoord.x - 1 >= 0) {
            loadChunk(currentChunkCoord.x - 1, currentChunkCoord.z);
            loadChunk(currentChunkCoord.x - 1, currentChunkCoord.z + 1);
            if (currentChunkCoord.z - 1 >= 0) {
                loadChunk(currentChunkCoord.x - 1, currentChunkCoord.z - 1);
            }
        }
        if (currentChunkCoord.z - 1 >= 0) {
            loadChunk(currentChunkCoord.x, currentChunkCoord.z - 1);
            loadChunk(currentChunkCoord.x + 1, currentChunkCoord.z - 1);
        }
        PlayerChunkCoord = currentChunkCoord;
        updateWorldView();
    }

    // Make gravity work
    bool isOnSolidGround = false;
    // Check if the player is on solid ground
    const Block &blockBelow = getBlock(roundFloat(playerPosition.x),
                                       ceilFloat(playerPosition.y) - 2, // Check the block below the player
                                       roundFloat(playerPosition.z));
    if (blockBelow.getType() != BlockType::AIR && playerPosition.y - 2.0f <= ceilFloat(playerPosition.y) - 2.0f) {
        isOnSolidGround = true;
    }
    if (!isOnSolidGround) {
        player->addVerticalSpeed(-9.81f * deltaTime); // Apply gravity
    } else if (!playerJumped) {
        player->setPosition(glm::vec3(playerPosition.x, ceilFloat(playerPosition.y), playerPosition.z));
        player->notJumping();
    } else {
        playerJumped = false; // Reset jump flag after handling jump
    }
}

void World::handleInput(input info, std::pair<float, float> mousePosition) {
    switch (info) {
        case input::FORWARD:
            player->forward();
            break;
        case input::RELEASE_FORWARD:
            player->releaseForward();
            break;
        case input::BACKWARD:
            player->backward();
            break;
        case input::RELEASE_BACKWARD:
            player->releaseBackward();
            break;
        case input::LEFT:
            player->left();
            break;
        case input::RELEASE_LEFT:
            player->releaseLeft();
            break;
        case input::RIGHT:
            player->right();
            break;
        case input::RELEASE_RIGHT:
            player->releaseRight();
            break;
        case input::JUMP:
            if (!player->GetIsJumping()) {
                player->jump();
                playerJumped = true;
            }
            break;
        case input::SNEAK:
            player->setPosition(player->getPosition() - glm::vec3(0.0f, 0.1f, 0.0f)); // Move down slightly
            break;
        case input::SPRINT:
            // Handle sprint logic here
            break;
        case input::ESCAPE:
            // Handle escape logic here
            break;
        case input::LEFT_CLICK:
            placeBlock();
            break;
        case input::RIGHT_CLICK:
            breakBlock();
            break;
        case input::CURSOR_POSITION:
            player->moveHead(mousePosition.first, mousePosition.second);
            break;
    }
}

const Block &World::getBlock(int x, int y, int z) const {
    ChunkCoord coord{x / 16, z / 16};
    auto it = chunkMap.find(coord);
    if (it == chunkMap.end()) {
        std::cerr << "Chunk not found at coordinates: " << coord.x << ", " << coord.z << std::endl;
        static Block airBlock{}; // or throw, depending on your design
        return airBlock;
    }

    auto mod = [](int a, int b) { return (a % b + b) % b; };
    return it->second->getBlock(mod(x, 16), y, mod(z, 16));
}

World::World(std::shared_ptr<WorldView> view) : worldView(std::move(view)) {
    // Load the initial chunks
    loadChunk(0, 0);
    loadChunk(1, 0);
    loadChunk(0, 1);
    loadChunk(1, 1);
    // Move player to a solid ground position, not in a block
    for (int y = 0; y < 30 ; y++) {
        if (getBlock(0, y, 0).getType() != BlockType::AIR) {
            player->setPosition(glm::vec3(0.0f, y + 2.0f, 0.0f)); // Set player above the ground
            break;
        }
    }
    updateWorldView();
}

void World::loadChunk(int x, int z) {
    ChunkCoord coord = {x, z};
    if (chunkMap.find(coord) == chunkMap.end()) {
        auto chunk = std::make_unique<Chunk>();

        for (int cx = 0; cx < 16; ++cx) {
            for (int cz = 0; cz < 16; ++cz) {
                int worldX = x * 16 + cx;
                int worldZ = z * 16 + cz;

                // Scale to avoid too steep terrain
                float noiseX = worldX * 0.05f;
                float noiseZ = worldZ * 0.05f;

                // Get Perlin noise value
                float height = stb_perlin_noise3(noiseX, 0.0f, noiseZ, 0, 0, 0);

                // Scale to desired terrain height
                int terrainHeight = static_cast<int>(height * 10.0f + 20.0f); // e.g., from y = 10 to 30

                for (int y = 0; y < terrainHeight; ++y) {
                    chunk->replaceBlock(cx, y, cz, BlockType::GRASS); // Replace with your actual block setting
                }
            }
        }

        chunkMap[coord] = std::move(chunk);
    }
}

void World::updateWorldView() {
    std::vector<ChunkCoord> loadedChunks = {{PlayerChunkCoord.x, PlayerChunkCoord.z},
                                            {PlayerChunkCoord.x + 1, PlayerChunkCoord.z},
                                            {PlayerChunkCoord.x, PlayerChunkCoord.z + 1},
                                            {PlayerChunkCoord.x + 1, PlayerChunkCoord.z + 1},};
    if (PlayerChunkCoord.x - 1 >= 0) {
        loadedChunks.emplace_back(PlayerChunkCoord.x - 1, PlayerChunkCoord.z);
        loadedChunks.emplace_back(PlayerChunkCoord.x - 1, PlayerChunkCoord.z + 1);
        if (PlayerChunkCoord.z - 1 >= 0) {
            loadedChunks.emplace_back(PlayerChunkCoord.x - 1, PlayerChunkCoord.z - 1);
        }
    }
    if (PlayerChunkCoord.z - 1 >= 0) {
        loadedChunks.emplace_back(PlayerChunkCoord.x, PlayerChunkCoord.z - 1);
        loadedChunks.emplace_back(PlayerChunkCoord.x + 1, PlayerChunkCoord.z - 1);
    }


    std::vector<std::pair<BlockType, BlockCoord>> blockList;
    for (const auto &chunkCoord: loadedChunks) {

        for (auto &BlockPair: chunkMap[chunkCoord]->getBlocks()) {
            BlockPair.second = BlockCoord{BlockPair.second.x + chunkCoord.x * CHUNK_SIZE,
                                          BlockPair.second.y,
                                          BlockPair.second.z + chunkCoord.z * CHUNK_SIZE};
            blockList.emplace_back(BlockPair.first, BlockPair.second);
        }
    }

    worldView->setBlocks(blockList);
}

void World::placeBlock() {
    for (int i = 10; i < 70; i++) {
        glm::vec3 coord = player->getPosition() + (player->getOrientation() * (float) i * 0.1f);
        const Block &block = getBlock(roundFloat(coord.x), roundFloat(coord.y), roundFloat(coord.z));
        if (block.getType() != BlockType::AIR) {
            int j = 0;
            while (getBlock(roundFloat(coord.x), roundFloat(coord.y), roundFloat(coord.z)).getType() !=
                   BlockType::AIR && j < i) {
                coord -= player->getOrientation() * 0.1f;
                j++;
            }
            if (absolute(coord.x - player->getPosition().x) <= 1.0f &&
                absolute(coord.y - player->getPosition().y) <= 2.0f && absolute(coord.z - player->getPosition().z) <= 1.0f) {
                break;
            }
            ChunkCoord chunkCoord = getChunkCoord(roundFloat(coord.x), roundFloat(coord.z));
            if (chunkMap.find(chunkCoord) == chunkMap.end()) {
                loadChunk(chunkCoord.x, chunkCoord.z);
            }
            chunkMap[chunkCoord]->replaceBlock(positive_mod(roundFloat(coord.x), CHUNK_SIZE),
                                               roundFloat(coord.y),
                                               positive_mod(roundFloat(coord.z), CHUNK_SIZE), BlockType::DIRT);
            updateWorldView();
            break;
        }

    }
}

void World::breakBlock() {
    for (int i = 10; i < 60; i++) {
        glm::vec3 coord = player->getPosition() + (player->getOrientation() * (float) i * 0.1f);
        const Block &block = getBlock(roundFloat(coord.x), roundFloat(coord.y), roundFloat(coord.z));
        std::cout << "Checking solid at: " << roundFloat(coord.x) << ", " << roundFloat(coord.y) << ", "
                  << roundFloat(coord.z) << std::endl;
        if (block.getType() != BlockType::AIR) {
            ChunkCoord chunkCoord = getChunkCoord(roundFloat(coord.x), roundFloat(coord.z));
            if (chunkMap.find(chunkCoord) == chunkMap.end()) {
                loadChunk(chunkCoord.x, chunkCoord.z);
            }
            chunkMap[chunkCoord]->replaceBlock(positive_mod(roundFloat(coord.x), CHUNK_SIZE),
                                               roundFloat(coord.y),
                                               positive_mod(roundFloat(coord.z), CHUNK_SIZE), BlockType::AIR);
            updateWorldView();
            break;
        }
    }
}
