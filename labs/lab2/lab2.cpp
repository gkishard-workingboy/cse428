/*
 * @FilePath: /428cpp/labs/lab1/lab1.cpp
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Date: 2022-09-24 21:48:13
 * @LastEditTime: 2022-10-02 21:50:52
 * @Description: This file contains the main function for testing
 * the functionality of two kinds of decks.
 */

#include "PinochleDeck.h"
#include "HoldEmDeck.h"
#include "PinochleGame.h"
#include "HoldEmGame.h"
#include <iostream>
#include <exception>
#include <cstring>
#include <memory>
using namespace std;

enum
{
    ProgName,
    GameName,
    MinPlayers = 4,
    pinochlePlayers = 6,
    MaxPlayer = 11
};

enum ResultCode
{
    Success,
    UsageGameNameError,
    UsagePinochlePlayerNumError,
    UsageHoldEmPlayerNumError,
    InvalidPointer,
    Any
};

shared_ptr<Game> create(int argc, const char *argv[])
{
    shared_ptr<Game> game;
    if (strcmp(argv[GameName], "Pinochle") == 0)
    {
        game = make_shared<PinochleGame>(argc, argv);
    }
    if (strcmp(argv[GameName], "HoldEm") == 0)
    {
        game = make_shared<HoldEmGame>(argc, argv);
    }
    return game;
}

int usage(ResultCode rc)
{
    cout << "Usage: ./lab2.out <Game> <Player Names>" << endl;
    cout << "Game should be either 'Pinochle' or 'HoldEm'." << endl;
    if (rc != ResultCode::UsageHoldEmPlayerNumError)
    {
        cout << "If the game is Pinochle, there must be 4 player names." << endl;
    }
    if (rc != ResultCode::UsagePinochlePlayerNumError)
    {
        cout << "If the game is HoldEm, there must be between 2 and 9 player names." << endl;
    }
    return rc;
}

int main(int argc, const char *argv[])
{

    // aruments checking
    if (argc < MinPlayers)
    {
        return usage(ResultCode::UsageGameNameError);
    }
    else if (strcmp(argv[GameName], "Pinochle") == 0)
    {
        if (argc != pinochlePlayers)
        {
            return usage(ResultCode::UsagePinochlePlayerNumError);
        }
    }
    else if (strcmp(argv[GameName], "HoldEm") == 0)
    {
        if (argc > MaxPlayer)
        {
            return usage(ResultCode::UsageHoldEmPlayerNumError);
        }
    }
    else
    {
        return usage(ResultCode::UsageGameNameError);
    }

    // last try-catch to stop exception propagation.
    try
    {
        shared_ptr<Game> game = create(argc, argv);
        if (game)
        {
            game->play();
        }
        else
        {
            cout << "Error: invalid pointer to game" << endl;
            return ResultCode::InvalidPointer;
        }
    }
    catch (const std::exception &e)
    {
        // print out what message to cerr;
        std::cerr << e.what() << '\n';
        return ResultCode::Any;
    }

    return ResultCode::Success;
}
