/*
 * @File: Card_T.cpp
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Description: This file includes definition to template items declared in Card_T.h.
 *
 */
template <typename R, typename S>
Card<R, S>::Card(R r, S s) : rank(r), suit(s) {}

template <typename R, typename S>
std::ostream &operator<<(std::ostream &os, const Card<R, S> &c)
{
    os << c.rank << c.suit;
    return os;
}

template <typename R, typename S>
bool cardRankIsSmaller(const Card<R, S> &c1, const Card<R, S> &c2)
{
    if (c1.rank == c2.rank)
    {
        return c1.suit < c2.suit;
    }
    else
    {
        return c1.rank < c2.rank;
    }
}

template <typename R, typename S>
bool cardSuitIsSmaller(const Card<R, S> &c1, const Card<R, S> &c2)
{
    if (c1.suit == c2.suit)
    {
        return c1.rank < c2.rank;
    }
    else
    {
        return c1.suit < c2.suit;
    }
}