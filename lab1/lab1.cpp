#include "PinochleDeck.h"
#include "HoldEmDeck.h"
#include "HoldEmGame.h"
#include "PinochleGame.h"
#include <iostream>
#include <memory>
#include "Game.h"
using namespace std;

const int SUCCESS = 0;
const size_t PinC = 8;
const int GameName = 2;

shared_ptr<Game> create(int argc, char *argv[]) {
    shared_ptr<Game> GamePtr;
    if (argc < GameName) {
        cout << "usage: Pinochole/HoldEm [<arg1> <arg2> ...]" << endl;
        return GamePtr;
    }
    if (argv[GameName] == string("Pinochole")) {
        GamePtr = make_shared<PinochleGame>(argc, argv);
    }
    else if (argv[GameName] == string("HoldEm")) {
        GamePtr = make_shared<HoldEmGame>(argc, argv);
    }
    return GamePtr;
}


int main(int argc, char* argv[]) {
    HoldEmDeck hd;
    hd.print(cout, PinC);

    HoldEmGame pg(argc - GameName, argv + GameName);
    pg.play();
    return SUCCESS;
}