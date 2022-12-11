/*
 * @FilePath: /428cpp/labs/lab3/HoldEmGame.h
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Date: 2022-10-02 19:55:59
 * @LastEditTime: 2022-12-10 18:24:19
 * @Description: Declaration for Hold'Em Game states and class.
 *
 */
#pragma once
#ifndef _HOLDEMGAME_H
#define _HOLDEMGAME_H

#include "Game.h"
#include "Suit.h"
#include "HoldEmDeck.h"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <utility>

enum class HoldEmState {
	preflop,
	flop,
	turn,
	river,
	undefined
};

enum class HoldEmHandRank {
	xhigh,
	pair,
	twopair,
	threeofakind,
	straight,
	flush,
	fullhouse,
	fourofakind,
	straightflush,
	undefined
};

enum class HoldEmAction {
	fold,
	call,
	raise
};

class HoldEmGame: public Game {
public:
	HoldEmGame(int, const char* []);
	virtual int play() override;

	struct PlayerHand {
	public:
		CardSet<HoldEmRank, Suit> cards;
		int name;
		HoldEmHandRank rank;

		PlayerHand(CardSet<HoldEmRank, Suit>&, int, HoldEmHandRank);

		HoldEmGame::PlayerHand& operator=(const HoldEmGame::PlayerHand&);
	};

private:
	HoldEmHandRank holdem_hand_evaluation(const CardSet<HoldEmRank, Suit>&);

protected:
	int pot;
	HoldEmState state;
	HoldEmDeck deck;
	std::vector<CardSet<HoldEmRank, Suit>> hands;
	CardSet<HoldEmRank, Suit> board;
	std::vector<int> input_scores;
	std::vector<bool> playerStatus;
	std::vector<std::string> playerRank;

	virtual void deal();
	void reset();
	bool bet();
	std::vector<HoldEmAction> action_before_turn(const CardSet<HoldEmRank, Suit>&);
	std::vector<HoldEmAction> action_after_turn(const HoldEmGame::PlayerHand&);
	// * DESIGN:
	// * modularize play() by extract parts to 2 member methods
	void collectAll();
	void print(std::ostream&, const std::size_t);
	bool askForStop(std::ostream&, std::istream&);
	void evalCombinations(CardSet<HoldEmRank, Suit>&, CardSet<HoldEmRank, Suit>, HoldEmGame::PlayerHand&);
	void printPlayerHand(std::ostream&, std::vector<HoldEmGame::PlayerHand>&);
	void settleRound(std::vector<HoldEmGame::PlayerHand>&);
};

std::ostream& operator<<(std::ostream&, const HoldEmHandRank&);
bool operator<(const HoldEmGame::PlayerHand&, const HoldEmGame::PlayerHand&);
bool operator==(const HoldEmGame::PlayerHand&, const HoldEmGame::PlayerHand&);

#endif // _HOLDEMGAME_H