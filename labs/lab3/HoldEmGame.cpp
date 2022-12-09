/*
 * @FilePath: /428cpp/labs/lab2/HoldEmGame.cpp
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Date: 2022-10-02 19:55:59
 * @LastEditTime: 2022-10-31 18:34:47
 * @Description: Definition to HoldEmGame.h
 *
 */
#include "HoldEmGame.h"
using namespace std;

const int handCards = 2;
const int LENGTH_OF_PAIR = 2;
const int LENGTH_OF_THREE = 3;
const int LENGTH_OF_FOUR = 4;
// standard number of cards in hand for evaluation
const int STD_HAND_NUM = 5;
const int ACE_OFFSET = 1;
const int ACE_LOW = 0;

HoldEmGame::HoldEmGame(int argc, const char* argv[]) : Game(argc, argv), state(HoldEmState::preflop), input_scores(players.size(), 0), playerStatus(players.size(), true), pot(0) {
    // create as many hands as players in the game
    for (int i = Game::firstPlayerIndex; i < argc; ++i) {
        // will call default constructor of CardSet
        hands.emplace_back();
        this->scores.push_back(60);
    }
}

void HoldEmGame::deal() {
    const int flopCards = 3;

    if (this->state == HoldEmState::preflop) {
        // repeatedly shift a card to each hand of players, starting with the player right after the dealer and ending with the dealer.
        for (size_t i = 0; i < handCards; i++) {
            for (size_t j = 1; j <= hands.size() && !deck.isEmpty(); j++) {
                deck >> hands[(dealer + j) % hands.size()];
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
        this->state = HoldEmState::undefined;
    }
    // do nothing for other states
}

vector<HoldEmAction> HoldEmGame::action(const CardSet<HoldEmRank, Suit>& cs) {
    /*if (this->state == HoldEmState::flop) {
    }*/

    CardSet<HoldEmRank, Suit> hand(cs);
    vector<Card<HoldEmRank, Suit>> CardSet<HoldEmRank, Suit>::* pdata = CardSet<HoldEmRank, Suit>::data();
    vector<Card<HoldEmRank, Suit>>& cards = hand.*pdata;
    if (cards[0].rank == cards[1].rank && cards[0].rank == HoldEmRank::Ace) {
        vector<HoldEmAction> result{ HoldEmAction::raise,HoldEmAction::raise };
        return result;
    }
    else if (cards[0].rank == cards[1].rank && ((cards[0].rank == HoldEmRank::King) || (cards[0].rank == HoldEmRank::Queen) || (cards[0].rank == HoldEmRank::Jack))) {
        vector<HoldEmAction> result{ HoldEmAction::raise,HoldEmAction::call };
        return result;
    }
    else if (cards[0].suit == cards[1].suit) {
        vector<HoldEmAction> result{ HoldEmAction::call,HoldEmAction::call };
        return result;
    }
    else if (((static_cast<int>(cards[0].rank) == static_cast<int>(cards[1].rank) + 1) && (cards[1].rank > HoldEmRank::Three)) || ((static_cast<int>(cards[1].rank) == static_cast<int>(cards[0].rank) + 1) && (cards[0].rank > HoldEmRank::Three))) {
        vector<HoldEmAction> result{ HoldEmAction::call,HoldEmAction::call };
        return result;
    }
    else if (cards[0].rank == cards[1].rank) {
        vector<HoldEmAction> result{ HoldEmAction::call,HoldEmAction::call };
        return result;
    }
    else {
        vector<HoldEmAction> result{ HoldEmAction::fold,HoldEmAction::fold };
        return result;
    }

}

void HoldEmGame::bet() {
    if (this->state == HoldEmState::flop) {
        size_t small_blind = (1 + dealer) % players.size();
        size_t big_blind = (2 + dealer) % players.size();
        scores[small_blind] -= 1;
        scores[big_blind] -= 2;
        input_scores[small_blind] += 1;
        input_scores[big_blind] += 2;
    }

    bool flag = true;
    bool raiseFlag = false;
    int largest_bet_of_round = 100; //initiate a value for the largest bet of the round
    while (flag == true) {
        for (auto i : scores)
            std::cout << i << ' ';
        long unsigned int totalPass = 0;
        int largest_bet; // largest value for call/raise check max value
        for (size_t k = 0; k < players.size(); ++k) {
            size_t i = (k + dealer + 3) % players.size();

            if (playerStatus[i] == false || input_scores[i] == largest_bet_of_round || scores[i] == 0) //will pass if conditions satisfy
                continue;

            cout << "Player " << i << ", Please input your action, choose from 'fold','call','raise'." << endl;
            vector<HoldEmAction> handAction = action(hands[i]);
            HoldEmAction playerAction;
            if (raiseFlag == false) {
                playerAction = handAction[0];
            }
            else {
                playerAction = handAction[1];
            }

            if (playerAction == HoldEmAction::fold) {
                playerStatus[i] = false;
                cout << "Player " << i << " folded." << endl;
            }
            else if (playerAction == HoldEmAction::call) {
                largest_bet = *max_element(std::begin(input_scores), std::end(input_scores));
                if (scores[i] <= largest_bet) {
                    pot = pot + scores[i];
                    input_scores[i] = scores[i];
                    scores[i] = 0;
                }
                else {
                    pot = pot - input_scores[i] + largest_bet;
                    scores[i] = scores[i] + input_scores[i] - largest_bet;
                    input_scores[i] = largest_bet;

                }
                cout << "Player " << i << " successfully called." << endl;
                cout << "Player " << i << " left with " << scores[i] << "." << endl;
            }
            else if (playerAction == HoldEmAction::raise) {
                raiseFlag = true;
                largest_bet = *max_element(std::begin(input_scores), std::end(input_scores));
                if (scores[i] <= largest_bet) {
                    cout << "Player " << i << " opted to ALL-IN" << endl;
                    pot = pot + scores[i];
                    input_scores[i] = scores[i];
                    scores[i] = 0;
                }
                else {
                    cout << "Player " << i << ", please bet. You can bet from 0 to " << scores[i] << endl;
                    int betInput;
                    if (this->state == HoldEmState::preflop) {
                        while (true) {
                            cin >> betInput;
                            if (betInput <= scores[i] && betInput >= 2) {
                                break;
                            }
                        }
                    }
                    else {
                        while (true) {
                            cin >> betInput;
                            if (betInput <= scores[i] && betInput >= 4) {
                                break;
                            }
                        }
                    }
                    pot = pot + betInput;
                    scores[i] = scores[i] - betInput;
                    input_scores[i] = input_scores[i] + betInput;
                    largest_bet_of_round = *max_element(std::begin(input_scores), std::end(input_scores));
                    cout << "Player " << i << " successfully bet " << betInput << endl;
                }

            }
            else {
                cout << "Wrong input key. usage: Please input your action, choose from 'fold','call','raise'.";
                this->bet();
            }
        }

        // check if can end the loop
        largest_bet_of_round = *max_element(std::begin(input_scores), std::end(input_scores));
        for (size_t i = 0; i < players.size(); ++i) {
            if (playerStatus[i] == false)
                totalPass++;
            else if (input_scores[i] == largest_bet_of_round)
                totalPass++;
            else if (input_scores[i] != largest_bet_of_round && input_scores[i] != 0 && scores[i] == 0)
                totalPass++;
        }

        if (totalPass == players.size())
            flag = false;
    }
}

void HoldEmGame::collectAll() {
    size_t numPlayer = players.size();
    // collect cards from each player hand
    for (size_t i = 0; i < numPlayer; ++i) {
        deck.collect(hands[i]);
    }
    // collect cards from board
    deck.collect(board);
}

void HoldEmGame::print(std::ostream& os, const std::size_t rc) {
    size_t numPlayer = players.size();
    // print each player's status
    for (size_t i = 0; i < numPlayer; ++i) {
        os << "player name: " << players[i];
        if (i == dealer) {
            os << "*";
        }
        os << std::endl;
        hands[i].print(os, rc);
    }
}

bool HoldEmGame::askForStop(std::ostream& os, std::istream& is) {
    std::string input;
    // prompt hint message
    os << std::endl
        << ">>> Would you like to end the current game? (yes/*) " << std::endl;
    // read in a string from the standard input stream
    is >> input;
    // return whether input is yes
    return "yes" == input;
}

std::ostream& operator<<(std::ostream& os, const HoldEmHandRank& herank) {
    string label;
    switch (herank) {
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

int HoldEmGame::play() {
    const int STOP = 0;
    const int boardWidth = 5;

    while (true) {
        // shuffle card set state to preflop
        deck.shuffle();

        this->state = HoldEmState::preflop;
        this->pot = 0;

        // deal the card to players
        this->deal();
        // print each player info and hand

        print(cout, handCards);
        this->bet();
        // deal 3 flop cards to board
        this->deal();
        cout << "BOARD (flop): ";
        board.print(cout, boardWidth);

        vector<HoldEmGame::PlayerHand> phs;
        for (size_t i = 0; i < players.size(); ++i) {
            phs.emplace_back(hands[i], i, HoldEmHandRank::undefined);
        }
        for (size_t i = 0; i < phs.size(); ++i) {
            CardSet<HoldEmRank, Suit> tmpcs(board);
            while (!tmpcs.isEmpty()) {
                // * no risk for throwing exception
                tmpcs >> phs[i].cards;
            }
            phs[i].rank = holdem_hand_evaluation(phs[i].cards);
        }
        sort(phs.begin(), phs.end());
        reverse(phs.begin(), phs.end());
        for (auto& [cst, nid, rank] : phs) {
            cout << "Player: " << players[nid] << endl;
            cst.print(cout, boardWidth);
            cout << "Hand rank: " << rank << endl;
        }

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

        if (askForStop(cout, cin)) {
            return STOP;
        }

        dealer = (dealer + 1) % players.size();
    }
}

HoldEmGame::PlayerHand::PlayerHand(CardSet<HoldEmRank, Suit>& cardset, int playername, HoldEmHandRank hhr) : cards(cardset), name(playername), rank(hhr) { }

bool operator<(const HoldEmGame::PlayerHand& lhs, const HoldEmGame::PlayerHand& rhs) {
    // if rank is same, goes into complex logic
    if (lhs.rank == rhs.rank) {
        if (lhs.cards.isEmpty()) {

            return false;
        }
        vector<Card<HoldEmRank, Suit>> CardSet<HoldEmRank, Suit>::* pdata = CardSet<HoldEmRank, Suit>::data();
        // copy of lhs and rhs cardset, can be further used in recursive comparison
        CardSet<HoldEmRank, Suit> lcopy(lhs.cards), rcopy(rhs.cards);
        vector<Card<HoldEmRank, Suit>>& lcs = lcopy.*pdata, & rcs = rcopy.*pdata;
        // to get the cards in rank ascending order
        sort(lcs.begin(), lcs.end(), cardRankIsSmaller<HoldEmRank, Suit>);
        sort(rcs.begin(), rcs.end(), cardRankIsSmaller<HoldEmRank, Suit>);
        // the highest rank of lhs and rhs under further comparison logic
        HoldEmRank lpair = HoldEmRank::undefined, rpair = lpair;
        switch (lhs.rank) {
            // for flush and xhigh, we treat them as same because of we only need to find & compare the largest rank
        case HoldEmHandRank::flush:
        case HoldEmHandRank::xhigh:
            lpair = lcs.back().rank;
            rpair = rcs.back().rank;
            if (lpair == rpair) {
                lcs.pop_back();
                rcs.pop_back();
                HoldEmGame::PlayerHand lsub(lcopy, lhs.name, HoldEmHandRank::xhigh), rsub(rcopy, rhs.name, HoldEmHandRank::xhigh);
                return lsub < rsub;
            }
            break;
            // for pair family, we recursively degrade the comparison if they have same rank
        case HoldEmHandRank::pair:
        case HoldEmHandRank::twopair:
        {
            // index of last element 
            int lix = lcs.size() - 1, rix = rcs.size() - 1;
            // reversely traversal, to find largest rank
            for (; lix > 0;) {
                lpair = lcs[lix--].rank;
                if (lcs[lix].rank == lpair) { break; }
            }
            for (; rix > 0;) {
                rpair = lcs[rix--].rank;
                if (rcs[rix].rank == rpair) { break; }
            }
            if (lpair == rpair) {
                lcs.erase(lcs.begin() + lix, lcs.begin() + lix + LENGTH_OF_PAIR);
                rcs.erase(rcs.begin() + rix, rcs.begin() + rix + LENGTH_OF_PAIR);
                HoldEmHandRank nxtrank = lhs.rank == HoldEmHandRank::twopair ? HoldEmHandRank::pair : HoldEmHandRank::xhigh;
                HoldEmGame::PlayerHand lsub(lcopy, lhs.name, nxtrank), rsub(rcopy, rhs.name, nxtrank);
                return lsub < rsub;
            }
            break;
        }
        case HoldEmHandRank::threeofakind:
        case HoldEmHandRank::fullhouse:
        case HoldEmHandRank::fourofakind:
            for (auto pit = lcs.rbegin(), sit = lcs.rbegin(); sit != lcs.rend(); ++sit) {
                if (sit->rank != lpair) {
                    lpair = sit->rank;
                    pit = sit;
                }
                else {
                    if (pit - sit > LENGTH_OF_PAIR) {
                        break;
                    }
                }
            }
            for (auto pit = rcs.rbegin(), sit = rcs.rbegin(); sit != rcs.rend(); ++sit) {
                if (sit->rank != rpair) {
                    rpair = sit->rank;
                    pit = sit;
                }
                else {
                    if (pit - sit > LENGTH_OF_PAIR) {
                        break;
                    }
                }
            }
            break;
        case HoldEmHandRank::straight:
        case HoldEmHandRank::straightflush:
            lpair = lcs.back().rank;
            rpair = rcs.back().rank;

            if (lpair == HoldEmRank::Ace) {
                lcs.pop_back();
                if (lcs.back().rank != HoldEmRank::King) {
                    lpair = lcs.back().rank;
                }
            }
            if (rpair == HoldEmRank::Ace) {
                rcs.pop_back();
                if (rcs.back().rank != HoldEmRank::King) {
                    rpair = rcs.back().rank;
                }
            }
            break;
        default:
            break;
        }
        return lpair < rpair;
    }
    // otherwise, directly compare the rank
    return lhs.rank < rhs.rank;
}

HoldEmHandRank HoldEmGame::holdem_hand_evaluation(const CardSet<HoldEmRank, Suit>& cs) {

    CardSet<HoldEmRank, Suit> hand(cs);
    vector<Card<HoldEmRank, Suit>> CardSet<HoldEmRank, Suit>::* pdata = CardSet<HoldEmRank, Suit>::data();
    vector<Card<HoldEmRank, Suit>>& cards = hand.*pdata;
    size_t sz = cards.size(), i = 0, cnt = 0;

    if (sz != STD_HAND_NUM) {
        return HoldEmHandRank::undefined;
    }
    // bitmask for better memorize the highest rank we found and to find rank in combined
    int hrmask = 1 << static_cast<int>(HoldEmHandRank::xhigh);
    sort(cards.begin(), cards.end(), cardRankIsSmaller<HoldEmRank, Suit>);
    reverse(cards.begin(), cards.end());
    // current hand's rank, at least xhigh
    HoldEmHandRank hrk = HoldEmHandRank::xhigh;
    vector<int> suitcounts(static_cast<int>(Suit::undefined), 0);
    vector<int> rankcounts(static_cast<int>(HoldEmRank::undefined) + ACE_OFFSET, 0);
    for (Card<HoldEmRank, Suit>& card : cards) {
        suitcounts[static_cast<int>(card.suit)]++;
        rankcounts[static_cast<int>(card.rank) + ACE_OFFSET]++;
        if (card.rank == HoldEmRank::Ace)
            // index 0 stands for ace values as 1
            rankcounts[ACE_LOW]++;
    }
    for (i = 0; i < suitcounts.size(); ++i) {
        if (suitcounts[i] == STD_HAND_NUM) {
            hrmask |= (1 << static_cast<int>(HoldEmHandRank::flush));
        }
    }
    // skip index 0
    for (i = ACE_OFFSET, cnt = 0; i < rankcounts.size(); ++i) {
        if (rankcounts[i]) {
            cnt++;
            if (cnt == STD_HAND_NUM) {
                hrmask |= (1 << static_cast<int>(HoldEmHandRank::straight));
                if (hrmask & (1 << static_cast<int>(HoldEmHandRank::flush))) {
                    hrmask |= (1 << static_cast<int>(HoldEmHandRank::straightflush));
                }
            }
            int num = rankcounts[i];
            switch (num) {
            case LENGTH_OF_FOUR:
                hrmask |= (1 << static_cast<int>(HoldEmHandRank::fourofakind));
                break;
            case LENGTH_OF_THREE:
                hrmask |= (1 << static_cast<int>(HoldEmHandRank::threeofakind));
                if (hrmask & (1 << static_cast<int>(HoldEmHandRank::pair))) {
                    hrmask |= (1 << static_cast<int>(HoldEmHandRank::fullhouse));
                }
                break;
            case LENGTH_OF_PAIR:
                if (hrmask & (1 << static_cast<int>(HoldEmHandRank::pair))) {

                    hrmask |= (1 << static_cast<int>(HoldEmHandRank::twopair));

                }
                hrmask |= (1 << static_cast<int>(HoldEmHandRank::pair));
                if (hrmask & (1 << static_cast<int>(HoldEmHandRank::threeofakind))) {
                    hrmask |= (1 << static_cast<int>(HoldEmHandRank::fullhouse));
                }
                break;
            default:
                break;
            }
        }
        else {
            cnt = 0;
        }
    }
    // from largest rank to smallest, immediately exit if it is found
    for (int rk = static_cast<int>(HoldEmHandRank::straightflush); rk > static_cast<int>(hrk); rk--) {
        if ((1 << rk) & hrmask)
            hrk = static_cast<HoldEmHandRank>(rk);
    }
    return hrk;
}
