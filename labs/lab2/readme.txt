LAB2
Team member
Zhikuan Wei(w.zhikuan@wustl.edu)
Haoyuan Ye(haoyuan.y@wustl.edu)
Julia Zeng(julia.z@wustl.edu)

Errors and Warnings:
Errors:
1. multiple types in one declaration  };
Missing close brace after declaration of enumeration class.

2. error: ‘template<class R, class S> class CardSet’ used without template parameters
Missing parameters for using that template as a type.

3. error: expected unqualified-id before ‘*’ token
Missing same qualifier as we declared for that member data pointer.

4. error: no matching function for call to ‘std::vector<Card<HoldEmRank, Suit>, std::allocator<Card<HoldEmRank, Suit> > >::erase(std::reverse_iterator<__gnu_cxx::__normal_iterator<Card<HoldEmRank, Suit>*, std::vector<Card<HoldEmRank, Suit>, std::allocator<Card<HoldEmRank, Suit> > > > >, std::reverse_iterator<__gnu_cxx::__normal_iterator<Card<HoldEmRank, Suit>*, std::vector<Card<HoldEmRank, Suit>, std::allocator<Card<HoldEmRank, Suit> > > > >&)’
Find out that the reverse_iterator cannot be taken as parameter for vector::erase().

5. error: jump to case label [-fpermissive]
             case HoldEmHandRank::threeofakind:
The problem is that variables declared in one case are still visible in the subsequent cases unless an explicit { } block is used, but they will not be initialized because the initialization code belongs to another case.
Credit link: https://stackoverflow.com/questions/5685471/error-jump-to-case-label-in-switch-statement

Warnings:
We meet tons of warnings, but all of them just appear as the accompany of errors, so once we fixed the error, the warning just not bother us anymore. 

Behavior of Executable Program:

For any misformed command line, the program prints a usage message and terminates. We tested the following misformed command lines:
./lab2.out
./lab2.out hello
./lab2.out Pinochle
./lab2.out Pinochle playerA
./lab2.out HoldEm
./lab2.out HoldEm playerA
./lab2.out HoldEm player1 player2 player3 player4 player5 player6 player7 player8 player9 player10

All of the above commands caused the program to return a non-zero value.
If the game name is missing or isn't Pinochle or HoldEm, the following message appears:
Usage: ./lab2.out <Game> <Player Names>
Game can be 'Pinochle' or 'HoldEm'.
If the game is Pinochle, there must be 4 player names.
If the game is HoldEm, there must be between 2 and 9 player names.

If the game was specified as Pinochle but there is an incorrect number of player names, the same message above is displayed without the fourth line. If the game was HoldEm and there are too many or too few player names, this message is displayed without the third line.

For well-formed commands, the program plays the game as expected.

For example, "./lab2.out Pinochle p1 p2 p3 p4" yields the following output:

player name: p1
QD AD KH AC KC JH AD KH 
9H QS JD KD 
Melds:  pinochle 40
player name: p2
JC KS 10H AH 10S 10S QH 10D 
QS JD 9C JC 
Melds:  pinochle 40
player name: p3
9D JS JH QD 9S 10H 9S 10C 
9H JS KD QC 
Melds:
player name: p4
10C 10D AS 9D QH AH AS AC 
QC 9C KC KS 
Melds:

>>> Do you wish to stop playing? (yes/*)

Typing "yes" here will end the game, but typing anything else will generate a new distribution of cards. We re-generated the cards several times. Each time the cards were generated, the players' hands are listed in the order that the user specified in the command. Each player's melds are identified if there are any. In the output above, p1 and p2 were correctly identified to have pinochle since they each have one pair of JD and QS cards.

Here are some additional examples of outputs we got when playing:

In the output below, p1 is found to have hundredaces since they have at least one ace from every suit, but do not have all 8 aces. p2 has eightykings since they have one king from every suit. p3 is shown to have both fortyjacks and pinochle. This makes since since p3 has one jack from every suit and a JD and QS. 

player name: p1
KD 10D AC AD AD 9H AH QC 
QS AS AC 10H 
Melds:  hundredaces 100
player name: p2
KC AH 10S 10C JD 10H JS KD 
9D KH JC KS 
Melds:  eightykings 80
player name: p3
QD JD KH JS JC 10C QH QS 
KS JH 10S 9S 
Melds:  fortyjacks 40  pinochle 40
player name: p4
JH AS 10D 9H QD 9C QC QH 
9D 9C 9S KC 
Melds:

>>> Do you wish to stop playing? (yes/*)

Another output is shown below. Here, p1 is shown as having doublepinochle since they have two pairs of JD and QS. Note that p1 has the combination of cards needed for pinochle. However, p1 also meets the criteria for doublepinochle, so only the doublepinochle is counted.

player name: p1
JD JD 9C QC AH QS JH QS 
KS 9S 9H JS 
Melds:  doublepinochle 300
player name: p2
10C AD KS AH JC AC KC AC 
9S 9D 10H 10S 
Melds:
player name: p3
10S 10C KH KC KD 9D 10D AS 
QD 10H 9H 10D 
Melds:
player name: p4
KH QH KD QC AS 9C QH JH 
JC QD JS AD 
Melds:

>>> Do you wish to stop playing? (yes/*) 

The HoldEm game also works as expected. The command "./lab2.out HoldEm p1 p2 p3" yields the following output:

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

Like in Pinochle, typing "yes" here will end the game, but typing anything else will generate a new distribution of cards. We re-generated the cards several times. Each time the cards were generated, the players' hands are initially listed in the order that the user specified in the command. Each player is dealt 2 cards. Then, the program prints the board, which has 3 cards. The cards on the board are dealt to each player. The players' hands are displayed again after the flop. For each hand, the program lists the cards in order, starting with the player's original 2 cards followed by the 3 cards dealt from the board. This time, the players are listed in descending order based on rank.

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
