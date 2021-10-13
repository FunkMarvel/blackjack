#include "casino.h"

string database = "users.txt";

User::User() {
	username = "House is playing";
	password = "HousePass";
}

User::User(string new_username, string new_password) {
	username = new_username; password = new_password;
}

std::ostream& operator <<(std::ostream &os, User some_user) {
	os << "{" << some_user.username << ":" << some_user.password << "}";
	return os;
}

string User::getUsername() {
	return username;
}

string User::getPassword() {
	return password;
}

void User::save(string filename) {
	std::ofstream ofile(filename, std::ios::app);
	if (ofile.is_open()) {
		ofile << *this << std::endl;  // saves data
		ofile.close();
	}
	else {
		std::cout << "Save failed." << std::endl;  // exits on failure to open savefile
		exit(1);
	}
}

void User::addToHand(Card new_card) {
	hand.push_back(new_card);
	if (new_card.value == 1 && username != "House is playing") {
		while (true) {
			int choice{};
			system("cls");
			printHand();
			cout << " Count ace as 1 or 11? : ";
			cin >> choice;
			clearCin();
			switch (choice) {
			case 1:
				hand_total += 1;
				return;
			case 11:
				hand_total += 11;
				return;
			default:
				break;
			}
		}
	}
	else if (new_card.value == 1 && username == "House is playing") {
		if ((hand_total + 11) > 21) {
			hand_total += 1;
		}
		else {
			hand_total += 11;
		}
	}
	else if (new_card.value > 10) {
		hand_total += 10;
	}
	else {
		hand_total += new_card.value;
	}
}

void User::clearHand() {
	hand.clear();
	hand.shrink_to_fit();
	hand_total = 0;
}

const void User::printHand() {
	cout << " Most recently drawn card: " << hand[hand.size() - 1] << endl;
	cout << " Current hand: ";
	for (int i = 0; i < hand.size(); i++) {
		if ((i - 1) % 5 == 4) {
			cout << endl << "               ";
		}
		cout << hand[i] << ", ";
	}
	cout << endl << " Current hand value: " << hand_total << endl;
}

User newUser() {
	string username{};
	string password{};
	vector<User> existing_users = loadUsers(database);
	bool usernameFree{ false };

	if (existing_users.size() > 0) {
		while (!usernameFree) {
			cout << " Enter new username, no whitespace allowed: ";
			cin >> username;

			for (int i = 0; i < existing_users.size(); i++) {
				if (existing_users[i].getUsername() == username) {
					cout << " Username taken. Try again." << endl;
					break;
				}
				else if (i == existing_users.size()) {
					usernameFree = true;
				}
			}
		}
	}
	else {
		cout << " Enter new username, no whitespace allowed: ";
		cin >> username;
	}

	cout << " Enter new password, no whitespace allowed: ";
	cin >> password;

	User new_user(username, password);
	new_user.save(database);
	return new_user;
}

vector<User> loadUsers(string filename) {
	std::ifstream ifile(filename);
	if (!ifile) {
		std::ofstream ofile(filename);
		ofile.close();
		ifile.open(filename);
	}

	string line{};
	int start{};
	int stop{};
	vector<User> users{};

	if (ifile.is_open()) {
		while (std::getline(ifile, line)) {
			if (line.size() > 0) {
				start = line.find('{'); stop = line.find(':');
				string username = line.substr(start + 1, stop - start - 1);

				start = stop; stop = line.find('}');
				string password = line.substr(start + 1, stop - start - 1);
				users.push_back(User(username, password));
			}
		}
		ifile.close();
	}
	else {
		std::cout << "Load savefile failed." << std::endl;  // exits on failure to open savefile
		exit(1);
	}
	return users;
}

User login() {
	bool user_exists{ false };
	int user_number{};
	int password_tries{};
	int username_tries{};
	int max_tries{ 3 };
	
	vector<User> existing_users = loadUsers(database);
	if (existing_users.size() < 1) {
		cout << " Please make a user before attemting login." << endl;
		exit(0);
	}
	
	string username{};
	string password{};
	User current_user{};

	while (!user_exists && username_tries < max_tries) {
		system("cls");
		cout << " Enter username: ";
		cin >> username;

		for (user_number = 0; user_number < existing_users.size(); user_number++) {
			if (existing_users[user_number].getUsername() == username) {
				user_exists = true;
				current_user = existing_users[user_number];
				break;
			}
		}
		if (user_number == existing_users.size()) {
			cout << " Invalid username." << endl;
			system("pause");
		}
	}

	while (password_tries < max_tries) {
		system("cls");
		cout << " Enter password: ";
		cin >> password;

		if (current_user.getPassword() == password) {
			cout << " Log in successful!" << endl;
			system("pause");
			return current_user;
		}
		else {
			cout << " Incorrect password. " << max_tries - (++password_tries) << " attempts remaining" << endl;
			system("pause");
		}
	}
	system("cls");
	cout << " Too many incorrect attempts!" << endl;
	system("pause");
	exit(0);
	return current_user;
}