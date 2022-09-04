#include "Deck.h"
#include "Card_T.h"
#include "Suit.h"
#include <vector>

enum class HoldEmRank{
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace,
    undefined
};

char* to_string(const HoldEmRank&);
std::ostream& operator<<(std::ostream&, const HoldEmRank&);
HoldEmRank& operator++(HoldEmRank&);

class HoldEmDeck: public Deck {
private:
    vector< Card<HoldEmRank, Suit> > cards;
public:
    HoldEmDeck();
    virtual print(std::ostream&) override;
};