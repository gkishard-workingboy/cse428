/*
 * @FilePath: /428cpp/labs/lab1/PinochleGame.h
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Date: 2022-09-25 14:31:15
 * @LastEditTime: 2022-09-25 16:07:50
 * @Description:
 *
 */

#ifndef _PINOCHLEGAME_H
#define _PINOCHLEGAME_H

#include "Game.h"
#include "Suit.h"
#include "PinochleDeck.h"
#include <vector>
#include <ostream>
#include <istream>

class PinochleGame : public Game
{
public:
    PinochleGame(int, char *[]);
    // virtual function: how to play Pinochle Game
    virtual int play() override;

protected:
    PinochleDeck deck;
    // store the hands of each player in game
    std::vector<CardSet<PinochleRank, Suit>> hands;
    virtual void deal();

    // * DESIGN:
    // * modularize play() by extract parts to 3 member methods
    // print all players' name and hand
    void print(std::ostream &, const std::size_t);
    // collect cards back from players
    void collectAll();
    // ask for whether need to stop the game
    bool askForStop(std::ostream &, std::istream &);
};

#endif