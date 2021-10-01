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

void newUser() {
	string username{};
	string password{};
	vector<User> existing_users = loadUsers(filename);
	bool usernameFree{ false };

	if (existing_users.size() > 0) {
		while (!usernameFree) {
			cout << " Enter new username: ";
			cin >> username;

			for (int i = 0; i < existing_users.size(); i++) {
				if (existing_users[i].username == username) {
					cout << " Username taken. Try again." << endl;
					break;
				}
				else if (i == existing_users.size() - 1) {
					usernameFree = true;
				}
			}
		}
	}

	cout << " Enter new password: ";
	cin >> password;

	User new_user(username, password);
	new_user.save(filename);
}

vector<User> loadUsers(string filename) {
	std::ifstream ifile(filename);
	string line;
	vector<User> users{};

	if (ifile.is_open()) {
		while (std::getline(ifile, line)) {
			if (line.size() > 0) {
				string username = line.substr(line.find('{'), line.find(':'));
				string password = line.substr(line.find(':') + 1, line.find('}'));
				users.push_back(User(username, password));
			}
		}
		ifile.close();
	}
	else {
		std::cout << "Load savefile failed." << std::endl;  // exits on failure to open savefile
		exit(1);
	}
}