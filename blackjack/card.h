#pragma once
#include "user.h"

struct Card {
	int colour{};
	int value{};

	Card();
	Card(int, int);
	friend std::ostream& operator <<(std::ostream&, Card);
};

vector<Card> createDeck();
void shuffleDeck(vector<Card>&);