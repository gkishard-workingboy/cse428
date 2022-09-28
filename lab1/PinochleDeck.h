#pragma once
#include "Deck_T.h"
#include "Suit.h"
#include <vector>

enum class PinochleRank { nine, jack, queen, king, ten, ace, undefined };

std::ostream& operator<<(std::ostream& os, const PinochleRank& pr);

PinochleRank& operator++(PinochleRank& pr);

class PinochleDeck : public Deck<PinochleRank, Suit> {
public:
	PinochleDeck();
};

