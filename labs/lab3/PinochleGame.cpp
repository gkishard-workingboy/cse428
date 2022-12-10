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
#include <typeinfo>
#include <type_traits>

using namespace std;

const int EIGHT_SAME_RANKS = 8;
const int FOUR_SAME_RANKS = 4;
const int DOUBLE_PINOCHLE_CASE = 2;
const int PINOCHLE_CASE = 1;
const int SUIT_MASK = (1 << static_cast<int>(Suit::undefined)) - 1;
std::pair<int, int> TEAM_1_INDICES(0,2);
std::pair<int, int> TEAM_2_INDICES(1,3);
vector<pair<int, int> > index_pairs = {TEAM_1_INDICES, TEAM_2_INDICES};
const int secondPlayerIndex = 1;
const unsigned int LAST_TRICK_BONUS = 10;
const unsigned int WIN_THRESHOLD = 1500;

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
    for(size_t j = 0; j < index_pairs.size(); ++j){
        running_tally.push_back(0);
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

unsigned int PinochleGame::total_value(CardSet<PinochleRank, Suit>& cs){
    const std::vector<Card<PinochleRank, Suit>> CardSet<PinochleRank, Suit>::* pdata = CardSet<PinochleRank, Suit>::data();
    std::vector<Card<PinochleRank, Suit>> cards = cs.*pdata;
    unsigned int sum = 0;
    for(Card<PinochleRank, Suit> card: cards){
        if(card.rank == PinochleRank::undefined){
            throw std::runtime_error("Error: undefined card found in a hand");
        }
        sum += PinochleDeck::PinochleRanksPointValue[static_cast<int>(card.rank)];
    }
    return sum;
}

void PinochleGame::make_bid(std::vector<PinochleMelds>& melds, CardSet<PinochleRank, Suit>& hand, size_t playerIndex){
    unsigned int meld_value_sum = 0;
    for(PinochleMelds meld: melds){
        meld_value_sum += PinochleGame::PinochleMeldsPointValue[static_cast<int>(meld)];
    }
    total_meld_values[playerIndex] = meld_value_sum;

    unsigned int bid = meld_value_sum + total_value(hand);
    bids[playerIndex] = bid;
}

void PinochleGame::make_all_bids(){
    for(size_t i = 0; i < all_melds.size(); ++i){
        make_bid(all_melds[i], hands[i], i);
    }
}

PinochleContractTeam PinochleGame::award_contract(){
    unsigned int team1_bid = bids.at(TEAM_1_INDICES.first) + bids.at(TEAM_1_INDICES.second);
    unsigned int team2_bid = bids.at(TEAM_2_INDICES.first) + bids.at(TEAM_2_INDICES.second);
    if(team1_bid == team2_bid){
        return PinochleContractTeam::misdeal;
    }
    else if (team1_bid > team2_bid){
        int team1Index = static_cast<int>(PinochleContractTeam::team1);
        running_tally.at(team1Index) = total_meld_values.at(TEAM_1_INDICES.first) + total_meld_values.at(TEAM_1_INDICES.second);
        return PinochleContractTeam::team1;
    }
    else {
        int team2Index = static_cast<int>(PinochleContractTeam::team2);
        running_tally.at(team2Index) = total_meld_values.at(TEAM_2_INDICES.first) + total_meld_values.at(TEAM_2_INDICES.second);
        return PinochleContractTeam::team2;
    }
}

void PinochleGame::print_contract_result(std::ostream& os, PinochleContractTeam team){
    if(team == PinochleContractTeam::misdeal){
        os << "misdeal, re-dealing cards..." << std::endl;
    }
    else {
        os << "contract went to " << to_string(team) << ", running tally: " << running_tally.at(static_cast<int>(team)) << std::endl;
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

void PinochleGame::initialize_play_order(vector<int>& player_order, PinochleContractTeam contract_team){
    pair<int, int> contract_pair = index_pairs.at(static_cast<int>(contract_team));
    unsigned int bid1 = bids.at(contract_pair.first);
    unsigned int bid2 = bids.at(contract_pair.second);
    size_t leadingIndex;
    if(bid1 >= bid2){
        leadingIndex = contract_pair.first;
    }
    else {
        leadingIndex = contract_pair.second;
    }
    player_order.push_back(leadingIndex);
    for(size_t i = 0; i < players.size(); ++i){
        if(i != leadingIndex){
            player_order.push_back(i);
        }
    }
}

Card<PinochleRank, Suit> PinochleGame::play_leading_card(CardSet<PinochleRank, Suit>& hand, CardSet<PinochleRank, Suit>& trick){
    const std::vector<Card<PinochleRank, Suit>> CardSet<PinochleRank, Suit>::* pdata = CardSet<PinochleRank, Suit>::data();
    vector<Card<PinochleRank, Suit>> cards = hand.*pdata;
    sort(cards.begin(), cards.end(), cardRankIsSmaller<PinochleRank, Suit>);
    vector<Card<PinochleRank, Suit>>::reverse_iterator rit = cards.rbegin();
    PinochleRank maxRank = (*rit).rank;
    Suit leading_suit = Suit::undefined;
    for(; rit != cards.rend() && (*rit).rank == maxRank; ++rit){
        if((*rit).suit == trump_suit){
            leading_suit = trump_suit;
            break;
        }
    }
    if(leading_suit == Suit::undefined){
        leading_suit = cards.back().suit;
    }
    add_to_trick(hand, trick, maxRank, leading_suit);
    return Card(maxRank, leading_suit);
}

void PinochleGame::add_to_trick(CardSet<PinochleRank, Suit>& hand, CardSet<PinochleRank, Suit>& trick, PinochleRank r, Suit s){
    const std::vector<Card<PinochleRank, Suit>> CardSet<PinochleRank, Suit>::* pdata = CardSet<PinochleRank, Suit>::data();
    CardSet<PinochleRank, Suit> tmp;
    bool foundCard = false;
    while(!hand.isEmpty()){
        Card<PinochleRank, Suit> nextCard = (hand.*pdata).back();
        if(nextCard.rank == r && nextCard.suit == s){
            foundCard = true;
            hand >> trick;
            break;
        }
        hand >> tmp;
    }
    while(!tmp.isEmpty()){
        tmp >> hand;
    }
    if(!foundCard){
        cout << "error: getting " << Card(r,s) << "from ";
        hand.print(cout, 8);
        cout << "trick: ";
        trick.print(cout, 8);
        throw runtime_error("could not find this card");
    }
}

//return rank of highest trump card in the trick after this play
PinochleRank PinochleGame::trump_led_play(CardSet<PinochleRank, Suit>& hand, CardSet<PinochleRank, Suit>& trick, PinochleRank highest_trump_rank){
    const std::vector<Card<PinochleRank, Suit>> CardSet<PinochleRank, Suit>::* pdata = CardSet<PinochleRank, Suit>::data();
    vector<Card<PinochleRank, Suit>> hand_cards = hand.*pdata;
    sort(hand_cards.begin(), hand_cards.end(), cardSuitIsSmaller<PinochleRank, Suit>);
    //function returns in this loop if player has a trump card
    for(vector<Card<PinochleRank, Suit>>::reverse_iterator rit = hand_cards.rbegin(); rit != hand_cards.rend(); ++rit){
        if((*rit).suit == trump_suit){ //reached highest trump card in hand
            if((*rit).rank > highest_trump_rank){
                //hand has higher trump card than any played before
                cout << endl << 1 << endl;
                add_to_trick(hand, trick, (*rit).rank, trump_suit);
                return (*rit).rank;
            }
            else {
                //get lowest trump card
                PinochleRank lowest_trump_rank = (*rit).rank;
                while(rit != hand_cards.rend() && (*rit).suit == trump_suit){
                    lowest_trump_rank = (*rit).rank;
                    ++rit;
                }
                cout << endl << 2 << endl;
                add_to_trick(hand, trick, lowest_trump_rank, trump_suit);
                return highest_trump_rank;
            }
        }
    }
    //player does not have trump card, get lowest ranked card
    sort(hand_cards.begin(), hand_cards.end(), cardRankIsSmaller<PinochleRank, Suit>);
    cout << endl << 3 << endl;
    add_to_trick(hand, trick, hand_cards.front().rank, hand_cards.front().suit);
    return highest_trump_rank;
}

//returns ranks of highest-ranked led suit and trump cards in the trick after this play. The pair contains (highest_led_rank, highest_trump_rank)
pair<PinochleRank, PinochleRank> PinochleGame::non_trump_led_play(CardSet<PinochleRank, Suit>& hand, CardSet<PinochleRank, Suit>& trick, pair<PinochleRank, PinochleRank> ranks, Suit leading_suit){
    PinochleRank highest_led_rank = ranks.first;
    PinochleRank highest_trump_rank = ranks.second;
    const std::vector<Card<PinochleRank, Suit>> CardSet<PinochleRank, Suit>::* pdata = CardSet<PinochleRank, Suit>::data();
    vector<Card<PinochleRank, Suit>> hand_cards = hand.*pdata;
    sort(hand_cards.begin(), hand_cards.end(), cardSuitIsSmaller<PinochleRank, Suit>);
    for(vector<Card<PinochleRank, Suit>>::reverse_iterator rit = hand_cards.rbegin(); rit != hand_cards.rend(); ++rit){
        if((*rit).suit == leading_suit){
            //player has leading suit card
            if(highest_trump_rank == PinochleRank::undefined || (*rit).rank <= highest_led_rank){
                //trump card was played or player's highest leading suit card is lower ranked than another leading suit card played before
                //add lowest leading suit card
                PinochleRank lowest_led_rank = (*rit).rank;
                while(rit != hand_cards.rend() && (*rit).suit == leading_suit){
                    lowest_led_rank = (*rit).rank;
                    ++rit;
                }
                cout << endl << 4 << endl;
                add_to_trick(hand, trick, lowest_led_rank, leading_suit);
                return {highest_led_rank, highest_trump_rank};
            }
            cout << endl << 5 << endl;
            add_to_trick(hand, trick, (*rit).rank, leading_suit);
            return {(*rit).rank, highest_trump_rank};
        }
    }

    //player does not have a card of the leading suit
    for(vector<Card<PinochleRank, Suit>>::reverse_iterator rit = hand_cards.rbegin(); rit != hand_cards.rend(); ++rit){
        if((*rit).suit == trump_suit){
            //player has trump card
            if(highest_trump_rank == PinochleRank::undefined || (*rit).rank > highest_trump_rank){
                //player has higher trump card than any played before
                cout << endl << 6 << endl;
                add_to_trick(hand, trick, (*rit).rank, trump_suit);
                return {highest_led_rank, (*rit).rank};
            }
            break; //if player's max trump card is not higher than any played, exit loop
        }
    }

    //add lowest ranked card of any non-trump suit
    sort(hand_cards.begin(), hand_cards.end(), cardRankIsSmaller<PinochleRank, Suit>);
    for(vector<Card<PinochleRank, Suit>>::const_iterator cit = hand_cards.cbegin(); cit != hand_cards.cend(); ++cit){
        if((*cit).suit != trump_suit){
            cout << endl << 7 << endl;
            add_to_trick(hand, trick, (*cit).rank, (*cit).suit);
            return {highest_led_rank, highest_trump_rank};
        }
    }

    cout << "hand";
    hand.print(cout, 8);
    cout << "trick";
    hand.print(cout, 8);
    cout << "trump " << trump_suit << "leading " << leading_suit << endl;
    throw runtime_error("failed to add card to trick");
}

//return i, where players[i] is the first person who played the card of wanted_rank and wanted_suit
int PinochleGame::player_with_card(CardSet<PinochleRank, Suit>& trick, vector<int>& player_order, PinochleRank wanted_rank, Suit wanted_suit){
    const std::vector<Card<PinochleRank, Suit>> CardSet<PinochleRank, Suit>::* pdata = CardSet<PinochleRank, Suit>::data();
    vector<Card<PinochleRank, Suit>> trick_cards = trick.*pdata;
    for(size_t i = 0; i < trick_cards.size(); ++i){
        Card<PinochleRank, Suit> currentCard = trick_cards.at(i);
        if(currentCard.suit == wanted_suit && currentCard.rank == wanted_rank){
            return player_order.at(i);
        }
    }
    throw runtime_error("trick does not have a card of wanted_rank and wanted_suit");
}

//returns true if the team with the contract has won the game
bool PinochleGame::update_scores(PinochleContractTeam contract_team){
    int teamIndex = static_cast<int>(contract_team);
    int tally = running_tally.at(teamIndex);
    pair<int,int> team_players = index_pairs.at(teamIndex);
    int total_bid = bids.at(team_players.first) + bids.at(team_players.second);
    if(tally >= total_bid){
        scores.at(teamIndex) = scores.at(teamIndex) + total_bid;
    }
    return scores.at(teamIndex) >= WIN_THRESHOLD;
}

void PinochleGame::reset_member_variables(){
    int team1Index = static_cast<int>(PinochleContractTeam::team1);
    int team2Index = static_cast<int>(PinochleContractTeam::team2);
    bids[team1Index] = 0;
    bids[team2Index] = 0;
    running_tally[team1Index] = 0;
    running_tally[team2Index] = 0;
    all_melds.clear();
}

//returns i, where players[i] is the winner of the trick
int PinochleGame::do_trick(PinochleContractTeam contract_team, vector<int>& player_order, bool lastTrick){
    //for testing
                cout << "player order ";
            for(int i : player_order){
                cout << players.at(i) << " ";
            }
            cout << endl;
    //end testing
    CardSet<PinochleRank, Suit> trick;
    Card<PinochleRank, Suit> leading_card = play_leading_card(hands.at(player_order.front()), trick); // play leading card
    Suit leading_suit = leading_card.suit;
    cout << "trump suit: " << trump_suit << " leading suit: " << leading_suit;
    int winner;
    PinochleRank winning_rank = PinochleRank::undefined;
    Suit winning_suit = Suit::undefined;
    if(leading_suit == trump_suit){
        PinochleRank highest_trump_rank = leading_card.rank;
        for(size_t i = secondPlayerIndex; i < player_order.size(); ++i){
            int currentPlayer = player_order.at(i);
            CardSet<PinochleRank, Suit>& hand = hands.at(currentPlayer);
            highest_trump_rank = trump_led_play(hand, trick, highest_trump_rank);
        }
        winner = player_with_card(trick, player_order, highest_trump_rank, trump_suit);
        winning_rank = highest_trump_rank;
        winning_suit = trump_suit;
    }
    else {
        //highest_ranks keeps track of the highest trump and led suit cards in the trick
        //highest_ranks.first = highest rank of led suit, highest_ranks.second = highest rank of trump suit
        pair<PinochleRank, PinochleRank> highest_ranks(leading_card.rank, PinochleRank::undefined);
        for(size_t i = secondPlayerIndex; i < player_order.size(); ++i){
            int currentPlayer = player_order.at(i);
            CardSet<PinochleRank, Suit>& hand = hands.at(currentPlayer);
            highest_ranks = non_trump_led_play(hand, trick, highest_ranks, leading_suit);
        }
        if(highest_ranks.second == PinochleRank::undefined){
            //trump card wasn't played
            winner = player_with_card(trick, player_order, highest_ranks.first, leading_suit);
            winning_rank = highest_ranks.first;
            winning_suit = leading_suit;
        }
        else {
            winner = player_with_card(trick, player_order, highest_ranks.second, trump_suit);
            winning_rank = highest_ranks.second;
            winning_suit = trump_suit;
        }
    }
    cout << "cards played: ";
    trick.print(cout, 8);
    cout << "trick winner: " << players.at(winner) << ", who played " << Card(winning_rank, winning_suit);

    //update running tally if appropriate
    bool team1Wins = winner == TEAM_1_INDICES.first || winner == TEAM_1_INDICES.second;
    bool team1GetsPoints = team1Wins && contract_team == PinochleContractTeam::team1;
    bool team2GetsPoints = !team1Wins && contract_team == PinochleContractTeam::team2;
    int teamIndex;
    if(team1GetsPoints && team2GetsPoints){
        throw runtime_error("both teams cannot win a trick");
    }
    int additional_points;
    if(team1GetsPoints){
        teamIndex = static_cast<int>(PinochleContractTeam::team1);
        additional_points = total_value(trick);
        if(lastTrick){
            additional_points += LAST_TRICK_BONUS;
        }
        running_tally.at(teamIndex) = running_tally.at(teamIndex) + additional_points;
        cout << "team 1 (" << players.at(TEAM_1_INDICES.first) << ", " << players.at(TEAM_1_INDICES.second) << ") got " << additional_points << " points" << endl;
    }
    if(team2GetsPoints){
        teamIndex = static_cast<int>(PinochleContractTeam::team2);
        additional_points = total_value(trick);
        if(lastTrick){
            additional_points += LAST_TRICK_BONUS;
        }
        running_tally.at(teamIndex) = running_tally.at(teamIndex) + additional_points;
        cout << "team 2 (" << players.at(TEAM_2_INDICES.first) << ", " << players.at(TEAM_2_INDICES.second) << ") got " << additional_points << " points" << endl;
    }

    deck.collect(trick);
    return winner;
}

string PinochleGame::team_members_to_string(PinochleContractTeam t){
    int teamIndex = static_cast<int>(t);
    pair<int,int> members = index_pairs.at(teamIndex);
    return to_string(t) + " (" + players.at(members.first) + ", " + players.at(members.second) + ")";
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
        evaluate_hands();
        // print out each player's name and then the cards in their hand to the standard output stream
        print(std::cout, CardsInRow);
        // find who wins the contract (or if there's a misdeal). If there's no misdeal, update the dealer
        make_all_bids();
        PinochleContractTeam award_contract_result = award_contract();
        print_contract_result(std::cout, award_contract_result);
        int cardsPerPlayer = dealer_hand.size();
        if(award_contract_result != PinochleContractTeam::misdeal){
            dealer = (dealer + 1) % players.size();
            vector<int> player_order;
            initialize_play_order(player_order, award_contract_result);
            for(int i = cardsPerPlayer; i > 0; --i){
                unsigned int winner = do_trick(award_contract_result, player_order, (i == 1)); //boolean parameter is true if players only have 1 card left
                /*if(askForStop(cout, cin)){
                    return STOP;
                }*/
                //update player order
                player_order.clear();
                player_order.push_back(winner);
                for(size_t j = 0; j < players.size(); ++j){
                    if(j != winner){
                        player_order.push_back(j);
                    }
                }
            }

            if(update_scores(award_contract_result)){
                cout << "Game over. " << endl;
                cout << "Winner: " << team_members_to_string(award_contract_result) << " with score " << scores.at(static_cast<int>(award_contract_result)) << endl;
                return STOP;
            }
            reset_member_variables();
        }
        else {
            collectAll();
            reset_member_variables();
        }
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
        os << "Melds:";
        vector<PinochleMelds>& melds = all_melds[i];
        for (auto meld : melds)
            os << "  " << meld;
        os << std::endl;
    }
}

void PinochleGame::evaluate_hands(){
    size_t numPlayer = players.size();
    for (size_t i = 0; i < numPlayer; ++i) {
        vector<PinochleMelds> melds;
        suit_independent_evaluation(hands[i], melds);
        suit_dependent_evaluation(hands[i], melds, trump_suit);
        all_melds.push_back(melds);
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
    int mask = 1;
    int mask_end = 1 << (static_cast<int>(Suit::undefined));
    while(mask < mask_end){
        if((marriage & mask) == mask){
            if(mask == passed_suit_mask){
                pmv.push_back(PinochleMelds::insuitmarriage);
            }
            else {
                pmv.push_back(PinochleMelds::offsuitmarriage);
            }
        }
        mask = mask << 1;
    }

    if(dix){
        pmv.push_back(PinochleMelds::dix);
    }
}
