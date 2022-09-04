#include <ostream>

template<typename R, typename S>
class Card {
public:
	R rank;
	S suit;
	Card(R, S);
};

template<typename R, typename S>
std::ostream& operator<<(std::ostream&, const Card<R,S>&);