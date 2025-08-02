//
// Created by cain on 19/06/25.
//

#ifndef BUDGETBLOCKS_UTILS_H
#define BUDGETBLOCKS_UTILS_H

enum class input {
    FORWARD,
    RELEASE_FORWARD,
    BACKWARD,
    RELEASE_BACKWARD,
    LEFT,
    RELEASE_LEFT,
    RIGHT,
    RELEASE_RIGHT,
    JUMP,
    SNEAK,
    SPRINT,
    UNSPRINT,
    ESCAPE,
    LEFT_CLICK,
    RIGHT_CLICK,
    CURSOR_POSITION,
};

enum BlockType {
    AIR,
    DIRT,
    GRASS,
};

struct BlockCoord {
    int x, y, z;

    bool operator==(const BlockCoord &other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};

#endif //BUDGETBLOCKS_UTILS_H
