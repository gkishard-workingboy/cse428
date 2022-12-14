/*
 * @File: Suit.h
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Description: Declaration of enumeration class Suit and corresponding shift and prefix increment operator.
 *
 */
#ifndef _SUIT_H
#define _SUIT_H

#include <ostream>
#include <string>

enum class Suit
{
    Clubs,
    Diamonds,
    Hearts,
    Spades,
    undefined
};

std::string to_string(const Suit &);
std::ostream &operator<<(std::ostream &, const Suit &);
Suit &operator++(Suit &);

#endif