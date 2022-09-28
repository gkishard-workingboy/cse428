#pragma once
#include <ostream>

template<typename R, typename S>
struct Card {
public:
	R r_;
	S s_;
	Card(R r, S s);
};

template<typename R, typename S>
std::ostream& operator<<(std::ostream&, const Card<R, S>&);

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE 
#include "Card_T.cpp"
#endif