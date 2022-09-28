#pragma once
#include <vector>
#include <iostream>
#include "Card_T.h"

template<typename R, typename S>
class CardSet {
public:
	void print(std::ostream& os, std::size_t s);
	CardSet<R,S>& operator>>(CardSet<R,S> &);
	bool isEmpty();
protected:
	std::vector< Card<R, S> > cards;
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "CardSet_T.cpp"
#endif