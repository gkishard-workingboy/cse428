#include "PinochleDeck.h"

char* to_string(const PinochleRank& pr) {
    switch (pr)
    {
    case PinochleRank::Nine:
        return "9";
    case PinochleRank::Jack:
        return "J";
    case PinochleRank::Queen:
        return "Q";
    case PinochleRank::King:
        return "K";
    case PinochleRank::Ten:
        return "10";
    case PinochleRank::Ace:
        return "A";
    case PinochleRank::undefined:
        return "?";
    default:
        return "not_exists";
    }
}

std::ostream& operator<<(std::ostream& os, const PinochleRank& pr) {
    return os << to_string(pr);
}

PinochleRank& operator++(PinochleRank& pr) {
    switch (pr)
    {
    case PinochleRank::Nine:
        pr = PinochleRank::Jack;
    case PinochleRank::Jack:
        pr = PinochleRank::Queen;
    case PinochleRank::Queen:
        pr = PinochleRank::King;
    case PinochleRank::King:
        pr = PinochleRank::Ten;
    case PinochleRank::Ten:
        pr = PinochleRank::Ace;
    case PinochleRank::Ace:
        pr = PinochleRank::undefined;
    default:
        break;
    }
    return pr;
}

PinochleDeck::PinochleDeck() {
    for (PinochleRank pr = PinochleRank::Nine; pr != PinochleRank::undefined; ++pr) {
        for (Suit s = Suit::Clubs; s != Suit::undefined; ++s) {
            this->cards.emplace_back(pr, s);
            this->cards.emplace_back(pr, s);
        }
    }
};

void PinochleDeck::print(std::ostream& os) {
    for (int i = 0; i < cards.size(); i += COL) {
        for (int j = 0; j < COL && i + j < cards.size(); ++j) {
            os << cards[i+j] << " ";
        }
        os << endl;
    }
}