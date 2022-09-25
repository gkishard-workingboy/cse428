/*
 * @FilePath: /428cpp/labs/lab1/Game.cpp
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Date: 2022-09-25 14:14:21
 * @LastEditTime: 2022-09-25 16:04:25
 * @Description: Definition to Game.h
 *
 */

#include "Game.h"

Game::Game(int argc, char *argv[])
{
    // * DESIGN CHOICE
    // * the index start from 0, instead of 2
    // * which requires us to pass in the correct argv (modify the pointer so that the first string should be player name)
    for (int i = 0; i < argc; ++i)
    {
        // use c-style string directly construct c++ string object
        players.emplace_back(argv[i]);
    }
}