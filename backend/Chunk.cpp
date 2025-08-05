//
// Created by cain on 25/04/25.
//

#include <iostream>
#include "Chunk.h"

std::vector<std::pair<BlockType, BlockCoord>> Chunk::getBlocks() const {
    std::vector<std::pair<BlockType, BlockCoord>> blockList;

    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int y = 0; y < CHUNK_HEIGHT; ++y) {
            for (int z = 0; z < CHUNK_SIZE; ++z) {
                int index = getIndex(x, y, z);
                const Block& block = blocks[index];

                if (block.getType()) {
                    blockList.emplace_back(block.getType(), BlockCoord{x, y, z});
                }
            }
        }
    }

    return blockList;
}

Chunk::Chunk() : blocks(CHUNK_SIZE * CHUNK_HEIGHT * CHUNK_SIZE, Block(BlockType::AIR)) {

}

void Chunk::replaceBlock(int x, int y, int z, BlockType type) {
    if (inBounds(x, y, z)) {
        blocks[getIndex(x, y, z)] = Block(type);
    } else {
        std::cerr << "Error: Attempted to replace block out of bounds at (" << x << ", " << y << ", " << z << ")\n";
    }
}
