/*
 * @FilePath: /428cpp/labs/lab2/PinochleGame.cpp
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Date: 2022-09-25 14:31:48
 * @LastEditTime: 2022-10-29 23:25:15
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

PinochleGame::PinochleGame(int argc, const char* argv[]): Game(argc, argv) {
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
    // repeatedly shift a packet of cards to each hand of players, starting with the player right after the dealer and ending with the dealer.
    for (int p = 1; p <= numHands && !deck.isEmpty(); ++p) {
        // current hand
        auto& hand = hands[(dealer + p) % numHands];
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

        dealer = (dealer + 1) % players.size();
    }
}

void PinochleGame::print(std::ostream& os, const std::size_t rc) {
    size_t numPlayer = players.size();
    // print each player's status
    for (size_t i = 0; i < numPlayer; ++i) {
        os << "player name: " << players[i];
        if(i == dealer){
            os << "*";
        }
        os << std::endl;
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

void PinochleGame::suit_dependent_evaluation(const CardSet<PinochleRank, Suit>& cs, std::vector<PinochleMelds>& pmv, Suit passed_suit){
    // call copy constructor and make an independent copy
    CardSet<PinochleRank, Suit> csl(cs);
    // data returns a pointer to the content member fo class CardSet
    const std::vector<Card<PinochleRank, Suit>> CardSet<PinochleRank, Suit>::* pdata = CardSet<PinochleRank, Suit>::data();
    // to use pdata, bind to an object of CardSet
    auto s = csl.*pdata;
    // sort (rank and then suit ordering relation) and reverse the vector
    std::sort(s.begin(), s.end(), cardSuitIsSmaller<PinochleRank, Suit>);
    std::reverse(s.begin(), s.end());

    size_t i = 0, j;
    int run_mask = (1 << static_cast<int>(PinochleRank::Ace)) - 1;
    int run = 0; // each bit represents one of J,Q,K,10,A. Bit is 1 if there's at least one card of that rank in the passed suit.
    int double_run = 0; // each bit represents one of J,Q,K,10,A. Bit is 1 if there's 2 cards of that rank in the passed suit.

    int passed_suit_mask = 1 << static_cast<int>(passed_suit);
    int king_all_suits = 0; // each bit represents a suit, the bit is set to 1 if there's a king of the given suit
    int queen_all_suits = 0; // each bit represents a suit, the bit is set to 1 if there's a queen of the given suit
    boolean dix = false;

     while (i < s.size()) {
        if(s.at(i).suit == passed_suit){
            for (j = i; j < s.size() && s.at(j).suit == passed_suit; ++j) {
                if(s.at(j).rank == PinochleRank::Nine){
                    dix = true;
                }
                else {
                    int rank_mask = 1 << (static_cast<int>(s.at(j).rank) - 1);
                    if(run & rank_mask > 0){
                        double_run |= rank_mask;
                    }
                    else {
                        run |= rank_mask;
                    }
                    if(s.at(j).rank == PinochleRank::King){
                        king_all_suits |= passed_suit_mask;
                    }
                    else if(s.at(j).rank == PinochleRank::Queen){
                        queen_all_suits |= passed_suit_mask;
                    }
                }
            }
        }
        else{
            int current_suit_mask = 1 << static_cast<int>(s.at(i).suit);
            if(s.at(i).rank == PinochleRank::King){
                king_all_suits |= current_suit_mask;
            }
            if(s.at(i).rank == PinochleRank::Queen){
                queen_all_suits |= current_suit_mask;
            }
        }
        i = j;
    }

    if(double_run == run_mask){
        pmv.push_back(PinochleMelds::insuitdoublerun);
    }
    else if (run == run_mask){
        pmv.push_back(PinochleMelds::insuitrun);
    }

    int marriage = king_all_suits & queen_all_suits;
    if(marriage == passed_suit_mask){
        pmv.push_back(PinochleMelds::insuitmarriage);
    }
    else if(marriage > 0){
        pmv.push_back(PinochleMelds::offsuitmarriage);
    }

    if(dix){
        pmv.push_back(PinochleMelds::dix);
    }
}
