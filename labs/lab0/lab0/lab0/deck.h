#pragma once
#include "card.h"

class cardDeck{
public:
	virtual void print(std::ostream& os) = 0;
};