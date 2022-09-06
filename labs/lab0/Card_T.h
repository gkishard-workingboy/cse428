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
Card<R, S>::Card(R r, S s){
    this->rank = r;
    this->suit = s;
}

template<typename R, typename S>
std::ostream& operator<<(std::ostream& os, const Card<R, S>& c) {
    os << c.rank << c.suit;
    return os;
}

#endif