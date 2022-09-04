#include "Deck.h"
#include "Card_T.h"
#include "Suit.h"
#include <vector>

#define COL 8 

enum class PinochleRank{
    Nine,
    Jack,
    Queen,
    King,
    Ten,
    Ace,
    undefined
};

char* to_string(const PinochleRank&);
std::ostream& operator<<(std::ostream&, const PinochleRank&);
PinochleRank& operator++(PinochleRank&);

class PinochleDeck: public Deck {
private:
    std::vector< Card<PinochleRank, Suit> > cards;
public:
    PinochleDeck();
    virtual void print(std::ostream& os) override;
};