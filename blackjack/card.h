#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using std::string; using std::cout; using std::cin;
using std::vector; using std::endl;

struct Card {
	int colour{};
	int value{};

	Card();
	Card(int, int);
	friend std::ostream& operator <<(std::ostream&, Card);
};

vector<Card> createDeck();
void shuffleDeck(vector<Card>&);