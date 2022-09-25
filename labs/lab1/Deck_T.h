/*
 * @FilePath: /428cpp/labs/lab1/Deck _T.h
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Date: 2022-09-24 21:48:13
 * @LastEditTime: 2022-09-24 22:56:08
 * @Description: Declaration of class Deck derived public from CardSet with same template parameterized.
 *
 */

#ifndef _DECK_T_H
#define _DECK_T_H

#include "CardSet_T.h"

template <typename R, typename S>
class Deck : public CardSet<R, S>
{
};

#endif