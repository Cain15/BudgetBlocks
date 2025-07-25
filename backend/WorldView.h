//
// Created by cain on 25/07/25.
//

#ifndef BUDGETBLOCKS_WORLDVIEW_H
#define BUDGETBLOCKS_WORLDVIEW_H

#include <vector>
#include "../utils.h"

class WorldView {
private:
    std::vector<std::pair<BlockType, BlockCoord>> blocks; // Vector of pairs containing block type and coordinates
public:
    void setBlocks(const std::vector<std::pair<BlockType, BlockCoord>> &newBlocks) {
        blocks = newBlocks;
    }

    [[nodiscard]] const std::vector<std::pair<BlockType, BlockCoord>> &getBlocks() const {
        return blocks;
    }
};


#endif //BUDGETBLOCKS_WORLDVIEW_H
