#include "Game.h"

Game::Game(int argc, char* argv[]) {
    // * DESIGN CHOICE
    // * the index start from 0, instead of 2
    // * which requires us to pass in the correct argv (modify the pointer so that the first string should be player name)
    for (int i = 0; i < argc; ++i)
    {
        // use c-style string directly construct c++ string object
        players.emplace_back(argv[i]);
    }
}