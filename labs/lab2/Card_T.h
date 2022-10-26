/*
 * @File: Card_T.h
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Description: Declaration of template struct Card with corresponding template shift operator. This file includes the cpp file containing definition to items above.
 *
 */
#ifndef _CARD_T_H
#define _CARD_T_H

#include <ostream>

template <typename R, typename S>
struct Card
{
public:
	R rank;
	S suit;
	Card(R, S);
};

template <typename R, typename S>
std::ostream &operator<<(std::ostream &, const Card<R, S> &);

template <typename R, typename S>
bool cardRankIsSmaller(const Card<R, S> &, const Card<R, S> &);

template <typename R, typename S>
bool cardSuitIsSmaller(const Card<R, S> &, const Card<R, S> &);

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE /* test whether guard symbol is defined */
#include "Card_T.cpp"
#endif

#endif