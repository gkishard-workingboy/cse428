/*
 * @File: PinochleDeck.cpp
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Description: Definition of enumeration class PinochleRank with corresponding shift and prefix increment operator, class PinochleDeck inherited from Deck.
 *
 */
#include "PinochleDeck.h"

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
    for (PinochleRank pr = PinochleRank::Nine; pr != PinochleRank::undefined; ++pr)
    {
        for (Suit s = Suit::Clubs; s != Suit::undefined; ++s)
        {
            this->cards.emplace_back(pr, s);
            this->cards.emplace_back(pr, s);
        }
    }
};

void PinochleDeck::print(std::ostream &os)
{
    int sz = cards.size();
    for (int i = 0; i < sz; i += COL)
    {
        for (int j = 0; j < COL && i + j < sz; ++j)
        {
            os << cards[i + j] << " ";
        }
        os << std::endl;
    }
}