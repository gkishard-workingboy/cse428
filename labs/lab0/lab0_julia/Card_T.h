#pragma once
#include <fstream>

using namespace std;

template<typename R, typename S> struct Card {
	R rank_;
	S suit_;
	Card(R rank, S suit);
};

template<typename R, typename S> ostream& operator<<(ostream& os, const Card<R, S>& card);

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE 
#include "Card_T.cpp"
#endif