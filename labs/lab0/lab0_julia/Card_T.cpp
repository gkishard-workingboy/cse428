#include "Card_T.h"

template<typename R, typename S> Card<R, S>::Card(R rank, S suit) : rank_(rank), suit_(suit) {
}

template<typename R, typename S> ostream& operator<<(ostream& os, const Card<R, S>& card) {
	os << card.rank_;
	os << card.suit_;
	return os;
}
