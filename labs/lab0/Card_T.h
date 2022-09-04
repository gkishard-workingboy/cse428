#include <ostream>

template<typename R, typename S>
class Playcard {
public:
	R rank;
	S suit;
	Playcard(R, S);
};

template<typename R, typename S>
std::ostream& operator<<(std::ostream&, const Playcard<R,S>&);