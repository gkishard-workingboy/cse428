/*
 * @FilePath: /428cpp/labs/lab1/lab1.cpp
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Date: 2022-09-24 21:48:13
 * @LastEditTime: 2022-09-25 15:57:45
 * @Description: This file contains the main function for testing
 * the functionality of two kinds of decks.
 */

#include "PinochleDeck.h"
#include "HoldEmDeck.h"
#include "PinochleGame.h"
#include <iostream>
#include <exception>
using namespace std;

const int PROGRAM_NAME = 1;
const int baseArgs = 2;
const int pinochleArgs = baseArgs + 4;
const int holdEmMinArgs = baseArgs + 2;
const int holdEmMaxArgs = baseArgs + 9;
const int SUCCESS = 0;
const int USAGE = 1;
const int PinC = 8;
const int HolC = 13;

int main(int argc, const char *argv[])
{
    if(argc < baseArgs){
        cout << "Usage: ";
    }
    
    // last try-catch to stop exception propagation.
    try
    {
        PinochleDeck pd;
        HoldEmDeck hd;
        // print out Pinochle deck
        cout << "Pinochle Deck: " << endl;
        pd.print(cout, PinC);
        // print out Hold'em deck
        cout << "Texas hold'em Deck: " << endl;
        hd.print(cout, HolC);
        cout << "Texas hold'em Deck shuffled: " << endl;
        // test for shuffle
        hd.shuffle();
        hd.print(cout, HolC);
        CardSet<HoldEmRank, Suit> cs;
        // test for right shift operator
        hd >> cs;
        cs.print(cout, HolC);
        // test for PinochleGame
        cout << endl;
        // TODO: Replace inline literal in future
        PinochleGame pg(argc, argv);
        pg.play();
    }
    catch (const std::exception &e)
    {
        // print out what message to cerr;
        std::cerr << e.what() << '\n';
    }

    return SUCCESS;
}
