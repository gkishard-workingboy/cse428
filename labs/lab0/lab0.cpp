#include "PinochleDeck.h"
#include "HoldEmDeck.h"
#include <iostream>
using namespace std;

int main(void) {
    PinochleDeck pd;
    HoldEmDeck hd;
    pd.print(cout);
    hd.print(cout);
    
    return 0;
}