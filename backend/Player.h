//
// Created by cain on 25/04/25.
//

#ifndef BUDGETBLOCKS_PLAYER_H
#define BUDGETBLOCKS_PLAYER_H

struct coordinates {
    float x;
    float y;
    float z;
};

class Player {
public:
    coordinates position = {0.0f, 0.0f, 0.0f};

    [[nodiscard]] coordinates getPosition() const;

    void move(float deltaX, float deltaY, float deltaZ);
};


#endif //BUDGETBLOCKS_PLAYER_H
