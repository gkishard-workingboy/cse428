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

using std::vector;
using std::pair;

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
    std::vector<unsigned int> running_tally;
    void suit_independent_evaluation(const CardSet<PinochleRank, Suit> &, std::vector<PinochleMelds> &);
    void suit_dependent_evaluation(const CardSet<PinochleRank, Suit>&, std::vector<PinochleMelds>&, Suit);
    unsigned int total_value(CardSet<PinochleRank, Suit>&);
    void make_bid(std::vector<PinochleMelds>&, CardSet<PinochleRank, Suit>&, size_t);
    PinochleContractTeam award_contract();
    void print_contract_result(std::ostream&, PinochleContractTeam);
    std::string to_string(const PinochleContractTeam&);
    void initialize_play_order(vector<int>& player_order, PinochleContractTeam contract_team);
    Card<PinochleRank, Suit> play_leading_card(CardSet<PinochleRank, Suit>&, CardSet<PinochleRank, Suit>&);
    void add_to_trick(CardSet<PinochleRank, Suit>&, CardSet<PinochleRank, Suit>&, PinochleRank, Suit);
    PinochleRank trump_led_play(CardSet<PinochleRank, Suit>&, CardSet<PinochleRank, Suit>&, PinochleRank);
    pair<PinochleRank, PinochleRank> non_trump_led_play(CardSet<PinochleRank, Suit>&, CardSet<PinochleRank, Suit>&, pair<PinochleRank, PinochleRank>, Suit);
    int do_trick(PinochleContractTeam, vector<int>&);
    int player_with_card(CardSet<PinochleRank, Suit>&, vector<int>&, PinochleRank, Suit);
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
