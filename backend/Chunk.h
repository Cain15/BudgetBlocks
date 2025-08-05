//
// Created by cain on 25/04/25.
//

#ifndef BUDGETBLOCKS_CHUNK_H
#define BUDGETBLOCKS_CHUNK_H

#include <vector>
#include "Block.h"
#include <cassert>

struct ChunkCoord {
    int x, z;

    bool operator==(const ChunkCoord &other) const {
        return x == other.x && z == other.z;
    }

    bool operator!=(const ChunkCoord& other) const {
        return x != other.x || z != other.z;
    }
};

const int CHUNK_SIZE = 16;
const int CHUNK_HEIGHT = 32; // Assuming a fixed height for simplicity


class Chunk {
private:
    std::vector<Block> blocks;
public:
    Chunk();

    [[nodiscard]] const Block &getBlock(int x, int y, int z) const{
        if (inBounds(x, y, z)){
            return blocks[getIndex(x, y, z)];
        } else {
            static Block airBlock{BlockType::AIR}; // Return an air block if out of bounds
            return airBlock;
        }
    }

    [[nodiscard]] std::vector<std::pair<BlockType, BlockCoord>> getBlocks() const;

    void replaceBlock(int x, int y, int z, BlockType type);

    [[nodiscard]] std::vector<Block> getBlockVector() const {
        return blocks;
    }
private:
     static bool inBounds(int x, int y, int z) {
        return x >= 0 && x < CHUNK_SIZE && y >= 0 && y < CHUNK_HEIGHT && z >= 0 && z < CHUNK_SIZE;
    }

    [[nodiscard]] inline int getIndex(int x, int y, int z) const {
        return x + CHUNK_SIZE * (z + CHUNK_SIZE * y);
    }
};


#endif //BUDGETBLOCKS_CHUNK_H
