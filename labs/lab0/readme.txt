LAB0
Team member
Zhikuan Wei(w.zhikuan@wustl.edu)
Haoyuan Ye
Julia Zeng(julia.z@wustl.edu)

Errors and Warnings:
Errors:
1. Linker errors, exit -1: cannot find definition of template functions.
2. Wrongly type the HoldEmRank with HoldEmDeck.
3. Redefine of several header file.

Warnings:
1. compare between int and size_t
2. missing break in switch could result in falling through

Incorrect Output:
No outputs at all. And after carefully gdb debugging process(actually painstaking), 
the problem lies in the prefix overload operator ++ of HoldEmRank which the Jack will
remain as Jack, then the for loop inside HoldEmDeck constructor never get stop.

Behavior of Executable Program:
Running "./lab0.out" generated the following output:
Pinochle Deck: 
9C 9C 9D 9D 9H 9H 9S 9S 
JC JC JD JD JH JH JS JS 
QC QC QD QD QH QH QS QS 
KC KC KD KD KH KH KS KS 
10C 10C 10D 10D 10H 10H 10S 10S 
AC AC AD AD AH AH AS AS 
Texas hold'em Deck: 
2C 2D 2H 2S 3C 3D 3H 3S 
4C 4D 4H 4S 5C 5D 5H 5S 
6C 6D 6H 6S 7C 7D 7H 7S 
8C 8D 8H 8S 9C 9D 9H 9S 
10C 10D 10H 10S JC JD JH JS 
QC QD QH QS KC KD KH KS 
AC AD AH AS 

Design Decisions:

In the PinochleDeck constructor, we pushed cards to the card vector using nested loops. The inner loop incremented the suit and the outer loop incremented the rank. This way, cards with the same rank will be grouped together. In the print() function for this class, we added a line break after every 8 cards so that cards of the same rank will be printed on the same line. The number of cards will be printed per row is controlled by the macro "COL" defined in Deck.h, where we think that since all subclass will include this file and is easy to control the behavior of all inherited print() function.
