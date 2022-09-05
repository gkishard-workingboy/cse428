#ifndef _DECK_H
#define _DECK_H

#include <ostream>

#define COL 8

class Deck{
public:
	virtual void print(std::ostream&) = 0;
};

#endif