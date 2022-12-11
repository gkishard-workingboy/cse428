/*
 * @FilePath: /428cpp/labs/lab3/HoldEmGame.cpp
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Date: 2022-10-02 19:55:59
 * @LastEditTime: 2022-12-11 01:07:45
 * @Description: Definition to HoldEmGame.h
 *
 */
#include "HoldEmGame.h"
using namespace std;

const int HANDCARD_NUM = 2;
const int LENGTH_OF_PAIR = 2;
const int LENGTH_OF_THREE = 3;
const int LENGTH_OF_FOUR = 4;
const int BEGIN_SCORE = 60;
// standard number of cards in hand for evaluation
const int STD_HAND_NUM = 5;
const int ACE_OFFSET = 1;
const int ACE_LOW = 0;
const int minimum_value_bet_before_turn = 2;
const int minimum_value_bet_after_turn = 4;
const int big_blind_default_bet_value = 2;
const int small_blind_default_bet_value = 1;


HoldEmGame::HoldEmGame(int argc, const char* argv[]) : Game(argc, argv), state(HoldEmState::preflop), combinations() {
    // create as many hands as players in the game
    for (int i = Game::firstPlayerIndex; i < argc; ++i) {
        // will call default constructor of CardSet
        hands.emplace_back();
        this->input_scores.push_back(0);
        this->playerStatus.push_back(true);
    }
    // new game, new scores
    fill(scores.begin(), scores.end(), BEGIN_SCORE);
    combinations.push_back({ 0 });
    for (int i = 0; i < HANDCARD_NUM; ++i) {
        vector<int>& prev = combinations[i], tmp;
        for (int prevCombo : prev) {
            for (int j = i + STD_HAND_NUM - 1; ((1 << j) & prevCombo) == 0 && j >= 0; --j) {
                tmp.push_back((1 << j) | prevCombo);
            }
        }
        combinations.push_back(tmp);
    }
}

void HoldEmGame::deal() {
    const int flopCards = LENGTH_OF_THREE;

    if (this->state == HoldEmState::preflop) {
        // repeatedly shift a card to each hand of players, starting with the player right after the dealer and ending with the dealer.
        for (size_t i = 0; i < HANDCARD_NUM; i++) {
            for (size_t j = 1; j <= players.size() && !deck.isEmpty(); j++) {
                deck >> hands[(dealer + j) % players.size()];
            }
        }
        this->state = HoldEmState::flop;
        // after each player has been dealt 2 cards, the pot should be set to 0 
        this->pot = 0;
    } else if (this->state == HoldEmState::flop) {
        for (size_t i = 0; i < flopCards; i++) {
            deck >> board;
        }
        this->state = HoldEmState::turn;
    } else if (this->state == HoldEmState::turn) {
        deck >> board;
        this->state = HoldEmState::river;
    } else if (this->state == HoldEmState::river) {
        deck >> board;
        this->state = HoldEmState::undefined;
    }
    // do nothing for other states
}

vector<HoldEmAction> HoldEmGame::action_before_turn(const CardSet<HoldEmRank, Suit>& cs) {
    //setup moves preflop
    CardSet<HoldEmRank, Suit> hand(cs);
    vector<Card<HoldEmRank, Suit>> CardSet<HoldEmRank, Suit>::* pdata = CardSet<HoldEmRank, Suit>::data();
    vector<Card<HoldEmRank, Suit>>& cards = hand.*pdata;
    if (cards[0].rank == cards[1].rank && cards[0].rank == HoldEmRank::Ace) {
        vector<HoldEmAction> result{ HoldEmAction::raise,HoldEmAction::raise };
        return result;
    } else if (cards[0].rank == cards[1].rank && ((cards[0].rank == HoldEmRank::King) || (cards[0].rank == HoldEmRank::Queen) || (cards[0].rank == HoldEmRank::Jack))) {
        vector<HoldEmAction> result{ HoldEmAction::raise,HoldEmAction::call };
        return result;
    } else if (cards[0].suit == cards[1].suit) {
        vector<HoldEmAction> result{ HoldEmAction::call,HoldEmAction::call };
        return result;
    } else if (((static_cast<int>(cards[0].rank) == static_cast<int>(cards[1].rank) + 1) && (cards[1].rank > HoldEmRank::Three)) || ((static_cast<int>(cards[1].rank) == static_cast<int>(cards[0].rank) + 1) && (cards[0].rank > HoldEmRank::Three))) {
        vector<HoldEmAction> result{ HoldEmAction::call,HoldEmAction::call };
        return result;
    } else if (cards[0].rank == cards[1].rank) {
        vector<HoldEmAction> result{ HoldEmAction::call,HoldEmAction::call };
        return result;
    } else {
        vector<HoldEmAction> result{ HoldEmAction::fold,HoldEmAction::fold };
        return result;
    }
}


vector<HoldEmAction> HoldEmGame::action_after_turn(const HoldEmGame::PlayerHand& playerHands) {
    //setup moves after flop
    if (this->state == HoldEmState::turn) {
        if (static_cast<int>(playerHands.rank) >= static_cast<int>(HoldEmHandRank::threeofakind)) {
            vector<HoldEmAction> result{ HoldEmAction::raise,HoldEmAction::raise };
            return result;
        } else if (playerHands.rank == HoldEmHandRank::twopair) {
            vector<HoldEmAction> result{ HoldEmAction::raise,HoldEmAction::call };
            return result;
        } else if (playerHands.rank == HoldEmHandRank::pair) {   //four consecutive cards WIP
            vector<HoldEmAction> result{ HoldEmAction::call,HoldEmAction::call };
            return result;
        } else {
            vector<HoldEmAction> result{ HoldEmAction::call,HoldEmAction::fold };
            return result;
        }
    } else if (this->state == HoldEmState::river) {           //setup moves after turn
        if (static_cast<int>(playerHands.rank) >= static_cast<int>(HoldEmHandRank::straight)) {
            vector<HoldEmAction> result{ HoldEmAction::raise,HoldEmAction::raise };
            return result;
        } else if (playerHands.rank == HoldEmHandRank::threeofakind) {
            vector<HoldEmAction> result{ HoldEmAction::raise,HoldEmAction::call };
            return result;
        } else if (playerHands.rank == HoldEmHandRank::twopair || playerHands.rank == HoldEmHandRank::pair) {   //four consecutive cards WIP
            vector<HoldEmAction> result{ HoldEmAction::call,HoldEmAction::call };
            return result;
        } else {
            vector<HoldEmAction> result{ HoldEmAction::call,HoldEmAction::fold };
            return result;
        }
    } else {                      //setup moves after river
        if (static_cast<int>(playerHands.rank) >= static_cast<int>(HoldEmHandRank::straight)) {
            vector<HoldEmAction> result{ HoldEmAction::raise,HoldEmAction::raise };
            return result;
        } else if (playerHands.rank == HoldEmHandRank::threeofakind) {
            vector<HoldEmAction> result{ HoldEmAction::raise,HoldEmAction::call };
            return result;
        } else if (playerHands.rank == HoldEmHandRank::twopair) {
            vector<HoldEmAction> result{ HoldEmAction::call,HoldEmAction::call };
            return result;
        } else {
            vector<HoldEmAction> result{ HoldEmAction::call,HoldEmAction::fold };
            return result;
        }
    }
}

bool HoldEmGame::bet() {
    cout << " pot starts with " << pot << " chips" << endl;
    unsigned int min_raise_value;
    // clear the scores player chipped in this betting round.
    std::fill(input_scores.begin(), input_scores.end(), 0);

    if (this->state == HoldEmState::flop || this->state == HoldEmState::turn) {
        min_raise_value = minimum_value_bet_before_turn;
    } else {
        min_raise_value = minimum_value_bet_after_turn;
    }
    unsigned int foldCount = 0;
    // bool isRoundOver = false;
    bool raiseFlag = false;
    unsigned int largest_bet = 0; // largest value for call/raise check max value

    size_t k = 0;
    if (this->state == HoldEmState::flop) {  // if its preflop, we want UTG go first
        lastRaisedPlayer = (dealer + big_blind_default_bet_value) % players.size();
        size_t small_blind = (small_blind_default_bet_value + dealer) % players.size();
        size_t big_blind = (big_blind_default_bet_value + dealer) % players.size();
        scores[small_blind] -= small_blind_default_bet_value;
        scores[big_blind] -= big_blind_default_bet_value;
        input_scores[small_blind] += small_blind_default_bet_value;
        input_scores[big_blind] += big_blind_default_bet_value;
        pot = small_blind_default_bet_value + big_blind_default_bet_value;
        largest_bet = big_blind_default_bet_value;
        k++;
    }
    unsigned int startPlayer = lastRaisedPlayer;

    for (; ; ++k) {
        size_t i = (startPlayer + k) % players.size();
        if (k != 0 && i == lastRaisedPlayer) break;
        if (!playerStatus[i] || scores[i] == 0) //will pass if conditions satisfy
            continue;

        cout << "Player " << players[i] << " has " << scores[i] << " chips" << endl;

        //part 15, get specific move based on hands
        vector<HoldEmAction> handAction;
        if (this->state == HoldEmState::flop) {
            handAction = action_before_turn(hands[i]);
        } else {
            handAction = action_after_turn(phs[i]);
        }

        //make move based on whether sb already raised
        HoldEmAction playerAction;
        if (raiseFlag == false) {
            playerAction = handAction[0];
        } else {
            playerAction = handAction[1];
        }

        //make action to fold
        if (playerAction == HoldEmAction::fold) {
            foldCount++;
            playerStatus[i] = false;
            cout << "Player " << players[i] << " folds " << endl;
            //check if all other players fold the card already.
            if (foldCount == (players.size() - 1)) {  //if all other than 1 player folded, end the game.                    
                for (size_t j = 0; j < players.size(); ++j) {
                    if (playerStatus[j] == true) {
                        scores[j] += pot;
                        cout << "player " << players[j] << " wins with " << pot << " chips" << endl;
                    }
                }
                return true;
            }
        } else if (playerAction == HoldEmAction::call) {    //make action to call
            if (input_scores[i] < largest_bet) {
                unsigned int needed = largest_bet - input_scores[i];
                if (scores[i] <= needed) {
                    pot += scores[i];
                    input_scores[i] = scores[i];
                    scores[i] = 0;
                } else {
                    pot += needed;
                    input_scores[i] += needed;
                    scores[i] -= needed;
                }
                cout << "Player " << players[i] << " calls" << endl;
            } else {
                cout << "Player " << players[i] << " checks" << endl;
            }

        } else if (playerAction == HoldEmAction::raise) {         //make action to raise
            raiseFlag = true;
            unsigned int betInput = largest_bet + min_raise_value - input_scores[i];
            if (scores[i] <= betInput) {
                cout << "Player " << players[i] << " opts to ALL-IN" << endl;
                pot += scores[i];
                input_scores[i] = scores[i];
                largest_bet = max(largest_bet, scores[i]);
                scores[i] = 0;
            } else {
                scores[i] -= betInput;
                pot = pot + betInput;
                input_scores[i] += betInput;
                largest_bet = input_scores[i];
                lastRaisedPlayer = i;
                cout << "Player " << players[i] << " bets " << betInput << endl;
            }
        }
        cout << "Player " << players[i] << " leaves " << scores[i] << " chips " << endl;
    }
    //check if all other players fold the card already.
    if (foldCount == (players.size() - 1)) {  //if all other than 1 player folded, end the game.                    
        for (size_t j = 0; j < players.size(); ++j) {
            if (playerStatus[j] == true) {
                scores[j] += pot;
                cout << "player " << players[j] << " win this pot with " << pot << " scores" << endl;
            }
        }
        return true;
    }

    return false;
}

void HoldEmGame::resetAllPlayerStatus() {
    fill(playerStatus.begin(), playerStatus.end(), true);
    fill(input_scores.begin(), input_scores.end(), 0);
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
        if (playerStatus[i] == true) {
            os << "player name: " << players[i];
            if (i == dealer) {
                os << "*";
            }
            os << std::endl;
            hands[i].print(os, rc);
        }
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

void HoldEmGame::evalCombinations(CardSet<HoldEmRank, Suit>& handCards, CardSet<HoldEmRank, Suit> boardCards, HoldEmGame::PlayerHand& playerHand) {
    if (!playerStatus[playerHand.name]) return;
    // combinations vector
    CardSet<HoldEmRank, Suit> cset;
    auto pdata = CardSet<HoldEmRank, Suit>::data();
    std::vector<Card<HoldEmRank, Suit>>& boardVec = boardCards.*pdata;
    std::vector<Card<HoldEmRank, Suit>>& handVec = handCards.*pdata;
    int totalCards = boardVec.size() + HANDCARD_NUM;
    // number of cards that need to be removed in each combination.
    int missed = totalCards - STD_HAND_NUM;
    // always keep last card in combination.
    boardCards >> cset;
    // put all rest cards into a vector
    std::vector<Card<HoldEmRank, Suit>> restCards = boardVec;
    restCards.insert(restCards.end(), handVec.begin(), handVec.end());
    vector<int>& combos = combinations[missed];
    // evaluate every possible combinations.
    for (int combo : combos) {
        HoldEmGame::PlayerHand tmpPH(cset, playerHand.name, HoldEmHandRank::undefined);
        std::vector<Card<HoldEmRank, Suit>>& phVec = tmpPH.cards.*pdata;
        for (size_t i = 0; i < restCards.size(); ++i) {
            if (combo & (1 << i)) continue;
            phVec.push_back(restCards[i]);
        }
        tmpPH.rank = holdem_hand_evaluation(tmpPH.cards);
        if (playerHand < tmpPH) {
            playerHand = tmpPH;
        }
    }
}

void HoldEmGame::printPlayerHand(std::ostream& os, std::vector<HoldEmGame::PlayerHand>& playerHands) {
    const int boardWidth = 5;
    sort(playerHands.begin(), playerHands.end());
    reverse(playerHands.begin(), playerHands.end());
    for (auto& [cst, nid, rank] : playerHands) {
        if (playerStatus[nid]) {
            os << "Player: " << players[nid] << endl;
            cst.print(cout, boardWidth);
            os << "Hand rank: " << rank << endl;
        }
    }
}

void HoldEmGame::settleRound(std::vector<HoldEmGame::PlayerHand>& allPlayerHands) {
    using PH = HoldEmGame::PlayerHand;
    PH& bestHand = allPlayerHands.front();
    // number of equal valued hand players
    size_t eqNum = 1;
    for (; eqNum < allPlayerHands.size(); ++eqNum) {
        // if next player's hand is same as the best, keep looping
        if (bestHand == allPlayerHands[eqNum]) continue;
        // otherwise break the loop
        break;
    }
    int remainder = pot % eqNum;
    int won = pot / eqNum;
    int earliestIndex = static_cast<int>(2 * dealer), minDist = static_cast<int>(2 * dealer);
    if (remainder > 0) {
        // if we have a remainder under such pot, the remainder should go to the player in an earlier dealing place. And the way to judge is through comparing of the index of that player in accordance with the dealer's position.
        for (size_t i = 0; i < eqNum; ++i) {
            int ci = allPlayerHands[i].name;
            int dis = ci < static_cast<int>(dealer) ? players.size() - dealer + ci : ci - dealer;
            if (minDist > dis) {
                minDist = dis;
                earliestIndex = ci;
            }
        }
    }

    for (size_t i = 0; i < eqNum; ++i) {
        int ci = allPlayerHands[i].name;
        int totalEarned = won + (earliestIndex == ci ? remainder : 0);
        cout << "Player " << players[ci] << " won " << totalEarned << " chips" << endl;
        scores[ci] += totalEarned;
    }
    // reset pot to zero
    pot = 0;

    vector<unsigned int> newScores;
    vector<string> newPlayers;
    // clear any losers
    for (size_t i = 0; i < players.size(); ++i) {
        // lose all their scores (probably money:()
        if (scores[i] == 0) {
            cout << "Player " << players[i] << " loses all his chips, and he is rank at " << players.size() << " place" << endl;
            playerRank.push_back(players[i]);
            // need to update the value of dealer, since someone before him lose his place.
            if (i <= dealer) dealer--;
        } else {
            newScores.push_back(scores[i]);
            newPlayers.push_back(players[i]);
        }
    }
    players = std::move(newPlayers);
    scores = std::move(newScores);
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

    bool isGameEnd = false;
    bool foldRound = true;

    while (!isGameEnd) {
        // reset foldRound
        foldRound = true;

        // shuffle card set state to preflop
        deck.shuffle();
        // reset in-game player's status
        resetAllPlayerStatus();
        state = HoldEmState::preflop;

        // deal cards to players
        deal();

        // init all player's hand
        phs.clear();
        for (size_t i = 0; i < players.size(); ++i) {
            phs.emplace_back(hands[i], i, HoldEmHandRank::undefined);
        }

        // print each player info and hand
        print(cout, HANDCARD_NUM);

        if (!bet()) {

            // deal 3 flop cards to board
            deal();

            cout << "BOARD (flop): ";
            board.print(cout, boardWidth);


            for (size_t i = 0; i < phs.size(); ++i) {
                // copy constructor, would not affect board.
                CardSet<HoldEmRank, Suit> tmpcs(board);
                while (!tmpcs.isEmpty()) {
                    // * no risk for throwing exception
                    tmpcs >> phs[i].cards;
                }
                phs[i].rank = holdem_hand_evaluation(phs[i].cards);
            }
            printPlayerHand(cout, phs);

            if (!bet()) {

                // deal turn cards to board
                deal();

                cout << "BOARD (turn): ";
                board.print(cout, boardWidth);

                for (size_t i = 0; i < phs.size(); ++i) {
                    evalCombinations(hands[phs[i].name], board, phs[i]);
                }
                printPlayerHand(cout, phs);
                if (!bet()) {

                    // deal river cards to board
                    deal();
                    cout << "BOARD (river): ";
                    board.print(cout, boardWidth);

                    for (size_t i = 0; i < phs.size(); ++i) {
                        evalCombinations(hands[phs[i].name], board, phs[i]);
                    }
                    printPlayerHand(cout, phs);
                    if (!bet()) foldRound = false;
                }
            }
        }
        // collect hands and board
        collectAll();
        if (!foldRound)
            settleRound(phs);

        if (askForStop(cout, cin)) {
            return STOP;
        }

        // if only one player left after this round, the winner comes out and game ends.
        if (players.size() == 1) {
            cout << "The winner is " << players.front() << endl;
            cout << "His final count is " << scores.front() << endl;
            isGameEnd = true;
        }
        dealer = (dealer + 1) % players.size();
    }
    return STOP;
}

HoldEmGame::PlayerHand::PlayerHand(CardSet<HoldEmRank, Suit>& cardset, int playername, HoldEmHandRank hhr) : cards(cardset), name(playername), rank(hhr) { }

HoldEmGame::PlayerHand& HoldEmGame::PlayerHand::operator=(const HoldEmGame::PlayerHand& rhs) {
    this->name = rhs.name;
    this->rank = rhs.rank;
    this->cards = rhs.cards;
    return *this;
}

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
                    } else {
                        if (pit - sit > LENGTH_OF_PAIR) {
                            break;
                        }
                    }
                }
                for (auto pit = rcs.rbegin(), sit = rcs.rbegin(); sit != rcs.rend(); ++sit) {
                    if (sit->rank != rpair) {
                        rpair = sit->rank;
                        pit = sit;
                    } else {
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
        } else {
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

bool operator==(const HoldEmGame::PlayerHand& lhs, const HoldEmGame::PlayerHand& rhs) {
    return !(lhs < rhs) && !(rhs < lhs);
}