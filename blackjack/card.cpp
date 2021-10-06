#include "card.h"
#include <random>
#include <algorithm>

Card::Card() {
	colour = 's'; value = 1;
}

Card::Card(int in_colour, int in_value) {
	colour = in_colour;
	value = in_value;
}

std::ostream& operator <<(std::ostream& os, Card some_card) {
	vector<string> colours{ "hearts", "diamonds", "clubs", "spades" };
	vector<string> value{ "ace", "knight", "queen", "king" };

	if (some_card.value == 1) {
		os << value[some_card.value - 1] << " of " << colours[some_card.colour];
		return os;
	}
	else if (some_card.value > 10) {
		os << value[some_card.value - 10] << " of " << colours[some_card.colour];
		return os;
	}
	else {
		os << some_card.value << " of " << colours[some_card.colour];
		return os;
	}
}

vector<Card> createDeck() {
	vector<Card> deck{};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			deck.push_back(Card(i, j));
		}
	}
	return deck;
}

void shuffleDeck(vector<Card> &deck) {
	std::random_device rd{};
	std::mt19937_64 gen(rd());

	std::shuffle(deck.begin(), deck.end(), gen);
}