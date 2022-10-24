/*
 * @FilePath: /428cpp/labs/lab2/HoldEmGame.h
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Date: 2022-10-02 19:55:59
 * @LastEditTime: 2022-10-24 16:51:48
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

enum class HoldEmState
{
	preflop,
	flop,
	turn,
	river,
	undefined
};

enum class HoldEmHandRank
{
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
}

std::ostream &
operator<<(std::ostream &, const HoldEmHandRank &);

class HoldEmGame : public Game
{
private:
	HoldEmHandRank holdem_hand_evaluation(const CardSet<HoldEmRank, Suit>);

protected:
	HoldEmState state;
	HoldEmDeck deck;
	std::vector<CardSet<HoldEmRank, Suit>> hands;
	CardSet<HoldEmRank, Suit> board;
	virtual void deal();
	// * DESIGN:
	// * modularize play() by extract parts to 2 member methods
	void collectAll();
	void print(std::ostream &, const std::size_t);
	bool askForStop(std::ostream &, std::istream &);

public:
	HoldEmGame(int, const char *[]);
	virtual int play() override;
};

#endif // _HOLDEMGAME_H