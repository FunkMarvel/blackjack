#include "User.h"

User::User(string new_username, string new_password) {
	username = new_username; password = new_password;
}

inline bool User::operator ==(User some_user) {
	return (username == some_user.username && password == some_user.password);
}

std::ostream& operator <<(std::ostream &os, User some_user) {
	os << "{" << some_user.username << ":" << some_user.password << "}";
	return os;
}

void User::save(string filename) {
	std::ofstream ofile(filename, std::ios::app);
	if (ofile.is_open()) {
		ofile << this << std::endl;  // saves data
		ofile.close();
	}
	else {
		std::cout << "Save failed." << std::endl;  // exits on failure to open savefile
		exit(1);
	}
}