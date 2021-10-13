#pragma once
#include "card.h"

class User {
private:
	string password{};
	string username{};

public:
	vector<Card> hand{};
	int hand_total{};
	int cash{ 100 };

	User();
	User(string, string);
	string getUsername();
	string getPassword();
	void save(string);
	void addToHand(Card);
	void clearHand();
	const void printHand();
	friend std::ostream& operator <<(std::ostream&, User);
};

User newUser();
User login();
vector<User> loadUsers(string);
