LAB3
Team member
Zhikuan Wei(w.zhikuan@wustl.edu)
Julia Zeng(julia.z@wustl.edu)
Haoyuan Ye(haoyuan.y@wustl.edu)

Errors and Warnings:
Errors:
1. Missing declaration of HoldEmGame or HoldEmGame::PlayerHand
It is due to the reason that the function need that type is declared before that type, so I decide to put forward the declaration of that type, but turns out that it is impossible for a nested struct to be forward declared, so I just reorder the code.
2. "Failed to add card" 
This was an error I had the Pinochle game throw if it tried to move a specific card from a player's hand to the trick, but could not find that card in the player's hand. I encountered this error when testing the program. It was happening because I did not consider the scenario where a player does not have a card of the non-trump suit that was led, and they do not have a higher-ranked trump card or any non-trump card. The program was trying to play a non-trump card when the player didn't have one. The error was solved by having the player play their lowest trump card in this case.
3. bad_alloc
I got this because I had a PinochleGame member variable that tracked each player's melds. This was a vector, and I forgot to clear the vector each time the cards were re-dealt. This error stopped happening when I made sure to clear the vector every time.
4. Segmentation Fault
This is weird problem due to the runtime blurry information. But usually is the proble caused by accessing out of boundary of an array or vector. So I just need skim where the problem crashs and try to find where I have accessed an sequential container.
5. "Money Growth"
Really funny problem, because I just ran HoldEm Game until the end, and found out that two people starting 60 bucks each will end up having over 2k, money really can make money here! But that won't actually should be allowed in computer world, or at least at our game. So after searching carefully, I found out that the money has been added twice since one of our variable controlling which way the money goes has been flipped and never been reseted as expected. 

Warnings:
We got warnings when we tried to compare an int to an unsigned int or size_t. Since the int value was always non-negative, we solved this by making the int an unsigned int or size_t.
There were other warnings too, but all of them just appear as the accompany of errors, so once we fixed the error, the warning just not bother us anymore. 

Behavior of Executable Program:

For any misformed command line, the program prints a usage message and terminates. We tested the following misformed command lines:
./lab3.out
./lab3.out hello
./lab3.out Pinochle
./lab3.out Pinochle playerA
./lab3.out HoldEm
./lab3.out HoldEm playerA
./lab3.out HoldEm player1 player2 player3 player4 player5 player6 player7 player8 player9 player10

All of the above commands caused the program to return a non-zero value.
If the game name is missing or isn't Pinochle or HoldEm, the following message appears:
Usage: ./lab3.out <Game> <Player Names>
Game can be 'Pinochle' or 'HoldEm'.
If the game is Pinochle, there must be 4 player names.
If the game is HoldEm, there must be between 2 and 9 player names.

If the game was specified as Pinochle but there is an incorrect number of player names, the same message above is displayed without the fourth line. If the game was HoldEm and there are too many or too few player names, this message is displayed without the third line.

For well-formed commands, the program plays the game as expected.

For example, "./lab3.out Pinochle p1 p2 p3 p4" yields the following output:

[w.zhikuan@linuxlab004 lab3]$ ./lab3.out Pinochle p1 p2 p3 p4
player name: p1
QH 10D QS 10D 10C KS AS JD 
AC AD JH 10C 
Melds:  pinochle 40  offsuitmarriage 20
player name: p2
KC QD AH JS QC JC 9C AS 
9S QH 10S 10H 
Melds:  offsuitmarriage 20
player name: p3
QS QD 9H KH 10S JD KS AH 
9S 10H AD AC 
Melds:  pinochle 40  offsuitmarriage 20  dix 10
player name: p4*
9H QC KD KC 9D JC 9C JS 
JH KD 9D KH 
Melds:  offsuitmarriage 20  dix 10
contract went to team 1 (p1, p3), running tally: 130

Trick #1
Trump suit: H Leading suit: S
Cards played (in order): p1:AS p2:9S p3:9S p4:JS 
p1 won the trick with card AS
Running tally for team 1 (p1, p3): 143

Trick #2
Trump suit: H Leading suit: D
Cards played (in order): p1:AD p2:QD p3:JD p4:9D 
p1 won the trick with card AD
Running tally for team 1 (p1, p3): 159

Trick #3
Trump suit: H Leading suit: C
Cards played (in order): p1:AC p2:9C p3:AC p4:9C 
p1 won the trick with card AC
Running tally for team 1 (p1, p3): 181

Trick #4
Trump suit: H Leading suit: D
Cards played (in order): p1:10D p2:AH p3:QD p4:9D 
p2 won the trick with card AH
Running tally for team 1 (p1, p3): 181

Trick #5
Trump suit: H Leading suit: S
Cards played (in order): p2:AS p1:QS p3:QS p4:KH 
p4 won the trick with card KH
Running tally for team 1 (p1, p3): 181

Trick #6
Trump suit: H Leading suit: D
Cards played (in order): p4:KD p1:10D p2:10H p3:AD 
p2 won the trick with card 10H
Running tally for team 1 (p1, p3): 181

Trick #7
Trump suit: H Leading suit: S
Cards played (in order): p2:10S p1:KS p3:KS p4:JH 
p4 won the trick with card JH
Running tally for team 1 (p1, p3): 181

Trick #8
Trump suit: H Leading suit: D
Cards played (in order): p4:KD p1:JD p2:QH p3:AH 
p3 won the trick with card AH
Running tally for team 1 (p1, p3): 201

Trick #9
Trump suit: H Leading suit: H
Cards played (in order): p3:10H p1:JH p2:JC p4:9H 
p3 won the trick with card 10H
Running tally for team 1 (p1, p3): 215

Trick #10
Trump suit: H Leading suit: S
Cards played (in order): p3:10S p1:QH p2:JS p4:JC 
p1 won the trick with card QH
Running tally for team 1 (p1, p3): 232

Trick #11
Trump suit: H Leading suit: C
Cards played (in order): p1:10C p2:QC p3:KH p4:QC 
p3 won the trick with card KH
Running tally for team 1 (p1, p3): 252

Trick #12
Trump suit: H Leading suit: H
Cards played (in order): p3:9H p1:10C p2:KC p4:KC 
p3 won the trick with card 9H
Running tally for team 1 (p1, p3): 280

team 1's bid was 286
Total Scores:
team 1 (p1, p3): 0 (increased by 0 this round)
team 2 (p2, p4): 0

>>> Do you wish to stop playing? (yes/*) 

Typing "yes" here will end the game, but typing anything else will start a new deal. We repeated the deal several times. Each time the cards were generated, the players' hands are listed in the order that the user specified in the command. Each player's melds are identified correctly and completly. 
And cards are played correctly in each trick, and the winner of each trick is identified correctly and scoring will be tallied accurately in each trick. The result of trick is correctly conducted by comparing bid and running tally.

If there was a misdeal, the tricks will not be played. The game will print a message saying there was a misdeal and re-deal the cards if the user continues playing. For example:
New deal
player name: p1
KD JD 10H 10S AH QH JS 9S 
JC QD QC 9S 
Melds:  insuitmarriage 40
player name: p2
9D KS AS AC AS KC KC 10D 
AD KS KH 9C 
Melds:  dix 10
player name: p3
10H AH JH QH 10C QS 9C JH 
KD 10D QS JC 
Melds:
player name: p4*
QC 10C 9H 9D 9H QD AD JS 
10S AC KH JD 
Melds:  dix 10
misdeal, re-dealing cards...


>>> Do you wish to stop playing? (yes/*) 

Here are some additional examples of outputs we got when playing:

In the output below, p2 is found to have two offsuitmarriage since they have two pair of Queen and King but both are not of trump suit. p4 got one insuitmarriage and a dix, so team 2 won the contract, and they played alligned with strategy we made during trick, and finally won the points as same value as their bid.

player name: p1*
9C QC AC QS 10C AS 10S 9C 
10D JH AH KH 
Melds:
player name: p2
QS AD KD 10H 10C 10H QD 9S 
KS AS 10D QD 
Melds:  offsuitmarriage 20  offsuitmarriage 20
player name: p3
JD AC AH KD JD KS QC 9S 
9D JS JH JS 
Melds:
player name: p4
QH 9H KH JC KC QH JC KC 
9H AD 10S 9D 
Melds:  insuitmarriage 40  dix 10
contract went to team 2 (p2, p4), running tally: 90

Trick #1
Trump suit: H Leading suit: S
Cards played (in order): p2:AS p1:QS p3:9S p4:10S 
p2 won the trick with card AS
Running tally for team 2 (p2, p4): 114

Trick #2
Trump suit: H Leading suit: D
Cards played (in order): p2:AD p1:10D p3:9D p4:9D 
p2 won the trick with card AD
Running tally for team 2 (p2, p4): 135

Trick #3
Trump suit: H Leading suit: H
Cards played (in order): p2:10H p1:AH p3:JH p4:9H 
p1 won the trick with card AH
Running tally for team 2 (p2, p4): 135

Trick #4
Trump suit: H Leading suit: S
Cards played (in order): p1:AS p2:9S p3:JS p4:KH 
p4 won the trick with card KH
Running tally for team 2 (p2, p4): 152

Trick #5
Trump suit: H Leading suit: D
Cards played (in order): p4:AD p1:KH p2:QD p3:JD 
p1 won the trick with card KH
Running tally for team 2 (p2, p4): 152

Trick #6
Trump suit: H Leading suit: C
Cards played (in order): p1:AC p2:10C p3:QC p4:JC 
p1 won the trick with card AC
Running tally for team 2 (p2, p4): 152

Trick #7
Trump suit: H Leading suit: S
Cards played (in order): p1:10S p2:QS p3:JS p4:QH 
p4 won the trick with card QH
Running tally for team 2 (p2, p4): 170

Trick #8
Trump suit: H Leading suit: C
Cards played (in order): p4:KC p1:10C p2:10H p3:AC 
p2 won the trick with card 10H
Running tally for team 2 (p2, p4): 205

Trick #9
Trump suit: H Leading suit: D
Cards played (in order): p2:10D p1:JH p3:JD p4:QH 
p4 won the trick with card QH
Running tally for team 2 (p2, p4): 222

Trick #10
Trump suit: H Leading suit: C
Cards played (in order): p4:KC p1:9C p2:QD p3:AH 
p3 won the trick with card AH
Running tally for team 2 (p2, p4): 222

Trick #11
Trump suit: H Leading suit: S
Cards played (in order): p3:KS p1:9C p2:KS p4:9H 
p4 won the trick with card 9H
Running tally for team 2 (p2, p4): 230

Trick #12
Trump suit: H Leading suit: C
Cards played (in order): p4:JC p1:QC p2:KD p3:KD 
p1 won the trick with card QC
Running tally for team 2 (p2, p4): 230

team 2's bid was 212
Total Scores:
team 2 (p2, p4): 212 (increased by 212 this round)
team 1 (p1, p3): 0

When a team's score equals or exceeds 1500, the game ends and prints a message saying that team won. Here's an example message:
Game over. 
Winner: team 2 (p2, p4) with score 1835

The HoldEm game also works as expected. The command "./lab3.out HoldEm p1 p2 p3" yields the following output:

player name: p1
9S AS 
player name: p2
9C 8C 
player name: p3*
6D 10D 
 pot starts with 0 chips
Player p3 has 60 chips
Player p3 calls
Player p3 leaves 58 chips 
Player p1 has 59 chips
Player p1 calls
Player p1 leaves 58 chips 
BOARD (flop): KD 5S 8S 
Player: p2
9C 8C 8S 5S KD 
Hand rank: pair
Player: p1
9S AS 8S 5S KD 
Hand rank: xhigh
Player: p3
6D 10D 8S 5S KD 
Hand rank: xhigh
 pot starts with 6 chips
Player p2 has 58 chips
Player p2 checks
Player p2 leaves 58 chips 
Player p3 has 58 chips
Player p3 checks
Player p3 leaves 58 chips 
Player p1 has 58 chips
Player p1 checks
Player p1 leaves 58 chips 
BOARD (turn): KD 5S 8S QS 
Player: p1
QS 5S 8S 9S AS 
Hand rank: flush
Player: p2
QS KD 8S 9C 8C 
Hand rank: pair
Player: p3
QS KD 8S 6D 10D 
Hand rank: xhigh
 pot starts with 6 chips
Player p2 has 58 chips
Player p2 checks
Player p2 leaves 58 chips 
Player p3 has 58 chips
Player p3 checks
Player p3 leaves 58 chips 
Player p1 has 58 chips
Player p1 bets 4
Player p1 leaves 54 chips 
Player p2 has 58 chips
Player p2 calls
Player p2 leaves 54 chips 
Player p3 has 58 chips
Player p3 folds 
Player p3 leaves 58 chips 
BOARD (river): KD 5S 8S QS 4H 
Player: p1
QS 5S 8S 9S AS 
Hand rank: flush
Player: p2
QS KD 8S 9C 8C 
Hand rank: pair
 pot starts with 14 chips
Player p1 has 54 chips
Player p1 bets 4
Player p1 leaves 50 chips 
Player p2 has 54 chips
Player p2 folds 
Player p2 leaves 54 chips 
Player p1 won 18 chips

>>> Would you like to end the current game? (yes/*) 

Like in Pinochle, typing "yes" here will end the game, but typing anything else will start a new round. We repeated the game several times. Each time the cards were reshuffeled and dealt, the players' hands are initially listed in the order that the user specified in the command. Each player is dealt 2 cards. Then we start pre-flop round betting, first two player in order should pay small blind and big blind, then players will follow certain strategy to act at betting round considering their hand. Then, the program prints the board after flop. The cards on the board are dealt to each player. The players' hands who still remain in game (not fold) are displayed again after the flop, fllowing the order by thier hand rank. And start another round of betting. So on and so forth. Until only one person doesn't fold or those people with highest hand rank win this round and get those chips in pot.

Here a few examples from the outputs we got:

In the output below, p2 folds at pre-flop, which is expected since they only got a 5 and a 7 at start. After the flop, p1 and p3 both only has xhigh in hand, so they decided to check. And since p2 alreay folded, we don't consider him at this round anymore. Even after river, both p1 and p3 still has xhigh in hand, so none of them raise. And p1 who got higher card 9C won at the end.   

player name: p1*
9C 8S 
player name: p2
5D 7H 
player name: p3
8D 4D 
 pot starts with 0 chips
Player p1 has 68 chips
Player p1 calls
Player p1 leaves 66 chips 
Player p2 has 53 chips
Player p2 folds 
Player p2 leaves 53 chips 
BOARD (flop): JS 7C 6C 
Player: p1
9C 8S 6C 7C JS 
Hand rank: xhigh
Player: p3
8D 4D 6C 7C JS 
Hand rank: xhigh
 pot starts with 5 chips
Player p3 has 56 chips
Player p3 checks
Player p3 leaves 56 chips 
Player p1 has 66 chips
Player p1 checks
Player p1 leaves 66 chips 
BOARD (turn): JS 7C 6C AS 
Player: p1
AS JS 7C 9C 8S 
Hand rank: xhigh
Player: p3
AS JS 7C 6C 8D 
Hand rank: xhigh
 pot starts with 5 chips
Player p3 has 56 chips
Player p3 checks
Player p3 leaves 56 chips 
Player p1 has 66 chips
Player p1 checks
Player p1 leaves 66 chips 
BOARD (river): JS 7C 6C AS 2H 
Player: p1
AS JS 7C 9C 8S 
Hand rank: xhigh
Player: p3
AS JS 7C 6C 8D 
Hand rank: xhigh
 pot starts with 5 chips
Player p3 has 56 chips
Player p3 checks
Player p3 leaves 56 chips 
Player p1 has 66 chips
Player p1 checks
Player p1 leaves 66 chips 
Player p1 won 5 chips

>>> Would you like to end the current game? (yes/*) 

In the next example, p1 and p3 are correctly identified to have a pair rank after flop. p2 was recognized as a pair of 8 after turn with a higher card rank. So p2 won at the end.

player name: p1
2S 2H 
player name: p2
8C KD 
player name: p3*
3S 9S 
 pot starts with 0 chips
Player p3 has 60 chips
Player p3 calls
Player p3 leaves 58 chips 
Player p1 has 59 chips
Player p1 calls
Player p1 leaves 58 chips 
BOARD (flop): QC 3C AS 
Player: p3
3S 9S AS 3C QC 
Hand rank: pair
Player: p1
2S 2H AS 3C QC 
Hand rank: pair
Player: p2
8C KD AS 3C QC 
Hand rank: xhigh
 pot starts with 6 chips
Player p2 has 58 chips
Player p2 checks
Player p2 leaves 58 chips 
Player p3 has 58 chips
Player p3 checks
Player p3 leaves 58 chips 
Player p1 has 58 chips
Player p1 checks
Player p1 leaves 58 chips 
BOARD (turn): QC 3C AS 8D 
Player: p2
8D QC AS 8C KD 
Hand rank: pair
Player: p3
3S 9S AS 3C QC 
Hand rank: pair
Player: p1
8D QC AS 2S 2H 
Hand rank: pair
 pot starts with 6 chips
Player p2 has 58 chips
Player p2 checks
Player p2 leaves 58 chips 
Player p3 has 58 chips
Player p3 checks
Player p3 leaves 58 chips 
Player p1 has 58 chips
Player p1 checks
Player p1 leaves 58 chips 
BOARD (river): QC 3C AS 8D JD 
Player: p2
8D QC AS 8C KD 
Hand rank: pair
Player: p1
JD QC AS 2S 2H 
Hand rank: pair
Player: p3
JD QC 3C AS 3S 
Hand rank: pair
 pot starts with 6 chips
Player p2 has 58 chips
Player p2 checks
Player p2 leaves 58 chips 
Player p3 has 58 chips
Player p3 checks
Player p3 leaves 58 chips 
Player p1 has 58 chips
Player p1 checks
Player p1 leaves 58 chips 
Player p2 won 6 chips

>>> Would you like to end the current game? (yes/*) 

Here's another example. p1 is correctly identified to have two pairs after flop, a pair of 3's and a pair of 9's. p1 is displayed first after the flop since their hand has the highest rank. But after turn, p2 also got their two pairs and splited the pot with p1 at final.

player name: p1*
3D 3H 
player name: p2
QS 5S 
player name: p3
7S 10D 
 pot starts with 0 chips
Player p1 has 58 chips
Player p1 calls
Player p1 leaves 56 chips 
Player p2 has 60 chips
Player p2 calls
Player p2 leaves 59 chips 
BOARD (flop): 9S KH 9H 
Player: p1
3D 3H 9H KH 9S 
Hand rank: twopair
Player: p2
QS 5S 9H KH 9S 
Hand rank: pair
Player: p3
7S 10D 9H KH 9S 
Hand rank: pair
 pot starts with 6 chips
Player p3 has 59 chips
Player p3 checks
Player p3 leaves 59 chips 
Player p1 has 56 chips
Player p1 bets 2
Player p1 leaves 54 chips 
Player p2 has 59 chips
Player p2 calls
Player p2 leaves 57 chips 
Player p3 has 59 chips
Player p3 calls
Player p3 leaves 57 chips 
BOARD (turn): 9S KH 9H QD 
Player: p2
QD 9S KH 9H QS 
Hand rank: twopair
Player: p1
3D 3H 9H KH 9S 
Hand rank: twopair
Player: p3
QD 9S KH 9H 10D 
Hand rank: pair
 pot starts with 12 chips
Player p1 has 54 chips
Player p1 checks
Player p1 leaves 54 chips 
Player p2 has 57 chips
Player p2 checks
Player p2 leaves 57 chips 
Player p3 has 57 chips
Player p3 checks
Player p3 leaves 57 chips 
BOARD (river): 9S KH 9H QD 8C 
Player: p1
3D 3H 9H KH 9S 
Hand rank: twopair
Player: p2
QD 9S KH 9H QS 
Hand rank: twopair
Player: p3
QD 9S KH 9H 10D 
Hand rank: pair
 pot starts with 12 chips
Player p1 has 54 chips
Player p1 checks
Player p1 leaves 54 chips 
Player p2 has 57 chips
Player p2 checks
Player p2 leaves 57 chips 
Player p3 has 57 chips
Player p3 checks
Player p3 leaves 57 chips 
Player p1 won 6 chips
Player p2 won 6 chips

>>> Would you like to end the current game? (yes/*) 


And I also observed a really interesting case in our HoldEm Game:

player name: A
9S 5H 
player name: C*
JS 8D 
player name: D
QS AC 
player name: E
7S 9D 
 pot starts with 0 chips
Player A has 122 chips
Player A folds 
Player A leaves 122 chips 
Player C has 57 chips
Player C folds 
Player C leaves 57 chips 
Player D has 62 chips
Player D folds 
player E wins with 3 chips
Player A won 0 chips
Player C won 3 chips
Player D won 0 chips
Player E won 0 chips

Due to the rule that only the ealier player will win the remainder at tie game, and here we have a pot less than the number of player in tie. So only Player C won all the chips.
