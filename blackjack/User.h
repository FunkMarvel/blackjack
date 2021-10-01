#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using std::string; using std::count; using std::cin;
using std::vector;

struct User {
	string password{};
	string username{};

	User(string, string);
	void save(string);
	inline bool operator ==(User some_user);
	friend std::ostream& operator <<(std::ostream&, User);
};

void newUser();
void login();
