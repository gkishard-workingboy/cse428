/*
 * @FilePath: /428cpp/labs/lab2/PinochleGame.h
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Date: 2022-09-25 14:31:15
 * @LastEditTime: 2022-10-24 16:49:45
 * @Description: Declaration of pinochle game class derived from base game class.
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
#include <algorithm>
#include <string>

const int PINOCHLE_NUM_ITEMS = 15;

enum class PinochleMelds
{
    dix,
    offsuitmarriage,
    fortyjacks,
    pinochle,
    insuitmarriage,
    sixtyqueens,
    eightykings,
    hundredaces,
    insuitrun,
    doublepinochle,
    fourhundredjacks,
    sixhundredqueens,
    eighthundredkings,
    thousandaces,
    insuitdoublerun
};

std::ostream &operator<<(std::ostream &, const PinochleMelds &);

class PinochleGame : public Game
{
private:
    Suit trump_suit;
    void suit_independent_evaluation(const CardSet<PinochleRank, Suit> &, std::vector<PinochleMelds> &);
    void suit_dependent_evaluation(const CardSet<PinochleRank, Suit>&, std::vector<PinochleMelds>&, Suit);

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

public:
    PinochleGame(int, const char *[]);
    // virtual function: how to play Pinochle Game
    virtual int play() override;
    static unsigned int PinochleMeldsPointValue[];
};

#endif
