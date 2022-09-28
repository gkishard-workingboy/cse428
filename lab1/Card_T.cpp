template<typename R, typename S>
Card<R, S>::Card(R r, S s) :r_(r), s_(s) {
}

template<typename R, typename S>
std::ostream& operator<<(std::ostream& os, const Card<R, S>& c) {
    os << c.r_ << c.s_;
    return os << " ";;
}

