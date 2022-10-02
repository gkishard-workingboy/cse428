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



Design Decisions:

