/*
 * @File: HoldEmDeck.h
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Description: Declaration of enumeration class HoldEmRank with corresponding shift and prefix increment operator, class HoldEmDeck inherited from Deck.
 *
 */
#ifndef _HOLDEMDECK_H
#define _HOLDEMDECK_H

#include "Suit.h"
#include "Deck_T.h"
#include <vector>

enum class HoldEmRank
{
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace,
    undefined
};

std::string to_string(const HoldEmRank&);
std::ostream& operator<<(std::ostream&, const HoldEmRank&);
HoldEmRank& operator++(HoldEmRank&);

class HoldEmDeck : public Deck<HoldEmRank, Suit>
{
public:
    HoldEmDeck();
};

#endif