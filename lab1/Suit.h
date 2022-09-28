#pragma once
using namespace std;
#include <ostream>

enum class Suit { clubs, diamonds, hearts, spades, undefined };

std::ostream& operator<<(std::ostream& os, const Suit& s);

Suit& operator++(Suit& s);