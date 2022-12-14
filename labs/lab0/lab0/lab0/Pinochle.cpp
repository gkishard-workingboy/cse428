#include "Pinochle.h"

std::ostream& operator<<(std::ostream& os, PinochleRank& pr) {
    switch (pr) {
    case PinochleRank::nine:
        os << "9";
        break;
    case PinochleRank::ten:
        os << "10";
        break;
    case PinochleRank::jack:
        os << "J";
        break;
    case PinochleRank::queen:
        os << "Q";
        break;
    case PinochleRank::king:
        os << "K";
        break;
    case PinochleRank::ace:
        os << "A";
        break;
    case PinochleRank::undefined:
        os << "?";
        break;
    }
    return os << " ";
}

PinochleRank& operator++(PinochleRank& pr) {
    switch (pr) {
    case PinochleRank::nine:
        pr = PinochleRank::jack;
        return pr;
    case PinochleRank::jack:
        pr = PinochleRank::queen;
        return pr;
    case PinochleRank::queen:
        pr = PinochleRank::king;
        return pr;
    case PinochleRank::king:
        pr = PinochleRank::ten;
        return pr;
    case PinochleRank::ten:
        pr = PinochleRank::ace;
        return pr;
    case PinochleRank::ace:
        pr = PinochleRank::undefined;
        return pr;
    case PinochleRank::undefined:
        return pr;
    }
    return pr;
}

PinochleDeck::PinochleDeck() {
    this->cards.push_back(Playcard<PinochleRank, suit>(PinochleRank::ace, suit::clubs));
    for (suit s = suit::clubs; s != suit::undefined; ++s) {
        for (PinochleRank r = PinochleRank::nine; r != PinochleRank::undefined; ++r) {
            this->cards.push_back(Playcard<PinochleRank, suit>(r, s));
            this->cards.push_back(Playcard<PinochleRank, suit>(r, s));
        }
    }
}

//WIP
void PinochleDeck::print(std::ostream& os) {
    os << " WIP " << endl;
}

int main()
{
    
}
