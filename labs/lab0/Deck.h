/*
 * @File: Deck.h
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Description: Declaration of class Deck with a pure virtual method called print should be implemented in subclass. Also declare the macro COl for specifying the maximum number of items will be printed per row.
 *
 */
#ifndef _DECK_H
#define _DECK_H

#include <ostream>

#define COL 8

class Deck
{
public:
	virtual void print(std::ostream &) = 0;
};

#endif