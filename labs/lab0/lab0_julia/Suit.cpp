// Lab0.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Suit.h"
#include <iostream>

ostream& operator<<(ostream& os, const Suit& suit) {
    switch (suit) {
    case Suit::clubs:
        os << "C";
        break;
    case Suit::diamonds:
        os << "D";
        break;
    case Suit::hearts:
        os << "H";
        break;
    case Suit::spades:
        os << "S";
        break;
    case Suit::undefined:
        os << "?";
        break;
    }
    return os;
}

Suit& operator++(Suit& suit) {
    switch (suit) {
    case Suit::clubs:
        suit = Suit::diamonds;
        break;
    case Suit::diamonds:
        suit = Suit::hearts;
        break;
    case Suit::hearts:
        suit = Suit::spades;
        break;
    case Suit::spades:
        suit = Suit::undefined;
        break;
    case Suit::undefined:
        ; //null statement
    }
    return suit;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
