#include "HoldEmDeck.h"

std::string to_string(const HoldEmRank& her) {
    switch (her)
    {
    case HoldEmRank::Two:
        return "2";
    case HoldEmRank::Three:
        return "3";
    case HoldEmRank::Four:
        return "4";
    case HoldEmRank::Five:
        return "5";
    case HoldEmRank::Six:
        return "6";
    case HoldEmRank::Seven:
        return "7";
    case HoldEmRank::Eight:
        return "8";
    case HoldEmRank::Nine:
        return "9";
    case HoldEmRank::Ten:
        return "10";
    case HoldEmRank::Jack:
        return "J";
    case HoldEmRank::Queen:
        return "Q";
    case HoldEmRank::King:
        return "K";
    case HoldEmRank::Ace:
        return "A";
    case HoldEmRank::undefined:
        return "?";
    default:
        return "not_exists";
    }
}

std::ostream& operator<<(std::ostream& os, const HoldEmRank& her) {
    return os << to_string(her);
}

HoldEmRank& operator++(HoldEmRank& her) {
    switch (her)
    {
    case HoldEmRank::Two:
        her = HoldEmRank::Three;
        break;
    case HoldEmRank::Three:
        her = HoldEmRank::Four;
        break;
    case HoldEmRank::Four:
        her = HoldEmRank::Five;
        break;
    case HoldEmRank::Five:
        her = HoldEmRank::Six;
        break;
    case HoldEmRank::Six:
        her = HoldEmRank::Seven;
        break;
    case HoldEmRank::Seven:
        her = HoldEmRank::Eight;
        break;
    case HoldEmRank::Eight:
        her = HoldEmRank::Nine;
        break;
    case HoldEmRank::Nine:
        her = HoldEmRank::Ten;
        break;
    case HoldEmRank::Ten:
        her = HoldEmRank::Jack;
        break;
    case HoldEmRank::Jack:
        her = HoldEmRank::Queen;
        break;
    case HoldEmRank::Queen:
        her = HoldEmRank::King;
        break;
    case HoldEmRank::King:
        her = HoldEmRank::Ace;
        break;
    case HoldEmRank::Ace:
        her = HoldEmRank::undefined;
        break;
    default:
        break;
    }
    return her;
}

HoldEmDeck::HoldEmDeck() {
    for (HoldEmRank her = HoldEmRank::Two; her != HoldEmRank::undefined; ++her) {
        for (Suit s = Suit::Clubs; s != Suit::undefined; ++s) {
            this->cards.emplace_back(her, s);
        }
    }
}

void HoldEmDeck::print(std::ostream& os) {
    int sz = cards.size();
    for (int i = 0; i < sz; i += COL) {
        for (int j = 0; j < COL && i + j < sz; ++j) {
            os << cards[i+j] << " ";
        }
        os << std::endl;
    }
}