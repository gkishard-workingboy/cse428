#include "card.h"

template<typename R, typename S>
Playcard<R, S>::Playcard(R r, S s){
    this->r = r;
    this->s = s;
}

template<typename R, typename S>
std::ostream& operator<<(std::ostream& os, const Playcard<R, S>& c) {
    switch (c.s) {
    case suit::clubs:
        os << "clubs";
        break;
    case suit::diamonds:
        os << "diamonds";
        break;
    case suit::spades:
        os << "spades";
        break;
    case suit::hearts:
        os << "hearts";
        break;
    case suit::undefined:
        os << "undefined";
        break;
    }
    os << " ";
    /*switch (c.r) {
    case Pinochle::nine:
        os << "9";
        break;
    case Pinochle::ten:
        os << "10";
        break;
    case Pinochle::jack:
        os << "J";
        break;
    case Pinochle::queen:
        os << "Q";
        break;
    case Pinochle::king:
        os << "K";
        break;
    case Pinochle::ace:
        os << "A";
        break;
    case Pinochle::undefined:
        os << "undefined";
        break;
    }*/
    return os << " ";;
}

