#include "CardSet_T.h"
#include <iostream>

template<typename R, typename S>
void CardSet<R, S>::print(std::ostream& os, std::size_t st) {
	std::size_t row_size = 0;
	for (auto i : cards) {
		os << i << ' ';
		row_size++;
		if (row_size == st) {
			os << std::endl;
			row_size = 0;
		}
	}
	if (row_size > 0)
		os << std::endl;
}

template<typename R, typename S>
CardSet<R, S>& CardSet<R, S>::operator>>(CardSet<R, S>& cs) {
	if (CardSet<R, S>::isEmpty()) {
		throw std::runtime_error("PinochleGame.cpp lab1.cpp");
	}
	else {
		try {
			cs.cards.push_back(CardSet<R, S>::cards.back());
			CardSet<R, S>::cards.pop_back();
		}
		catch (std::exception& exception) {
			std::cout << "failed" << exception.what() << std::endl;
		}
		return *this;
	}
}

template <typename R, typename S>
bool CardSet<R, S>::isEmpty()
{
	return CardSet<R, S>::cards.empty();
}