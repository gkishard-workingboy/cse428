#pragma once
#include "deck.h"
#include <vector>

enum class PinochleRank { nine, jack, queen, king, ten, ace, undefined };

std::ostream& operator<<(std::ostream& os, const PinochleRank& pr);

PinochleRank& operator++(PinochleRank& pr);

class PinochleDeck : public cardDeck {
private:
	std::vector< Playcard<PinochleRank, suit> > cards;

public:
	PinochleDeck();
	virtual void print(std::ostream& os) override;
};