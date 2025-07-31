//
// Created by cain on 25/04/25.
//

#include "Chunk.h"

std::vector<std::pair<BlockType, BlockCoord>> Chunk::getBlocks() const {
    std::vector<std::pair<BlockType, BlockCoord>> blockList;

    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int y = 0; y < CHUNK_SIZE; ++y) {
            for (int z = 0; z < CHUNK_SIZE; ++z) {
                int index = x + CHUNK_SIZE * (y + CHUNK_SIZE * z);
                const Block& block = blocks[index];

                if (block.getType()) {
                    blockList.emplace_back(block.getType(), BlockCoord{x, y, z});
                }
            }
        }
    }

    return blockList;
}

Chunk::Chunk() : blocks(CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE, Block(BlockType::AIR)) {
    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int z = 0; z < CHUNK_SIZE; ++z) {
            blocks[x + CHUNK_SIZE * (CHUNK_SIZE * z)] = Block(BlockType::DIRT);
        }
    }
}

void Chunk::replaceBlock(int x, int y, int z, BlockType type) {
    assert(inBounds(x, y, z));
    blocks[x + CHUNK_SIZE * (y + CHUNK_SIZE * z)] = Block(type);
}
