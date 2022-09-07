#include "Pinochle.h"
#include <iostream>

ostream& operator<<(ostream& os, const PinochleRank& pr) {
	switch (pr) {
	case PinochleRank::nine:
		os << "9";
		break;
	case PinochleRank::jack:
		os << "J";
		break;
	case PinochleRank::queen:
		os << "Q";
		break;
	case PinochleRank::king:
		os << "K";
		break;
	case PinochleRank::ten:
		os << "10";
		break;
	case PinochleRank::ace:
		os << "A";
		break;
	case PinochleRank::undefined:
		os << "?";
		break;
	}

	return os;
}

PinochleRank& operator++(PinochleRank& pr) {
	switch (pr) {
	case PinochleRank::nine:
		pr = PinochleRank::jack;
		break;
	case PinochleRank::jack:
		pr = PinochleRank::queen;
		break;
	case PinochleRank::queen:
		pr = PinochleRank::king;
		break;
	case PinochleRank::king:
		pr = PinochleRank::ten;
		break;
	case PinochleRank::ten:
		pr = PinochleRank::ace;
		break;
	case PinochleRank::ace:
		pr = PinochleRank::undefined;
		break;
	case PinochleRank::undefined:
		; // null statement
		break;
	}

	return pr;
}


PinochleDeck::PinochleDeck() {
	Suit suit = Suit::clubs;
	while (suit != Suit::undefined) {
		PinochleRank rank = PinochleRank::nine;
		while (rank != PinochleRank::undefined) {
			this->cards_.push_back(Card< PinochleRank, Suit >(rank, suit));
			++rank;
		}
		++suit;
	}
}


void PinochleDeck::print(ostream& os) {
	/*
	I insert a line break after every 6 cards. This is because the deck will have 6 cards of each suit, 
	and the default constructor adds cards to the cards vector such that cards of the same suit are next to each other.
	*/

	unsigned int cards_per_suit = 6;

	for (unsigned int i = 0; i < cards_.size(); ++i) {
		os << this->cards_.at(i) << " ";

		if ((i + 1) % cards_per_suit == 0) {
			os << endl;
		}
	}
}

int main()
{
	std::cout << "Hello World!\n";
}