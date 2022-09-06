#include "PinochleDeck.h"
#include "HoldEmDeck.h"
#include <iostream>
using namespace std;

int main(void) {
    PinochleDeck pd;
    HoldEmDeck hd;
    cout << "Pinochle Deck" << endl;
    pd.print(cout);
    cout << "Texas hold'em Deck" << endl;
    hd.print(cout);

    return 0;
}