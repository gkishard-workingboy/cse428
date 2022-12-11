/*
 * @FilePath: /428cpp/labs/lab3/Deck_T.cpp
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Date: 2022-09-25 11:12:00
 * @LastEditTime: 2022-12-11 00:48:58
 * @Description: Defition of Deck_T.h
 *
 */

template <typename R, typename S>
void Deck<R, S>::shuffle() {
    // uniformly reorder the cards
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(CardSet<R, S>::cards.begin(), CardSet<R, S>::cards.end(), g);
}

template <typename R, typename S>
void Deck<R, S>::collect(CardSet<R, S>& cardset) {
    // check cardset is not empty
    while (!cardset.isEmpty()) {
        // push last card from cardset to current object
        // * no risk for throwing exception
        cardset >> *this;
    }
}