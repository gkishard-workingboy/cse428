#include "Suit.h"

std::string to_string(const Suit& s) {
    switch (s)
    {
    case Suit::Clubs:
        return "C";
    case Suit::Diamonds:
        return "D";
    case Suit::Hearts:
        return "H";
    case Suit::Spades:
        return "S";
    case Suit::undefined:
        return "?";
    default:
        return "not_exists";
    }
}

std::ostream& operator<<(std::ostream& os, const Suit& s) {
    os << to_string(s);
    return os;
}

Suit& operator++(Suit& s) {
    switch (s)
    {
    case Suit::Clubs:
        s = Suit::Diamonds;
        break;
    case Suit::Diamonds:
        s = Suit::Hearts;
        break;
    case Suit::Hearts:
        s = Suit::Spades;
        break;
    case Suit::Spades:
        s = Suit::undefined;
        break;
    default:
        break;
    }
    return s;
}
