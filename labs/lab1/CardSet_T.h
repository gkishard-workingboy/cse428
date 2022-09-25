/*
 * @FilePath: /428cpp/labs/lab1/CardSet_T.h
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Date: 2022-09-24 22:18:03
 * @LastEditTime: 2022-09-24 23:13:28
 * @Description:
 *
 */

#ifndef _CardSet_T_H
#define _CardSet_T_H
#include "Card_T.h"
#include <vector>
#include <ostream>

// Base class for Deck
template <typename R, typename S>
class CardSet
{
public:
    // prints out all cards and specified number of cards in a row to given out stream;
    void print(std::ostream &, std::size_t);

protected:
    // vector that store all cards.
    std::vector<Card<R, S>> cards;
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "CardSet_T.cpp"
#endif

#endif