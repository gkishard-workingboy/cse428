#pragma once
#include <string>
#include <vector>
using namespace std;

class Game {
public:
	Game(int, char* []);
	virtual int play() = 0;
protected:
	vector<string> players;
};