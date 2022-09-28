#include "Suit.h"
#include <iostream>


std::ostream& operator<<(std::ostream& os, const Suit& s) {
    switch (s) {
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
    return os << " ";
}

Suit& operator++(Suit& s) {
    switch (s) {
    case Suit::clubs:
        s = Suit::diamonds;
        return s;
    case Suit::diamonds:
        s = Suit::hearts;
        return s;
    case Suit::hearts:
        s = Suit::spades;
        return s;
    case Suit::spades:
        s = Suit::undefined;
        return s;
    case Suit::undefined:
        return s;
    }
    return s;
}

//
//int main()
//{
//    std::cout << "Hello World!\n";
//}
