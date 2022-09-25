/*
 * @FilePath: /428cpp/labs/lab1/CardSet_T.h
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Date: 2022-09-24 22:18:03
 * @LastEditTime: 2022-09-25 13:47:31
 * @Description:
 *
 */

#ifndef _CardSet_T_H
#define _CardSet_T_H
#include "Card_T.h"
#include <vector>
#include <ostream>
#include <stdexcept>

// Base class for Deck
template <typename R, typename S>
class CardSet
{
public:
    // prints out all cards and specified number of cards in a row to given out stream;
    void print(std::ostream &, std::size_t);
    // Is there any cards left in current cardset?
    bool isEmpty();
    // right shift operator to push last card to another cardset
    CardSet<R, S> &operator>>(CardSet<R, S> &);

protected:
    // vector that store all cards.
    std::vector<Card<R, S>> cards;
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "CardSet_T.cpp"
#endif

#endif