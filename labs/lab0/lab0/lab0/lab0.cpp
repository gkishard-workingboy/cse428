#include <iostream>
#include "suit.h"

std::ostream& operator<<(std::ostream& os, const suit& s) {
    switch (s) {
    case suit::clubs:
        os << "C";
        break;
    case suit::diamonds:
        os << "D";
        break;
    case suit::hearts:
        os << "H";
        break;
    case suit::spades:
        os << "S";
        break;
    case suit::undefined:
        os << "?";
        break;
    }
    return os << " ";
}

suit& operator++(suit& s) {
    switch (s) {
    case suit::clubs:
        s = suit::diamonds;
        return s;
    case suit::diamonds:
        s = suit::hearts;
        return s;
    case suit::hearts:
        s = suit::spades;
        return s;
    case suit::spades:
        s = suit::undefined;
        return s;
    case suit::undefined:
        return s;
    }
    return s;
}

//
//int main()
//{
//    std::cout << "Hello World!\n";
//}
