LAB2
Team member
Zhikuan Wei(w.zhikuan@wustl.edu)
Haoyuan Ye(haoyuan.y@wustl.edu)
Julia Zeng(julia.z@wustl.edu)

Errors and Warnings:
Errors:


Warnings:


Behavior of Executable Program:

For any misformed command line, the program prints a usage message and terminates. We tested the following misformed command lines:
./lab2.out
./lab2.out hello
./lab2.out Pinochle
./lab2.out Pinochle playerA
./lab2.out HoldEm
./lab2.out HoldEm playerA
./lab2.out HoldEm player1 player2 player3 player4 player5 player6 player7 player8 player9 player10

All of the above commands caused the program to return a non-zero value and print this message:
Usage: ./lab2.out <Game> <Player Names>
Game can be 'Pinochle' or 'HoldEm'.
If the game is Pinochle, there must be 4 player names.
If the game is HoldEm, there must be between 2 and 9 player names.

For well-formed commands, the program plays the game as expected.



Design Decisions:

