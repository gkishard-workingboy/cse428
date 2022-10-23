/*
 * @FilePath: /428cpp/labs/lab1/PinochleGame.cpp
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Date: 2022-09-25 14:31:48
 * @LastEditTime: 2022-10-02 20:44:19
 * @Description: Definition to PinochleGame.h
 *
 */

#include "PinochleGame.h"
#include <iostream>
#include <string>

const int EIGHT_SAME_RANKS = 8;
const int FOUR_SAME_RANKS = 4;
const int PINOCHLE_NUM_CARDS = 11;
const int DOUBLE_PINOCHLE_CASE = 2;
const int PINOCHLE_CASE = 1;

unsigned int PinochleGame::PinochleMeldsPointValue[PINOCHLE_NUM_ITEMS] = { 10,20,40,40,40,60,80,100,150,300,400,600,800,1000,1500 };

PinochleGame::PinochleGame(int argc, const char* argv[]) : Game(argc, argv)
{
    // create as many hands as players in the game
    for (int i = 2; i < argc; ++i)
    {
        // will call default constructor of CardSet
        hands.emplace_back();
    }
}

void PinochleGame::deal()
{
    // size of a packet
    const int packet = 3;
    // number of players in game
    int numHands = hands.size();
    // repeatedly shift a packet of cards to each hand of players
    for (int p = 0; !deck.isEmpty(); p = (p + 1) % numHands)
    {
        // current hand
        auto& hand = hands[p];
        // shift a packet of cards
        for (int i = 0; i < packet && !deck.isEmpty(); ++i)
        {
            deck >> hand;
        }
    }
}

int PinochleGame::play()
{
    const int CardsInRow = 8;
    const int STOP = 0;

    while (true)
    {
        // call the deck's shuffle member function
        deck.shuffle();
        // call the deal member function to distribute the cards to the players
        deal();
        // print out each player's name and then the cards in their hand to the standard output stream
        print(std::cout, CardsInRow);

        //for each hand initiate a vector and call suit_independent_evaluation to print scores
        int numPlayer = players.size();
        for (int i = 0; i < numPlayer; ++i)
        {
            std::vector<PinochleMelds> vect;
            suit_independent_evaluation(hands[i], vect);
            for (auto j : vect)
                std::cout << j;
        }

        // use the deck's collect member function repeatedly to move the cards back out of each player's hand into the deck
        collectAll();
        // print a string to the standard output stream that asks the user whether or not to end the game
        if (askForStop(std::cout, std::cin))
        {
            // if that string is "yes" the member function should return a value to indicate success, and otherwise it should repeat the sequence of steps
            return STOP;
        }
    }
}

void PinochleGame::print(std::ostream& os, const std::size_t rc)
{
    int numPlayer = players.size();
    // print each player's status
    for (int i = 0; i < numPlayer; ++i)
    {
        os << "player name: " << players[i] << std::endl;
        hands[i].print(os, rc);
    }
}

void PinochleGame::collectAll()
{
    int numPlayer = players.size();
    // collect cards from each player hand
    for (int i = 0; i < numPlayer; ++i)
    {
        deck.collect(hands[i]);
    }
}

bool PinochleGame::askForStop(std::ostream& os, std::istream& is)
{
    std::string input;
    // prompt hint message
    os << std::endl
        << ">>> Do you wish to stop playing? (yes/*) " << std::endl;
    // read in a string from the standard input stream
    is >> input;
    // return whether input is yes
    return "yes" == input;
}

std::ostream& operator<<(std::ostream& os, const PinochleMelds& pm) {
    std::string meldName;
    switch (pm)
    {
    case PinochleMelds::dix:
        meldName = "dix";
        break;
    case PinochleMelds::offsuitmarriage:
        meldName = "offsuitmarriage";
        break;
    case PinochleMelds::fortyjacks:
        meldName = "fortyjacks";
        break;
    case PinochleMelds::pinochle:
        meldName = "pinochle";
        break;
    case PinochleMelds::insuitmarriage:
        meldName = "insuitmarriage";
        break;
    case PinochleMelds::sixtyqueens:
        meldName = "sixtyqueens";
        break;
    case PinochleMelds::eightykings:
        meldName = "eightykings";
        break;
    case PinochleMelds::hundredaces:
        meldName = "hundredaces";
        break;
    case PinochleMelds::insuitrun:
        meldName = "insuitrun";
        break;
    case PinochleMelds::doublepinochle:
        meldName = "doublepinochle";
        break;
    case PinochleMelds::fourhundredjacks:
        meldName = "fourhundredjacks";
        break;
    case PinochleMelds::sixhundredqueens:
        meldName = "sixhundredqueens";
        break;
    case PinochleMelds::eighthundredkings:
        meldName = "eighthundredkings";
        break;
    case PinochleMelds::thousandaces:
        meldName = "thousandaces";
        break;
    case PinochleMelds::insuitdoublerun:
        meldName = "insuitdoublerun";
        break;
    default:
        meldName = "not_exists";
        break;
    }
    //return namestring and meldscore
    return os << meldName << " " << PinochleGame::PinochleMeldsPointValue[static_cast<int>(pm)] << std::endl;
}

void PinochleGame::suit_independent_evaluation(const CardSet<PinochleRank, Suit>& cs, std::vector<PinochleMelds>& pmv) {
    //call copy constructor and make an independent copy
    CardSet<PinochleRank, Suit> csl(cs);
    //data returns a pointer to the content member fo class CardSet
    const std::vector<Card<PinochleRank, Suit>> CardSet<PinochleRank, Suit>::* pdata = CardSet<PinochleRank, Suit>::data();
    //to use pdata, bind to an object of CardSet
    auto s = csl.*pdata;
    //sort and reverse the vector
    std::sort(s.begin(), s.end(), cardSuitIsSmaller<PinochleRank, Suit>);
    std::sort(s.begin(), s.end(), cardRankIsSmaller<PinochleRank, Suit>);
    std::reverse(s.begin(), s.end());
    /*for (auto i : s)
        std::cout << i << ' ';
    std::cout << std::endl;*/

    int spd = 0;
    int dmd = 0;
    size_t i = 0;
    int count = 0;
    //while loop to check scores for each cases
    while (true) {
        if (s.at(i).rank == PinochleRank::Ace) {
            count = 0;
            while (s.at(i).rank == PinochleRank::Ace) {
                i++;
                count++;
                if (i >= PINOCHLE_NUM_CARDS) {
                    break;
                }
            }
            if (count >= EIGHT_SAME_RANKS) {
                pmv.push_back(PinochleMelds::thousandaces);
            }
            else if (count >= FOUR_SAME_RANKS) {
                pmv.push_back(PinochleMelds::hundredaces);
            }
        }
        if (s.at(i).rank == PinochleRank::Ten) {
            while (s.at(i).rank == PinochleRank::Ten) {
                i++;
                if (i >= PINOCHLE_NUM_CARDS) {
                    break;
                }
            }
        }
        if (s.at(i).rank == PinochleRank::King) {
            count = 0;
            while (s.at(i).rank == PinochleRank::King) {
                i++;
                count++;
                if (i >= PINOCHLE_NUM_CARDS) {
                    break;
                }
            }
            if (count >= EIGHT_SAME_RANKS) {
                pmv.push_back(PinochleMelds::eighthundredkings);
            }
            else if (count >= FOUR_SAME_RANKS) {
                pmv.push_back(PinochleMelds::eightykings);
            }
        }
        if (s.at(i).rank == PinochleRank::Queen) {
            count = 0;
            while (s.at(i).rank == PinochleRank::Queen && i < PINOCHLE_NUM_CARDS) {
                if (s.at(i).suit == Suit::Spades) {
                    spd++;
                }
                i++;
                count++;
                if (i >= PINOCHLE_NUM_CARDS) {
                    break;
                }
            }
            if (count >= EIGHT_SAME_RANKS) {
                pmv.push_back(PinochleMelds::sixhundredqueens);
            }
            else if (count >= FOUR_SAME_RANKS) {
                pmv.push_back(PinochleMelds::sixtyqueens);
            }
        }
        if (s.at(i).rank == PinochleRank::Jack) {
            count = 0;
            while (s.at(i).rank == PinochleRank::Jack) {
                if (s.at(i).suit == Suit::Diamonds) {
                    dmd++;
                }
                i++;
                count++;
                if (i >= PINOCHLE_NUM_CARDS) {
                    break;
                }
            }
            if (count >= EIGHT_SAME_RANKS) {
                pmv.push_back(PinochleMelds::fourhundredjacks);
            }
            else if (count >= FOUR_SAME_RANKS) {
                pmv.push_back(PinochleMelds::fortyjacks);
            }
        }

        if (i >= PINOCHLE_NUM_CARDS || s.at(i).rank == PinochleRank::Nine) {
            break;
        }
    }

    if (dmd >= DOUBLE_PINOCHLE_CASE && spd >= DOUBLE_PINOCHLE_CASE) {
        pmv.push_back(PinochleMelds::doublepinochle);
    }
    else if (dmd >= PINOCHLE_CASE && spd >= PINOCHLE_CASE) {
        pmv.push_back(PinochleMelds::pinochle);
    }

}