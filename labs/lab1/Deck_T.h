/*
 * @FilePath: /428cpp/labs/lab1/Deck_T.h
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Date: 2022-09-24 21:48:13
 * @LastEditTime: 2022-09-25 14:10:50
 * @Description: Declaration of class Deck derived public from CardSet with same template parameterized.
 *
 */

#ifndef _DECK_T_H
#define _DECK_T_H

#include "CardSet_T.h"
#include <algorithm>
#include <random>

template <typename R, typename S>
class Deck : public CardSet<R, S>
{
public:
    // shuffle cards
    void shuffle();
    // collect
    void collect(CardSet<R, S> &);
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "Deck_T.cpp"
#endif

#endif