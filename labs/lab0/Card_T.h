#ifndef _CARDT_H
#define _CARDT_H

#include <ostream>

// template<typename R, typename S> struct Card;

// template<typename R, typename S>
// std::ostream& operator<<(std::ostream&, const Card<R,S>&);

template<typename R, typename S>
struct Card{
public:
	R rank;
	S suit;
	Card(R, S);
};

template<typename R, typename S>
std::ostream& operator<<(std::ostream&, const Card<R, S>&);

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE /* test whether guard symbol is defined */
#include "Card_T.cpp"
#endif

#endif