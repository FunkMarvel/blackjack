#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using std::string; using std::cout; using std::cin;
using std::vector; using std::endl;

class User {
private:
	string password{};
	string username{};

public:
	User();
	User(string, string);
	string getUsername();
	string getPassword();
	void save(string);
	friend std::ostream& operator <<(std::ostream&, User);
};

User newUser();
User login();
vector<User> loadUsers(string);
