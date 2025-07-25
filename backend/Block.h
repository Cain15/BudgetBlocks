//
// Created by cain on 25/04/25.
//

#ifndef BUDGETBLOCKS_BLOCK_H
#define BUDGETBLOCKS_BLOCK_H

#include "../utils.h"

class Block {
private:
    BlockType type;
public:
    explicit Block(BlockType type = AIR) : type(type) {}

    [[nodiscard]] BlockType getType() const {
        return type;
    }
};


#endif //BUDGETBLOCKS_BLOCK_H
