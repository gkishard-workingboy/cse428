/*
 * @FilePath: /428cpp/labs/lab1/Deck_T.cpp
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Date: 2022-09-25 11:12:00
 * @LastEditTime: 2022-09-25 16:03:41
 * @Description: Defition of Deck_T.h
 *
 */
// initialize mt engine by random value get from random_device
template <typename R, typename S>
Deck<R, S>::Deck() : rd(), mtEngine(rd()){};

template <typename R, typename S>
void Deck<R, S>::shuffle()
{
    // uniformly reorder the cards
    std::shuffle(CardSet<R, S>::cards.begin(), CardSet<R, S>::cards.end(), Deck<R, S>::mtEngine);
}

template <typename R, typename S>
void Deck<R, S>::collect(CardSet<R, S> &cardset)
{
    // check cardset is not empty
    while (!cardset.isEmpty())
    {
        // push last card from cardset to current object
        // * no risk for throwing exception
        cardset >> *this;
    }
}