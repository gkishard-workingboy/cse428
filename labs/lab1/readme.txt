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


Design Decisions:

