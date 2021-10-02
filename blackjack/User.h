#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using std::string; using std::cout; using std::cin;
using std::vector; using std::endl;

struct User {
	string password{};
	string username{};

	User();
	User(string, string);
	void save(string);
	friend std::ostream& operator <<(std::ostream&, User);
};

User newUser();
User login();
vector<User> loadUsers(string);
