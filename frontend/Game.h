//
// Created by cain on 25/04/25.
//

/**
 * @file Game.h
 * @brief The header file for the Game class
 */

#ifndef BUDGETBLOCKS_GAME_H
#define BUDGETBLOCKS_GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "../backend/World.h"
#include "../backend/WorldView.h"

/* *
 * @class Game
 * @brief The class that represents the game. It contains the main game loop and is responsible for initializing
 * the game, handling events, and rendering the game.
 */
class Game {
public:
    /**
     * @brief This runs the game loop.
     * @return 0 if the game ran successfully, or an error code if it did not.
     */
    int run();

private:
    unsigned int width, height;

    std::shared_ptr<WorldView> worldView = std::make_shared<WorldView>();

    std::unique_ptr<World> world = std::make_unique<World>(worldView);

    void handleInput(GLFWwindow *window);
};


#endif //BUDGETBLOCKS_GAME_H
