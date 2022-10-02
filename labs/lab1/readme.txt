LAB1
Team member
Zhikuan Wei(w.zhikuan@wustl.edu)
Haoyuan Ye(haoyuan.y@wustl.edu)
Julia Zeng(julia.z@wustl.edu)

Errors and Warnings:
Errors:
"invalid conversion from ‘char**’ to ‘const char**’" - This happened when we made the argv parameter of main() a const char**, but the functions that took argv as a parameter still treated argv as a non-const char**. We fixed it by making the argv argument const for every function that used it.

Warnings:


Incorrect Output:


Behavior of Executable Program:

For any misformed command line, the program prints a usage message and terminates. We tested the following misformed command lines:
./lab1.out
./lab1.out hello
./lab1.out Pinochle
./lab1.out Pinochle playerA
./lab1.out HoldEm
./lab1.out HoldEm playerA
./lab1.out HoldEm player1 player2 player3 player4 player5 player6 player7 player8 player9 player10

All of the above commands caused the program to return a non-zero value and print this message:
Usage: ./lab1.out <Game> <Player Names>
Game can be 'Pinochle' or 'HoldEm'.
If the game is Pinochle, there must be 4 player names.
If the game is HoldEm, there must be between 2 and 9 player names.

For well-formed commands, the program plays the game as expected.

For example, the command "./lab1.out Pinochle player1 player2 player3 player4" yields the following output:

player name: player1
9C QH AC JC 9S QD 10H AH 
AS 9C AS AC 
player name: player2
QD 10D 10S AD 10D KD KC JS 
KC 9D QS 9H 
player name: player3
AH AD JD 9D KS 10C JH 9S 
JC QC 10C KH 
player name: player4
9H KD KH JS KS 10S QH 10H 
JH QS QC JD 

>>> Do you wish to stop playing? (yes/*) 

Typing any string other than "yes" (here, I typed "no") results in a new distribution of the cards, such as the one below:

player name: player1
AD 9H 10D 9C JC JS 9D AH 
9D AC KH KC 
player name: player2
AS 9S 10S 9C JS 10C JD KD 
KC 10H QC QC 
player name: player3
QD AS QD QH 10C 10H KH QS 
QH KS QS AC 
player name: player4
KD 10D JH JC JH AH 9S JD 
AD 9H 10S KS 

>>> Do you wish to stop playing? (yes/*) 

On the other hand, responding "yes" ends the game.

Design Decisions:

