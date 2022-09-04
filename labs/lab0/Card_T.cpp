#include "Card_T.h"

template<typename R, typename S>
Playcard<R, S>::Playcard(R r, S s){
    this->r = r;
    this->s = s;
}

template<typename R, typename S>
std::ostream& operator<<(std::ostream& os, const Playcard<R, S>& c) {
    os << c.rank << c.suit;
    return os;
}