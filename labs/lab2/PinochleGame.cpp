/*
 * @FilePath: /428cpp/labs/lab2/PinochleGame.cpp
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Date: 2022-09-25 14:31:48
 * @LastEditTime: 2022-12-09 16:16:03
 * @Description: Definition to PinochleGame.h
 *
 */

#include "PinochleGame.h"
#include <iostream>
#include <string>

const int EIGHT_SAME_RANKS = 8;
const int FOUR_SAME_RANKS = 4;
const int DOUBLE_PINOCHLE_CASE = 2;
const int PINOCHLE_CASE = 1;
const int SUIT_MASK = (1 << static_cast<int>(Suit::undefined)) - 1;

unsigned int PinochleGame::PinochleMeldsPointValue[PINOCHLE_NUM_ITEMS] = { 10, 20, 40, 40, 40, 60, 80, 100, 150, 300, 400, 600, 800, 1000, 1500 };

PinochleGame::PinochleGame(int argc, const char* argv[]) : Game(argc, argv) {
    // create as many hands as players in the game
    for (int i = Game::firstPlayerIndex; i < argc; ++i) {
        // will call default constructor of CardSet
        hands.emplace_back();
    }
}

void PinochleGame::deal() {
    // size of a packet
    const int packet = 3;
    // number of players in game
    int numHands = hands.size();
    // repeatedly shift a packet of cards to each hand of players
    for (int p = 0; !deck.isEmpty(); p = (p + 1) % numHands) {
        // current hand
        auto& hand = hands[p];
        // shift a packet of cards
        for (int i = 0; i < packet && !deck.isEmpty(); ++i) {
            deck >> hand;
        }
    }
}

int PinochleGame::play() {
    const int CardsInRow = 8;
    const int STOP = 0;

    while (true) {
        // call the deck's shuffle member function
        deck.shuffle();
        // call the deal member function to distribute the cards to the players
        deal();
        // print out each player's name and then the cards in their hand to the standard output stream
        print(std::cout, CardsInRow);

        // use the deck's collect member function repeatedly to move the cards back out of each player's hand into the deck
        collectAll();
        // print a string to the standard output stream that asks the user whether or not to end the game
        if (askForStop(std::cout, std::cin)) {
            // if that string is "yes" the member function should return a value to indicate success, and otherwise it should repeat the sequence of steps
            return STOP;
        }
    }
}

void PinochleGame::print(std::ostream& os, const std::size_t rc) {
    int numPlayer = players.size();
    // print each player's status
    for (int i = 0; i < numPlayer; ++i) {
        os << "player name: " << players[i] << std::endl;
        hands[i].print(os, rc);
        // for each hand initiate a vector and call suit_independent_evaluation to print scores
        std::vector<PinochleMelds> melds;
        suit_independent_evaluation(hands[i], melds);
        std::cout << "Melds:";
        for (auto meld : melds)
            std::cout << "  " << meld;
        std::cout << std::endl;
    }
}

void PinochleGame::collectAll() {
    int numPlayer = players.size();
    // collect cards from each player hand
    for (int i = 0; i < numPlayer; ++i) {
        deck.collect(hands[i]);
    }
}

bool PinochleGame::askForStop(std::ostream& os, std::istream& is) {
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
    switch (pm) {
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
    // outputs namestring and meldscore, then return ostream
    return os << meldName << " " << PinochleGame::PinochleMeldsPointValue[static_cast<int>(pm)];
}

void PinochleGame::suit_independent_evaluation(const CardSet<PinochleRank, Suit>& cs, std::vector<PinochleMelds>& pmv) {
    // call copy constructor and make an independent copy
    CardSet<PinochleRank, Suit> csl(cs);
    // data returns a pointer to the content member fo class CardSet
    const std::vector<Card<PinochleRank, Suit>> CardSet<PinochleRank, Suit>::* pdata = CardSet<PinochleRank, Suit>::data();
    // to use pdata, bind to an object of CardSet
    auto s = csl.*pdata;
    // sort (rank and then suit ordering relation) and reverse the vector
    std::sort(s.begin(), s.end(), cardRankIsSmaller<PinochleRank, Suit>);
    std::reverse(s.begin(), s.end());

    int spd = 0;
    int dmd = 0;
    size_t i = 0, j;
    int count = 0;

    int mask = 0;

    // while loop to check scores for each cases
    while (i < s.size()) {
        mask = 0;
        count = 0;
        if (s.at(i).rank == PinochleRank::Ace) {
            for (j = i; j < s.size() && s.at(j).rank == PinochleRank::Ace; ++j) {
                count++;
                mask |= 1 << static_cast<int>(s[j].suit);
            }
            if (count >= EIGHT_SAME_RANKS) {
                pmv.push_back(PinochleMelds::thousandaces);
            } else if (count >= FOUR_SAME_RANKS && mask == SUIT_MASK) {
                pmv.push_back(PinochleMelds::hundredaces);
            }
        }

        else if (s.at(i).rank == PinochleRank::King) {
            for (j = i; j < s.size() && s.at(j).rank == PinochleRank::King; ++j) {
                count++;
                mask |= 1 << static_cast<int>(s[j].suit);
            }
            if (count >= EIGHT_SAME_RANKS) {
                pmv.push_back(PinochleMelds::eighthundredkings);
            } else if (count >= FOUR_SAME_RANKS && mask == SUIT_MASK) {
                pmv.push_back(PinochleMelds::eightykings);
            }
        } else if (s.at(i).rank == PinochleRank::Queen) {
            for (j = i; j < s.size() && s.at(j).rank == PinochleRank::Queen; ++j) {
                count++;
                mask |= 1 << static_cast<int>(s[j].suit);
                if (s.at(j).suit == Suit::Spades) {
                    spd++;
                }
            }
            if (count >= EIGHT_SAME_RANKS) {
                pmv.push_back(PinochleMelds::sixhundredqueens);
            } else if (count >= FOUR_SAME_RANKS && mask == SUIT_MASK) {
                pmv.push_back(PinochleMelds::sixtyqueens);
            }
        } else if (s.at(i).rank == PinochleRank::Jack) {
            for (j = i; j < s.size() && s.at(j).rank == PinochleRank::Jack; ++j) {
                count++;
                mask |= 1 << static_cast<int>(s[j].suit);
                if (s.at(j).suit == Suit::Diamonds) {
                    dmd++;
                }
            }
            if (count >= EIGHT_SAME_RANKS) {
                pmv.push_back(PinochleMelds::fourhundredjacks);
            } else if (count >= FOUR_SAME_RANKS && mask == SUIT_MASK) {
                pmv.push_back(PinochleMelds::fortyjacks);
            }
        }
        // skip other kinds of rank.
        else {
            for (j = i + 1; j < s.size() && s.at(j).rank == s[i].rank; ++j)
                ;
        }
        i = j;
    }

    if (dmd >= DOUBLE_PINOCHLE_CASE && spd >= DOUBLE_PINOCHLE_CASE) {
        pmv.push_back(PinochleMelds::doublepinochle);
    } else if (dmd >= PINOCHLE_CASE && spd >= PINOCHLE_CASE) {
        pmv.push_back(PinochleMelds::pinochle);
    }
}
