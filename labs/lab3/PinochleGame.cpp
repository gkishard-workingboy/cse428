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
std::pair<int, int> TEAM_1_INDICES(0,2);
std::pair<int, int> TEAM_2_INDICES(1,3);

unsigned int PinochleGame::PinochleMeldsPointValue[PINOCHLE_NUM_ITEMS] = { 10, 20, 40, 40, 40, 60, 80, 100, 150, 300, 400, 600, 800, 1000, 1500 };

PinochleGame::PinochleGame(int argc, const char* argv[]): Game(argc, argv), trump_suit(Suit::undefined){
    // create as many hands as players in the game
    for (int i = Game::firstPlayerIndex; i < argc; ++i) {
        // will call default constructor of CardSet
        hands.emplace_back();
        bids.push_back(0);
        total_meld_values.push_back(0);
        scores.push_back(0);
    }
}

void PinochleGame::deal() {
    // size of a packet
    const int packet = 3;
    // number of players in game
    int numHands = hands.size();
    // repeatedly shift a packet of cards to each hand of players, starting with the player right after the dealer and ending with the dealer.
    while(!deck.isEmpty()){
    for (int p = 1; p <= numHands && !deck.isEmpty(); ++p) {
        // current hand
        auto& hand = hands[(dealer + p) % numHands];
        // shift a packet of cards
        for (int i = 0; i < packet && !deck.isEmpty(); ++i) {
            deck >> hand;
        }
    }
    }
}

void PinochleGame::make_bid(std::vector<PinochleMelds>& melds, CardSet<PinochleRank, Suit>& hand, size_t playerIndex){
    unsigned int meld_value_sum = 0;
    for(PinochleMelds meld: melds){
        meld_value_sum += PinochleGame::PinochleMeldsPointValue[static_cast<int>(meld)];
    }
    total_meld_values[playerIndex] = meld_value_sum;

    unsigned int bid = meld_value_sum;
    const std::vector<Card<PinochleRank, Suit>> CardSet<PinochleRank, Suit>::* pdata = CardSet<PinochleRank, Suit>::data();
    std::vector<Card<PinochleRank, Suit>> cards = hand.*pdata;
    for(Card<PinochleRank, Suit> card: cards){
        if(card.rank == PinochleRank::undefined){
            throw std::runtime_error("Error: undefined card found in a hand");
        }
        bid += PinochleDeck::PinochleRanksPointValue[static_cast<int>(card.rank)];
    }
    bids[playerIndex] = bid;
}

PinochleContractTeam PinochleGame::award_contract(){
    unsigned int team1_bid = bids.at(TEAM_1_INDICES.first) + bids.at(TEAM_1_INDICES.second);
    unsigned int team2_bid = bids.at(TEAM_2_INDICES.first) + bids.at(TEAM_2_INDICES.second);
    if(team1_bid == team2_bid){
        return PinochleContractTeam::misdeal;
    }
    else if (team1_bid > team2_bid){
        int team1Index = static_cast<int>(PinochleContractTeam::team1);
        scores.at(team1Index) = scores.at(team1Index) + total_meld_values.at(TEAM_1_INDICES.first) + total_meld_values.at(TEAM_1_INDICES.second);
        return PinochleContractTeam::team1;
    }
    else {
        int team2Index = static_cast<int>(PinochleContractTeam::team2);
        scores.at(team2Index) = scores.at(team2Index) + total_meld_values.at(TEAM_2_INDICES.first) + total_meld_values.at(TEAM_2_INDICES.second);
        return PinochleContractTeam::team2;
    }
}

std::string PinochleGame::to_string(const PinochleContractTeam& t){
    switch(t){
        case PinochleContractTeam::team1:
            return "team 1";
        case PinochleContractTeam::team2:
            return "team 2";
        default:
            return "misdeal";
    }
}

Card<PinochleRank, Suit> PinochleGame::first_trick(CardSet<PinochleRank, Suit>& trick, CardSet<PinochleRank, Suit>& first_hand){
    const std::vector<Card<PinochleRank, Suit>> CardSet<PinochleRank, Suit>::* pdata = CardSet<PinochleRank, Suit>::data();
    std::vector< Card<PinochleRank, Suit> > first_hand_cards = first_hand.*pdata;
    std::sort(first_hand_cards.begin(), first_hand_cards.end(), cardRankIsSmaller<PinochleRank, Suit>);
    PinochleRank maxRank = first_hand_cards.back().rank;
    bool playing_trump_card = false;
    int trick_card_position = 0;
    for(std::vector< Card<PinochleRank, Suit> >::reverse_iterator rit = first_hand_cards.rbegin(); rit != first_hand_cards.rend() && (*rit).rank == maxRank; ++rit){
        if((*rit).suit == trump_suit){
            playing_trump_card = true;
            break;
        }
        ++trick_card_position;
    }
    if(playing_trump_card){
        CardSet<PinochleRank, Suit> tmp;
        for(int i = 0; i < trick_card_position; ++i){
            first_hand >> tmp;
        }
        first_hand >> trick;
        while(!tmp.isEmpty()){
            tmp >> first_hand;
        }
    }
    else{
        first_hand >> trick;
    }

    std::vector< Card<PinochleRank, Suit> > trick_cards = trick.*pdata;
    return trick_cards.back();
}

bool PinochleGame::trump_led_trick(CardSet<PinochleRank, Suit>& trick, CardSet<PinochleRank, Suit>& hand, Card<PinochleRank, Suit>& maxTrumpCard){
    const std::vector<Card<PinochleRank, Suit>> CardSet<PinochleRank, Suit>::* pdata = CardSet<PinochleRank, Suit>::data();
    std::vector<Card<PinochleRank, Suit>> hand_cards = hand.*pdata;
    std::sort(hand_cards.begin(), hand_cards.end(), cardRankIsSmaller<PinochleRank, Suit>);
    bool trump_card_found = false;
    bool new_winner = false;
    int trick_card_position = 0;
    std::vector< Card<PinochleRank, Suit> >::reverse_iterator rit = hand_cards.rbegin();
    while(rit != hand_cards.rend()){
        if((*rit).suit == trump_suit){
            trump_card_found = true;
            if((*rit).rank > maxTrumpCard.rank){
                maxTrumpCard = *rit;
                new_winner = true;
            }
            else {
                ++rit;
                while(rit != hand_cards.rend() && (*rit).suit == trump_suit){
                    ++trick_card_position;
                    ++rit;
                }
            }
            break;
        }
        ++trick_card_position;
        ++rit;
    }

    if(trump_card_found){
        CardSet<PinochleRank, Suit> tmp;
        for(int i = 0; i < trick_card_position; ++i){
            hand >> tmp;
        }
        hand >> trick;
        while(!tmp.isEmpty()){
            tmp >> hand;
        }
    }
    else {
        std::reverse(hand_cards.begin(), hand_cards.end());
        hand >> trick;
    }

    return new_winner;
}

void PinochleGame::play_tricks(PinochleContractTeam team_with_contract){
    std::vector<int> player_order;
    if(team_with_contract == PinochleContractTeam::team1){
        player_order = {TEAM_1_INDICES.first, TEAM_1_INDICES.second, TEAM_2_INDICES.first, TEAM_2_INDICES.second};
    }
    else {
        player_order = {TEAM_2_INDICES.first, TEAM_2_INDICES.second, TEAM_1_INDICES.first, TEAM_1_INDICES.second};
    }

    CardSet<PinochleRank, Suit> trick;
    CardSet<PinochleRank, Suit> first_hand = hands[player_order.front()];
    Card<PinochleRank, Suit> first_trick_card = first_trick(trick, first_hand);
    Suit leading_suit = first_trick_card.suit;
    Card<PinochleRank, Suit> winningCard = first_trick_card;
    int winningPlayer = 0; //tracks index (of player_order) that points to winner
    const int secondPlayerIndex = 1;

    if(leading_suit == trump_suit){
        for(int i = secondPlayerIndex; i < player_order.size(); ++i){
            int currentPlayer = player_order.at(i);
            bool new_winner = trump_led_trick(trick, hands[currentPlayer], winningCard);
            if(new_winner){
                winningPlayer = i;
            }
        }
    }
    else {
        
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
        //make trump_suit the last card dealt
        const std::vector<Card<PinochleRank, Suit>> CardSet<PinochleRank, Suit>::* pdata = CardSet<PinochleRank, Suit>::data();
        auto dealer_hand = hands.at(dealer).*pdata;
        trump_suit = dealer_hand.back().suit;
        // print out each player's name and then the cards in their hand to the standard output stream
        print(std::cout, CardsInRow);
        // find who wins the contract (or if there's a misdeal). If there's no misdeal, update the dealer
        PinochleContractTeam award_contract_result = award_contract();
        if(award_contract_result != PinochleContractTeam::misdeal){
            dealer = (dealer + 1) % players.size();
            int teamIndex = static_cast<int>(award_contract_result);
            std::cout << "contract went to " << to_string(award_contract_result) << ", score: " << scores.at(teamIndex) << std::endl;
            play_tricks(award_contract_result);
        }
        else {
            std::cout << "misdeal" << std::endl;
        }
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
        suit_dependent_evaluation(hands[i], melds, trump_suit);
        std::cout << "Melds:";
        for (auto meld : melds)
            std::cout << "  " << meld;
        std::cout << std::endl;
        make_bid(melds, hands[i], i);
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
    bool dix = false;

     while (i < s.size()) {
        if(s.at(i).suit == passed_suit){
            for (j = i; j < s.size() && s.at(j).suit == passed_suit; ++j) {
                if(s.at(j).rank == PinochleRank::Nine){
                    dix = true;
                }
                else {
                    int rank_mask = 1 << (static_cast<int>(s.at(j).rank) - 1);
                    if((run & rank_mask) > 0){
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

            i = j;
        }
        else{
            int current_suit_mask = 1 << static_cast<int>(s.at(i).suit);
            if(s.at(i).rank == PinochleRank::King){
                king_all_suits |= current_suit_mask;
            }
            if(s.at(i).rank == PinochleRank::Queen){
                queen_all_suits |= current_suit_mask;
            }
            ++i;
        }
    }

    if(double_run == run_mask){
        pmv.push_back(PinochleMelds::insuitdoublerun);
    }
    else if (run == run_mask){
        pmv.push_back(PinochleMelds::insuitrun);
    }

    int marriage = king_all_suits & queen_all_suits;
    if((marriage & passed_suit_mask) == passed_suit_mask){
        pmv.push_back(PinochleMelds::insuitmarriage);
    }
    else if(marriage > 0){
        pmv.push_back(PinochleMelds::offsuitmarriage);
    }

    if(dix){
        pmv.push_back(PinochleMelds::dix);
    }
}
