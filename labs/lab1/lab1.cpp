/*
 * @FilePath: lab1.cpp
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Date: 2022-09-24 21:48:13
 * @LastEditTime: 2022-09-24 23:04:49
 * @Description: This file contains the main function for testing
 * the functionality of two kinds of decks.
 */

#include "PinochleDeck.h"
#include "HoldEmDeck.h"
#include <iostream>
using namespace std;

const int SUCCESS = 0;
const int PinC = 8;
const int HolC = 13;

int main(int, char *[])
{
    PinochleDeck pd;
    HoldEmDeck hd;
    cout << "Pinochle Deck: " << endl;
    pd.print(cout, PinC);
    cout << "Texas hold'em Deck: " << endl;
    hd.print(cout, HolC);

    return SUCCESS;
}