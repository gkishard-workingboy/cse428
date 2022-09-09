/*
 * @File: Card_T.cpp
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Description: This file includes definition to template items declared in Card_T.h.
 *
 */
template <typename R, typename S>
Card<R, S>::Card(R r, S s)
{
    this->rank = r;
    this->suit = s;
}

template <typename R, typename S>
std::ostream &operator<<(std::ostream &os, const Card<R, S> &c)
{
    os << c.rank << c.suit;
    return os;
}