#pragma once
#include "card.h"  // includes all necessary libraries.

class User {
	// Class for user-profiles and players.
	// Stores username and password of each user, as well as variables used
	// when playing blackjack.

private:  // username and password privatly:
	string password{};
	string username{};

public:
	// vector containing cards in user's hand, as well as value of hand and user's cash
	// are stored publicly:
	vector<Card> hand{};
	int hand_total{};
	int cash{ 100 };

	// constructors:
	User();
	User(string, string);

	// operator overloads:
	friend std::ostream& operator <<(std::ostream&, User);

	// public methods:
	string getUsername();
	string getPassword();
	void save(string);
	void addToHand(Card);
	void clearHand();
	const void printHand();
};

// stand-alone functions related to user-class:
User newUser();
User login();
vector<User> loadUsers(string);
