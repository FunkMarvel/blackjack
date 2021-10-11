// Compulsory 2, Anders P. Asbo
#include "casino.h"

int main() {
	User current_user{};
	mainMenu(current_user);
	system("cls");
	cout << " Welcome " << current_user.getUsername() << ", to the Lucky 38!" << endl;
	blackjack(current_user);

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

void blackjack(User &current_user) {
	int num_cards_pulled{};
	vector<Card> deck{ createDeck() };
	shuffleDeck(deck);

	while (true) {
		char user_answer{};
		cout << " Draw a card? y/n: ";
		cin >> user_answer;
		system("cls");

		cout << " Current hand: ";
		for (int i = 0; i < current_user.hand.size(); i++) {
			if ((i - 1) % 5 == 4) {
				cout << endl << "               ";
			}
			cout << current_user.hand[i] << ", ";
		}
		cout << endl << " Current hand value: " << current_user.hand_total << endl;

		switch (tolower(user_answer)) {
		case 'y':
			cout << " Drawn card: " << deck[num_cards_pulled] << endl;
			current_user.addToHand(deck[num_cards_pulled++]);
			break;
		case 'n':
			cout << " " << endl;
			return;
		default:
			break;
		}
	}
}