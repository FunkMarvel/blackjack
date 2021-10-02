// Compulsory 2, Anders P. Åsbø
#include "blackjackLib.h"

int main() {
	User current_user{};
	mainMenu(current_user);
	return 0;
}

void mainMenu(User &current_user) {
	char user_selection{};

	while (true) {
		system("cls");
		cout << " Welcome to the Lucky 38!" << endl;
		cout << " 1. Log in" << endl;
		cout << " 2. New user" << endl;
		cout << " Select menu item: ";
		cin >> user_selection;

		switch (tolower(user_selection)) {
		case '1': case 'l':
			current_user = login();
			return;
		case '2': case 'n':
			current_user = newUser();
			return;
		default:
			break;
		}
	}
}