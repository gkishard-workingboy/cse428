#include <ostream>

#define COL 8

class Deck{
public:
	virtual void print(std::ostream&) = 0;
};