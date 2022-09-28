#pragma once

#include "Game.h"
#include "Suit.h"
#include "HoldEmDeck.h"
#include <vector>
#include <ostream>
#include <istream>
using namespace std;

enum class HoldEmState { preflop, flop, turn, river, undefined };

class HoldEmGame : public Game {
protected:
	HoldEmState state;
	HoldEmDeck deck;
	vector<CardSet<HoldEmRank, Suit> > hands;
	CardSet<HoldEmRank, Suit> board;
	virtual void deal();
public:
	HoldEmGame(int, char* []);
	virtual int play() override;
};