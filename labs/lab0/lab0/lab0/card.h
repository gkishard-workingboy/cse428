#pragma once
#include "suit.h"

//redundant: enum class cardRank { two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace };

template<typename R, typename S>
class Playcard {
public:
	R r;
	S s;
	Playcard(R r, S s);
};

template<typename R, typename S>
std::ostream& operator<<(std::ostream& os, const Playcard<R,S>& c);

