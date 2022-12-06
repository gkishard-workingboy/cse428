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

enum class PinochleContractTeam
{
    team1,
    team2,
    misdeal
};

std::ostream &operator<<(std::ostream &, const PinochleMelds &);

class PinochleGame : public Game
{
private:
    Suit trump_suit;
    std::vector<unsigned int> bids;
    std::vector<unsigned int> total_meld_values;
    std::vector<unsigned int> scores;
    void suit_independent_evaluation(const CardSet<PinochleRank, Suit> &, std::vector<PinochleMelds> &);
    void suit_dependent_evaluation(const CardSet<PinochleRank, Suit>&, std::vector<PinochleMelds>&, Suit);
    void make_bid(std::vector<PinochleMelds>&, CardSet<PinochleRank, Suit>&, size_t);
    PinochleContractTeam award_contract();
    std::string to_string(const PinochleContractTeam&);
    Card<PinochleRank, Suit> first_trick(CardSet<PinochleRank, Suit>&, CardSet<PinochleRank, Suit>&);
    bool trump_led_trick(CardSet<PinochleRank, Suit>&, CardSet<PinochleRank, Suit>&, Card<PinochleRank, Suit>&);
    void play_tricks(PinochleContractTeam);
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
    //make bids
    void make_bids(std::vector<unsigned int>&);

public:
    PinochleGame(int, const char *[]);
    // virtual function: how to play Pinochle Game
    virtual int play() override;
    static unsigned int PinochleMeldsPointValue[];
};

#endif
