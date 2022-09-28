template<typename R, typename S>
void Deck<R, S>::shuffle() {
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(CardSet<R, S>::cards.begin(), CardSet<R, S>::cards.end(), g);
}

template<typename R, typename S>
void Deck<R, S>::collect(CardSet<R, S> & cs) {
	while (!cs.isEmpty()) {
		cs >> *this;
	}
}

