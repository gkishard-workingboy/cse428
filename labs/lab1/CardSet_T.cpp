/*
 * @FilePath: /428cpp/labs/lab1/CardSet_T.cpp
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Date: 2022-09-24 22:18:12
 * @LastEditTime: 2022-09-25 14:13:12
 * @Description: Source file contains the definition belongs to CardSet_T.h
 *
 */
template <typename R, typename S>
void CardSet<R, S>::print(std::ostream &os, std::size_t col)
{
    // counter for cards in current row
    std::size_t cnt = 0;
    // using itrator to traverse all cards
    for (auto cit = CardSet<R, S>::cards.begin(); cit != CardSet<R, S>::cards.end(); ++cit)
    {
        // print out card along with a whitespace
        os << *cit << " ";
        // when print enough cards in a row, start a new line
        if (++cnt == col)
        {
            cnt = 0;
            os << std::endl;
        }
    }
    // if counter is not 0, which means current row didn't finish but cards run out, it requires new line;
    if (cnt > 0)
    {
        os << std::endl;
    }
}

template <typename R, typename S>
CardSet<R, S> &CardSet<R, S>::operator>>(CardSet<R, S> &rhs)
{
    // throw exception if cards is empty
    if (CardSet<R, S>::cards.empty())
    {
        // ! alert: throw of runtime error
        throw std::runtime_error("Error: the left-hand side CardSet does not have any cards left.");
    }
    // get the reference to the last card of current cards
    auto &card = CardSet<R, S>::cards.back();
    
    try {
        // push onto the back of rhs's cards.
        rhs.cards.push_back(card);
        // pop last card
        CardSet<R, S>::cards.pop_back();
    }
    catch (const std::badalloc& exception) {
        std::cout << "bad allocation failure " << exception.what() << std::endl;
    }
    catch (const std::exception& exception) {
        std::cout << "failed " << exception.what() << std::endl;
    }
    // return reference to this.
    return *this;
}

template <typename R, typename S>
bool CardSet<R, S>::isEmpty()
{
    return CardSet<R, S>::cards.empty();
}