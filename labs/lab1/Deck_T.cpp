/*
 * @FilePath: /428cpp/labs/lab1/Deck_T.cpp
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Date: 2022-09-25 11:12:00
 * @LastEditTime: 2022-09-25 13:25:42
 * @Description: Defition of Deck_T.h
 *
 */
template <typename R, typename S>
Deck<R, S>::Deck() : rd(), mtEngine(rd()){};

template <typename R, typename S>
void Deck<R, S>::shuffle()
{
    // uniformly reorder the cards
    std::shuffle(CardSet<R, S>::cards.begin(), CardSet<R, S>::cards.end(), Deck<R, S>::mtEngine);
}