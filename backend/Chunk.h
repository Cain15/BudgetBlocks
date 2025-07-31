//
// Created by cain on 25/04/25.
//

#ifndef BUDGETBLOCKS_CHUNK_H
#define BUDGETBLOCKS_CHUNK_H

#include <vector>
#include "Block.h"
#include "../utils.h"
#include <cassert>

struct ChunkCoord {
    int x, y, z;

    bool operator==(const ChunkCoord &other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};

const int CHUNK_SIZE = 16;


class Chunk {
private:
    std::vector<Block> blocks;
public:
    Chunk();

    [[nodiscard]] const Block &getBlock(int x, int y, int z) const{
        assert(inBounds(x, y, z));
        return blocks[x + CHUNK_SIZE * (y + CHUNK_SIZE * z)];
    }

    [[nodiscard]] std::vector<std::pair<BlockType, BlockCoord>> getBlocks() const;

    void replaceBlock(int x, int y, int z, BlockType type);

    [[nodiscard]] std::vector<Block> getBlockVector() const {
        return blocks;
    }
private:
     bool inBounds(int x, int y, int z) const {
        return x >= 0 && x < CHUNK_SIZE && y >= 0 && y < CHUNK_SIZE && z >= 0 && z < CHUNK_SIZE;
    }
};


#endif //BUDGETBLOCKS_CHUNK_H
