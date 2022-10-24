/*
 * @FilePath: /428cpp/labs/lab2/HoldEmGame.cpp
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Date: 2022-10-02 19:55:59
 * @LastEditTime: 2022-10-24 16:48:08
 * @Description: Definition to HoldEmGame.h
 *
 */
#include "HoldEmGame.h"
using namespace std;

const int handCards = 2;

HoldEmGame::HoldEmGame(int argc, const char *argv[]) : Game(argc, argv), state(HoldEmState::preflop)
{
    // create as many hands as players in the game
    for (int i = 2; i < argc; ++i)
    {
        // will call default constructor of CardSet
        hands.emplace_back();
    }
}

void HoldEmGame::deal()
{
    const int flopCards = 3;

    if (this->state == HoldEmState::preflop)
    {
        for (size_t i = 0; i < handCards; i++)
        {
            for (size_t j = 0; j < hands.size() && !deck.isEmpty(); j++)
            {
                deck >> hands[j];
            }
        }
        this->state = HoldEmState::flop;
    }
    else if (this->state == HoldEmState::flop)
    {
        for (size_t i = 0; i < flopCards; i++)
        {
            deck >> board;
        }
        this->state = HoldEmState::turn;
    }
    else if (this->state == HoldEmState::turn)
    {
        deck >> board;
        this->state = HoldEmState::river;
    }
    else if (this->state == HoldEmState::river)
    {
        deck >> board;
        this->state = HoldEmState::undefined;
    }
    // do nothing for other states
}

void HoldEmGame::collectAll()
{
    size_t numPlayer = players.size();
    // collect cards from each player hand
    for (size_t i = 0; i < numPlayer; ++i)
    {
        deck.collect(hands[i]);
    }
    // collect cards from board
    deck.collect(board);
}

void HoldEmGame::print(std::ostream &os, const std::size_t rc)
{
    int numPlayer = players.size();
    // print each player's status
    for (int i = 0; i < numPlayer; ++i)
    {
        os << "player name: " << players[i] << std::endl;
        hands[i].print(os, rc);
    }
}

bool HoldEmGame::askForStop(std::ostream &os, std::istream &is)
{
    std::string input;
    // prompt hint message
    os << std::endl
       << ">>> Would you like to end the current game? (yes/*) " << std::endl;
    // read in a string from the standard input stream
    is >> input;
    // return whether input is yes
    return "yes" == input;
}

int HoldEmGame::play()
{
    const int STOP = 0;
    const int boardWidth = 5;

    while (true)
    {
        // shuffle card set state to preflop
        deck.shuffle();
        this->state = HoldEmState::preflop;
        // deal the card to players
        this->deal();
        // print each player info and hand

        print(cout, handCards);

        // deal 3 flop cards to board
        this->deal();
        cout << "BOARD (flop): ";
        board.print(cout, boardWidth);

        // deal turn cards to board
        this->deal();
        cout << "BOARD (turn): ";
        board.print(cout, boardWidth);

        // deal river cards to board
        this->deal();
        cout << "BOARD (river): ";
        board.print(cout, boardWidth);

        // collect hands and board
        collectAll();

        if (askForStop(cout, cin))
        {
            return STOP;
        }
    }
}

operator<<(std::ostream &os, const HoldEmHandRank &herank)
{
    string label;
    stri switch (herank)
    {
    case HoldEmHandRank::xhigh:
        label = "xhigh";
        break;
    case HoldEmHandRank::pair:
        label = "pair";
        break;
    case HoldEmHandRank::twopair:
        label = "twopair";
        break;
    case HoldEmHandRank::threeofakind:
        label = "threeofakind";
        break;
    case HoldEmHandRank::straight:
        label = "straight";
        break;
    case HoldEmHandRank::flush:
        label = "flush";
        break;
    case HoldEmHandRank::fullhouse:
        label = "fullhouse";
        break;
    case HoldEmHandRank::fourofakind:
        label = "fourofakind";
        break;
    case HoldEmHandRank::straightflush:
        label = "straightflush";
        break;
    default:
        label = "undefined";
        break;
    }
    return os << label;
}
