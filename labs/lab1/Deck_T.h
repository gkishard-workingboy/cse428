/*
 * @FilePath: /428cpp/labs/lab1/Deck_T.h
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Date: 2022-09-24 21:48:13
 * @LastEditTime: 2022-09-25 13:29:30
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
    Deck();
    // shuffle cards
    void shuffle();

private:
    // non-deterministic
    std::random_device rd;
    // PRNG
    std::mt19937 mtEngine;
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "Deck_T.cpp"
#endif

#endif