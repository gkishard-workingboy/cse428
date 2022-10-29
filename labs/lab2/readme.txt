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

For example, "./lab2.out HoldEm p1 p2 p3" yields the following output:

player name: p1
AH 2S 
player name: p2
5H 10S 
player name: p3
KC 5C 
BOARD (flop): 6S 8S 7D 
Player: p1
AH 2S 7D 8S 6S 
Hand rank: xhigh
Player: p3
KC 5C 7D 8S 6S 
Hand rank: xhigh
Player: p2
5H 10S 7D 8S 6S 
Hand rank: xhigh
BOARD (turn): 6S 8S 7D 3H 
BOARD (river): 6S 8S 7D 3H 6D 

>>> Would you like to end the current game? (yes/*)

Typing "yes" here will end the game, but typing anything else will generate a new distribution of cards. We re-generated the cards several times. Each time the cards were generated, the players' hands are initially listed in the order that the user specified in the command. Each player is dealt 2 cards. Then, the program prints the board, which has 3 cards. The cards on the board are dealt to each player. The players' hands are displayed again after the flop. For each hand, the program lists the cards in order, starting with the player's original 2 cards followed by the 3 cards dealt from the board. This time, the players are listed in descending order based on rank.

Here a few examples from the outputs we got:

In the output below, p1's rank is correctly identified as threeofakind. The rank of p2 and p3 is pair, which is expected since they both have 2 cards of rank 7. After the flop, p1 is displayed first since threeofakind is a higher rank than pair. p2 is displayed before p3. This is expected since p2 is higher ranked than p3. While p2 and p3 both have a pair of 7's, p2's highest ranked non-paired card is KS, which is higher than p3's highest non-paired card, 9C. 

player name: p1
QS 7D 
player name: p2
9S KS 
player name: p3
9C 5S 
BOARD (flop): 3H 7H 7C 
Player: p1
QS 7D 7C 7H 3H 
Hand rank: threeofakind
Player: p2
9S KS 7C 7H 3H 
Hand rank: pair
Player: p3
9C 5S 7C 7H 3H 
Hand rank: pair
BOARD (turn): 3H 7H 7C 2C 
BOARD (river): 3H 7H 7C 2C 5D 

>>> Would you like to end the current game? (yes/*) 

In the next example, p2 and p3 are correctly identified to have a pair rank. p2 has a pair of Q's, and p3 has a pair of 3's. After the flop, p2 is displayed before p3 since its paired card is higher ranked than p3's paired card. p1 is displayed last since their hand has the lowest rank.

player name: p1
AS 9D 
player name: p2
QD QC 
player name: p3
5C 3C 
BOARD (flop): 3H JD 6C 
Player: p2
QD QC 6C JD 3H 
Hand rank: pair
Player: p3
5C 3C 6C JD 3H 
Hand rank: pair
Player: p1
AS 9D 6C JD 3H 
Hand rank: xhigh
BOARD (turn): 3H JD 6C 5H 
BOARD (river): 3H JD 6C 5H 4S 

>>> Would you like to end the current game? (yes/*) 

Here's another example. p1 is correctly identified to have two pairs, a pair of 10's and a pair of J's. p1 is displayed first after the flop since their hand has the highest rank. p3 is displayed second and p2 is displayed last because p3's highest ranked card is higher than p2's highest ranked card.

player name: p1
JD 10S 
player name: p2
3D 9H 
player name: p3
QD 4D 
BOARD (flop): JS 10C 7H 
Player: p1
JD 10S 7H 10C JS 
Hand rank: twopair
Player: p3
QD 4D 7H 10C JS 
Hand rank: xhigh
Player: p2
3D 9H 7H 10C JS 
Hand rank: xhigh
BOARD (turn): JS 10C 7H 5H 
BOARD (river): JS 10C 7H 5H JH 

>>> Would you like to end the current game? (yes/*) 
