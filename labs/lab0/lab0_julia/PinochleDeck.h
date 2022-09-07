#pragma once
#include "Suit.h"
#include "Card_T.h"
#include "Deck.h"
#include <fstream>
#include <vector>

using namespace std;

enum class PinochleRank { nine, jack, queen, king, ten, ace, undefined };

ostream& operator<<(ostream& os, const PinochleRank& pr);
PinochleRank& operator++(PinochleRank& pr);

class PinochleDeck : Deck {
public:
	PinochleDeck();
	void print(ostream& os);
private:
	vector< Card<PinochleRank, Suit> > cards_;
};