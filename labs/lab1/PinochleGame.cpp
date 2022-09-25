/*
 * @FilePath: /428cpp/labs/lab1/PinochleGame.cpp
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Date: 2022-09-25 14:31:48
 * @LastEditTime: 2022-09-25 16:11:35
 * @Description: Definition to PinochleGame.h
 *
 */

#include "PinochleGame.h"
#include <iostream>
#include <string>

PinochleGame::PinochleGame(int argc, char *argv[]) : Game(argc, argv)
{
    // create as many hands as players in the game
    for (int i = 0; i < argc; ++i)
    {
        // will call default constructor of CardSet
        hands.emplace_back();
    }
}

void PinochleGame::deal()
{
    // size of a packet
    const int packet = 3;
    // number of players in game
    int numHands = hands.size();
    // repeatedly shift a packet of cards to each hand of players
    for (int p = 0; !deck.isEmpty(); p = (p + 1) % numHands)
    {
        // current hand
        auto &hand = hands[p];
        // shift a packet of cards
        for (int i = 0; i < packet && !deck.isEmpty(); ++i)
        {
            deck >> hand;
        }
    }
}

int PinochleGame::play()
{
    const int CardsInRow = 8;
    const int STOP = 1;

    while (true)
    {
        // call the deck's shuffle member function
        deck.shuffle();
        // call the deal member function to distribute the cards to the players
        deal();
        // print out each player's name and then the cards in their hand to the standard output stream
        print(std::cout, CardsInRow);
        // use the deck's collect member function repeatedly to move the cards back out of each player's hand into the deck
        collectAll();
        // print a string to the standard output stream that asks the user whether or not to end the game
        if (askForStop(std::cout, std::cin))
        {
            // if that string is "yes" the member function should return a value to indicate success, and otherwise it should repeat the sequence of steps
            return STOP;
        }
    }
}

void PinochleGame::print(std::ostream &os, const std::size_t rc)
{
    int numPlayer = players.size();
    // print each player's status
    for (int i = 0; i < numPlayer; ++i)
    {
        os << "player name: " << players[i] << std::endl;
        hands[i].print(os, rc);
    }
}

void PinochleGame::collectAll()
{
    int numPlayer = players.size();
    // collect cards from each player hand
    for (int i = 0; i < numPlayer; ++i)
    {
        deck.collect(hands[i]);
    }
}

bool PinochleGame::askForStop(std::ostream &os, std::istream &is)
{
    std::string input;
    // prompt hint message
    os << std::endl
       << ">>> Do you wish to stop playing? (yes/*) " << std::endl;
    // read in a string from the standard input stream
    is >> input;
    // return whether input is yes
    return "yes" == input;
}