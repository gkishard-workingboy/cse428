/*
 * @FilePath: /428cpp/labs/lab1/Game.h
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Date: 2022-09-25 14:14:14
 * @LastEditTime: 2022-09-25 16:05:09
 * @Description: Declaration of abstract class Game.
 *
 */

#ifndef _GAME_H
#define _GAME_H

#include <string>
#include <vector>

// abstract class
class Game
{
public:
    static const int firstPlayerIndex = 2;
    Game(int, const char *[]);
    // pure virtual function play
    virtual int play() = 0;

protected:
    std::vector<std::string> players;
    size_t dealer;
    std::vector<unsigned int> scores;
};

#endif
