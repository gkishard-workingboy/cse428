/*
 * @File: PinochleDeck.h
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Description: Declaration of enumeration class PinochleRank with corresponding shift and prefix increment operator, class PinochleDeck inherited from Deck.
 *
 */
#ifndef _PINOCHLEDECK_H
#define _PINOCHLEDECK_H

#include "Suit.h"
#include "Deck_T.h"
#include <vector>

enum class PinochleRank
{
    Nine,
    Jack,
    Queen,
    King,
    Ten,
    Ace,
    undefined
};

std::string to_string(const PinochleRank &);
std::ostream &operator<<(std::ostream &, const PinochleRank &);
PinochleRank &operator++(PinochleRank &);

class PinochleDeck : public Deck<PinochleRank, Suit>
{
public:
    PinochleDeck();
};

#endif