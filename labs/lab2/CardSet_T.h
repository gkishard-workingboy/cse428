/*
 * @FilePath: /428cpp/labs/lab2/CardSet_T.h
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Date: 2022-09-24 22:18:03
 * @LastEditTime: 2022-10-25 16:49:08
 * @Description:
 *
 */

#ifndef _CardSet_T_H
#define _CardSet_T_H
#include "Card_T.h"
#include <vector>
#include <iostream>
#include <stdexcept>
#include <new>
#include <algorithm>
#include <iterator>

 // Base class for Deck
template <typename R, typename S>
class CardSet {
protected:
    // vector that store all cards.
    std::vector<Card<R, S>> cards;

public:
    // constructor
    CardSet() = default;
    // copy constructor
    CardSet(const CardSet<R, S>&);
    // prints out all cards and specified number of cards in a row to given out stream;
    void print(std::ostream&, std::size_t);
    // Is there any cards left in current cardset?
    bool isEmpty() const;
    // right shift operator to push last card to another cardset
    CardSet<R, S>& operator>>(CardSet<R, S>&);
    // static function that returns a pointer to the class' protected vector data member
    static std::vector<Card<R, S>> CardSet::* data();
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "CardSet_T.cpp"
#endif

#endif