LAB0
Team member
Zhikuan Wei(w.zhikuan@wustl.edu)
Haoyuan Ye
Julia Zeng

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
