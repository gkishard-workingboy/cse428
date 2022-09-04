#pragma once
using namespace std;
#include <ostream>

enum class suit { clubs, diamonds, hearts, spades, undefined };

std::ostream& operator<<(std::ostream& os, const suit& s);

suit& operator++(suit& s);