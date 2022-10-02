#pragma once

#include "Game.h"
#include "Suit.h"
#include "HoldEmDeck.h"
#include <vector>
#include <iostream>
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
	HoldEmGame(int, const char* []);
	virtual int play() override;
};