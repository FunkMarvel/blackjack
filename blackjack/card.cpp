#include "casino.h"  // includes forward declarations from card.h
#include <random>
#include <algorithm>

Card::Card() {
	// Default constructor for Card-struct. Default card is ace of spades.
	colour = 3; rank = 1;
}

Card::Card(int in_colour, int in_rank) {
	// constructor that gives card user-provided colour and rank.
	colour = in_colour;
	rank = in_rank;
}

std::ostream& operator <<(std::ostream& os, Card some_card) {
	// overloading insertion operator for Card struct. Inserts string with Card-object's
	// colour and rank into ostream with format "[rank] of [colour]".
	// 
	// Args:
	//	os -- refrence to ostream.
	//	some_card -- object of struct Card.

	// vectors with colour-names and special ranks:
	vector<string> colours{ "hearts", "diamonds", "clubs", "spades" };
	vector<string> ranks{ "ace", "knight", "queen", "king" };

	if (some_card.rank == 1) {  // formats for aces.
		os << ranks[some_card.rank - 1] << " of " << colours[some_card.colour];
		return os;
	}
	else if (some_card.rank > 10) {  // formats for knights, queens and kings:
		os << ranks[some_card.rank - 10] << " of " << colours[some_card.colour];
		return os;
	}
	else {  // formats for all other cards:
		os << some_card.rank << " of " << colours[some_card.colour];
		return os;
	}
}

vector<Card> createDeck() {
	// Function creating and returning an ordered vector of Card-objects.
	// The vector corresponds to a regular 52 card playing deck.

	vector<Card> deck{};

	for (int i = 0; i < 4; i++) {
		for (int j = 1; j <= 13; j++) {
			deck.push_back(Card(i, j));  // i loops through colours and j loops through ranks.
		}
	}
	return deck;
}

void shuffleDeck(vector<Card> &deck) {
	// Function shuffling the provided vector of cards, using <algorithm>'s shuffle function.
	//
	// Args:
	//	deck -- refrence to vector of Card-objects.

	// using 64-bit Mersenne-Twister as RNG for shuffle-function:
	std::random_device rd{};
	std::mt19937_64 gen(rd());

	std::shuffle(deck.begin(), deck.end(), gen);  // shuffling deck.
}