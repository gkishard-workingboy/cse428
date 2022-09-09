/*
 * @File: lab0.cpp
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Description: This file contains the main function for testing
 * the functionality of two kinds of decks.
 *
 */

#include "PinochleDeck.h"
#include "HoldEmDeck.h"
#include <iostream>
using namespace std;

int main(void)
{
    PinochleDeck pd;
    HoldEmDeck hd;
    cout << "Pinochle Deck: " << endl;
    pd.print(cout);
    cout << "Texas hold'em Deck: " << endl;
    hd.print(cout);

    return 0;
}