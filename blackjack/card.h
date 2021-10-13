#pragma once

// This is the top-level header, so here are the top-level includes:
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// namespacing commonly used names:
using std::string; using std::cout; using std::cin;
using std::vector; using std::endl;

struct Card {
	// Struct corresponding to a single playing card.
	// Each Card object has a colour (0 == hearts, 1 == diamonds, 2 == clubs, 3 == spades),
	// and a rank (number from and including 1 to and including 13).
	// Rank 1 corresponds to ace, and rank 11, 12 and 13 corresponds to
	// knight, queen and king respectivly.

	int colour{};
	int rank{};

	// constructors:
	Card();
	Card(int, int);

	// operator overloads:
	friend std::ostream& operator <<(std::ostream&, Card);
};

// stand-alone functions for creating and shuffeling deck of cards:
vector<Card> createDeck();
void shuffleDeck(vector<Card>&);