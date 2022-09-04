#include <ostream>
using namespace std;

enum class Suit{
    Clubs,
    Diamonds,
    Hearts,
    Spades,
    undefined
};

char* to_string(const Suit&);
ostream& operator<<(ostream&, const Suit&);
Suit& operator++(Suit&);
