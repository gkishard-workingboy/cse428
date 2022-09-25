/*
 * @FilePath: /428cpp/labs/lab1/CardSet_T.cpp
 * @Author: Zhikuan Wei w.zhikuan@wustl.edu
 * @Date: 2022-09-24 22:18:12
 * @LastEditTime: 2022-09-25 11:11:29
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