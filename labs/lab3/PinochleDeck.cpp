/*
 * @File: PinochleDeck.cpp
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Description: Definition of enumeration class PinochleRank with corresponding shift and prefix increment operator, class PinochleDeck inherited from Deck.
 *
 */
#include "PinochleDeck.h"

unsigned int PinochleDeck::PinochleRanksPointValue[PINOCHLE_NUM_RANKS] = {0, 2, 3, 4, 10, 11};

std::string to_string(const PinochleRank &pr)
{
    switch (pr)
    {
    case PinochleRank::Nine:
        return "9";
    case PinochleRank::Jack:
        return "J";
    case PinochleRank::Queen:
        return "Q";
    case PinochleRank::King:
        return "K";
    case PinochleRank::Ten:
        return "10";
    case PinochleRank::Ace:
        return "A";
    case PinochleRank::undefined:
        return "?";
    default:
        return "not_exists";
    }
}

std::ostream &operator<<(std::ostream &os, const PinochleRank &pr)
{
    return os << to_string(pr);
}

PinochleRank &operator++(PinochleRank &pr)
{
    switch (pr)
    {
    case PinochleRank::Nine:
        pr = PinochleRank::Jack;
        break;
    case PinochleRank::Jack:
        pr = PinochleRank::Queen;
        break;
    case PinochleRank::Queen:
        pr = PinochleRank::King;
        break;
    case PinochleRank::King:
        pr = PinochleRank::Ten;
        break;
    case PinochleRank::Ten:
        pr = PinochleRank::Ace;
        break;
    case PinochleRank::Ace:
        pr = PinochleRank::undefined;
    default:
        break;
    }
    return pr;
}

PinochleDeck::PinochleDeck()
{
    // Nested loop in this manner will gather those cards with same rank togather.
    for (PinochleRank pr = PinochleRank::Nine; pr != PinochleRank::undefined; ++pr)
    {
        for (Suit s = Suit::Clubs; s != Suit::undefined; ++s)
        {
            // emplace() and emplace_back() will implicitly call the constructor of the class of value type.
            cards.emplace_back(pr, s);
            cards.emplace_back(pr, s);
        }
    }
};