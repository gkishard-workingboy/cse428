#pragma once
#include "CardSet_T.h"
#include <random>
#include <algorithm>

template<typename R, typename S>
class Deck : public CardSet<R, S> {
public:
	void shuffle();
	void collect(CardSet<R,S> &);
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "Deck_T.cpp"
#endif