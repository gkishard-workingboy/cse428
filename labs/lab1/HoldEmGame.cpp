#include "HoldEmGame.h"
using namespace std;
const int SUCCESS = 0;
const int handCards = 2;
const int flopCards = 3;
const int turnCards = 4;
const int riverCards = 5;

HoldEmGame::HoldEmGame(int argc, const char* argv[]) : Game(argc, argv) {
	this->state = HoldEmState::preflop;
    // create as many hands as players in the game
    for (int i = 0; i < argc; ++i)
    {
        // will call default constructor of CardSet
        hands.emplace_back();
    }
}

void HoldEmGame::deal() {
    if (this->state == HoldEmState::preflop) {
        for (size_t i = 0; i < handCards; i++) {
            for (size_t j = 0; j < hands.size() && !deck.isEmpty(); j++) {
                deck >> hands[j];
            }
        }
        this->state = HoldEmState::flop;
    }
    else if (this->state == HoldEmState::flop) {
        for (size_t i = 0; i < flopCards; i++) {
            deck >> board;
        }
        this->state = HoldEmState::turn;
    }
    else if (this->state == HoldEmState::turn) {
        deck >> board;
        this->state = HoldEmState::river;
    }
    else if (this->state == HoldEmState::river) {
        deck >> board;
        this->state = HoldEmState::river;
    }
}

void HoldEmGame::collectAll()
{
    size_t numPlayer = players.size();
    // collect cards from each player hand
    for (size_t i = 0; i < numPlayer; ++i)
    {
        deck.collect(hands[i]);
    }
}

void HoldEmGame::print(std::ostream& os, const std::size_t rc)
{
    int numPlayer = players.size();
    // print each player's status
    for (int i = 0; i < numPlayer; ++i)
    {
        os << "player name: " << players[i] << std::endl;
        hands[i].print(os, rc);
    }
    deck.collect(board);
}

int HoldEmGame::play() {
    //shuffle card set state to preflop
    deck.shuffle();
    this->state = HoldEmState::preflop;
    //deal the card to players
    this->deal();
    //print each player info and hand

    print(cout, handCards);

    //deal 3 flop cards to board
    this->deal();
    cout << "BOARD (flop): ";
    board.print(cout, flopCards);

    //deal turn cards to board
    this->deal();
    cout << "BOARD (turn): ";
    board.print(cout, turnCards);

    //deal river cards to board
    this->deal();
    cout << "BOARD (river): ";
    board.print(cout, riverCards);

    //collect hands and board
    collectAll();
    
    cout << "Would you like to end the current game?" << endl;
    string userInput;
    cin >> userInput;
    if (userInput == "yes")
        return SUCCESS;
    else {
        return this->play();
    }
}