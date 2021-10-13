#include "casino.h"  // includes declarations from user.h

string database = "users.txt";  // filename of file storing usernames and passwords.

User::User() {
	// Default constructor.
	// default user is the house ai.
	username = "House is playing";
	password = "HousePass";
	cash = 100;  // starting cash
}

User::User(string new_username, string new_password) {
	// constructor assigning user-provided username and password to object.
	username = new_username; password = new_password;
	cash = 100;  // starting cash
}

std::ostream& operator <<(std::ostream &os, User some_user) {
	// overload of insertion-operator for User-class. Inserts username and password of
	// given User-object into ostream with the format "{[username]:[password]}".
	// Used for saving to file. Not particularly secure, but implementing salted hashing seemed
	// a bit beyond the scope of this assignment.

	os << "{" << some_user.username << ":" << some_user.password << "}";
	return os;
}

string User::getUsername() {
	// Method for retrieving username. Returns value of username-string.
	return username;
}

string User::getPassword() {
	// Method for retrieving password. Returns value of password-string.
	return password;
}

void User::save(string filename) {
	// Method for saving username and password to database-file.
	//
	// Args:
	//	filename -- string containing filename of database-file.

	std::ofstream ofile(filename, std::ios::app);
	if (ofile.is_open()) { // saves data to end of file if file is open.
		ofile << *this << std::endl;
		ofile.close();
	}
	else {
		// exits on failure to open savefile:
		std::cout << "Save failed." << std::endl;
		exit(1);
	}
}

void User::addToHand(Card new_card) {
	// Method for adding provided card to user's hand.
	// 
	// Args:
	//	new_card -- Card-object to be added to hand.

	hand.push_back(new_card);  // adds card to user's hand-vector.

	// increases value of hand, stored in hand_total, by new_card's value:
	if (new_card.rank == 1 && username != "House is playing") {
		while (true) {  // if User-object is a player, then the player choses value of ace:
			int choice{};
			system("cls");
			printHand();

			cout << endl << " Count ace as 1 or 11? : ";
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
				break;  // invalid input is ignored, reprinting prompt.
			}
		}
	} // if user is house ai, then value of ace is picked automatically:
	else if (new_card.rank == 1 && username == "House is playing") {  // Only house has whitespace in username.
		if ((hand_total + 11) > 21) {  // chose ace to be 1 if 11 leads to loss.
			hand_total += 1;
		}
		else {  // chose ace to be 11 otherwise:
			hand_total += 11;
		}
	}
	else if (new_card.rank > 10) {  // knights, queens and kings all have value of 10:
		hand_total += 10;
	}
	else {  // every other card has value equal to their rank:
		hand_total += new_card.rank;
	}
}

void User::clearHand() {
	// Method for clearing user's hand. Empties and shrinks (if possible) hand-vector,
	// and sets hand value to 0.

	hand.clear();
	hand.shrink_to_fit();
	hand_total = 0;
}

const void User::printHand() {
	// Method for printing user's hand.

	// Only prints most recent card if hand is not empty:
	if (hand.size() > 0) cout << " Most recently drawn card: " << hand[hand.size() - 1] << endl;

	// prints all cards in hand:
	cout << " Current hand: ";
	for (int i = 0; i < hand.size(); i++) {
		if ((i - 1) % 5 == 4) {
			cout << endl << "               ";
		}
		cout << hand[i] << ", ";
	}

	// prints value of hand, and user's remaining cash:
	cout << endl << " Current hand value: " << hand_total << endl;
	cout << " Current cash: $" << cash << endl;
}

User newUser() {
	// Function for creating new user and saving them to database-file. Returns a User-object
	// corresponding to the created user.

	string username{};
	string password{};
	vector<User> existing_users = loadUsers(database);  // loading existing users.
	bool usernameFree{ false };
	system("cls");

	if (existing_users.size() > 0) {
		// checks if username is taken if there are existing users:
		while (!usernameFree) {
			clearCin();
			cout << " Enter new username, no whitespace allowed: ";
			cin >> username;
			system("cls");

			for (int i = 0; i < existing_users.size(); i++) {
				if (existing_users[i].getUsername() == username) {
					cout << " Username taken. Try again." << endl;
					break;
				}
				else if (i == existing_users.size()-1) {
					usernameFree = true;
				}
			}
		}
	}
	else {  // Does not check if username is taken when there are no existing users:
		cout << " Enter new username, no whitespace allowed: ";
		clearCin();
		cin >> username;
	}

	// asking user for password:
	cout << " Enter new password, no whitespace allowed: ";
	clearCin();
	cin >> password;

	// creating, saving and returning new user:
	User new_user(username, password);
	new_user.save(database);
	return new_user;
}

vector<User> loadUsers(string filename) {
	// Function for loading existing users from database-file. Returns vector of User-objects
	// corresponding to existing users.
	//
	// Args:
	//	filename -- string containing filename of database-file.

	std::ifstream ifile(filename);
	if (!ifile) {  // if no database-file exists, a new one is created:
		std::ofstream ofile(filename);
		ofile.close();
		ifile.open(filename);
	}

	// variables for parsing:
	string line{};
	int start{};
	int stop{};
	vector<User> users{};

	if (ifile.is_open()) {
		// loops through database-file and loads username-password pairs:
		while (std::getline(ifile, line)) {
			if (line.size() > 0) {
				// parses and retrieves username:
				start = line.find('{'); stop = line.find(':');
				string username = line.substr(start + 1, stop - start - 1);

				// parses and retrieves password:
				start = stop; stop = line.find('}');
				string password = line.substr(start + 1, stop - start - 1);

				// adding user to vector:
				users.push_back(User(username, password));
			}
		}
		ifile.close();
	}
	else {  // exits on failure to open savefile:
		std::cout << "Load savefile failed." << std::endl;
		exit(1);
	}
	return users;
}

User login() {
	// Function for logging in. Returns User-object corresponding to logged-in user.

	bool user_exists{ false };
	int user_number{};
	int password_tries{};
	int max_tries{ 3 };
	
	// retrieves existing users and exits if no user exists:
	vector<User> existing_users = loadUsers(database);
	if (existing_users.size() < 1) {
		cout << " Please make a user before attemting login." << endl;
		exit(0);
	}
	
	string username{};
	string password{};
	User current_user{};

	while (!user_exists) {  // loops until provided-username matches an existing user.
		system("cls");
		clearCin();
		cout << " Enter username: ";
		cin >> username;

		// checks if username exists:
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

	while (password_tries < max_tries) {  // loops until password is accepted, or password is rejected thrice.
		system("cls");
		clearCin();
		cout << " Enter password: ";
		cin >> password;

		// checks if password is correct:
		if (current_user.getPassword() == password) {
			cout << " Log in successful!" << endl;
			system("pause");
			return current_user;
		}
		else {  // displays remaining attempts if password is incorrect:
			cout << " Incorrect password. " << max_tries - (++password_tries) << " attempts remaining" << endl;
			system("pause");
		}
	}

	// exists on too many password attempts:
	system("cls");
	cout << " Too many incorrect attempts!" << endl;
	system("pause");
	exit(0);
}