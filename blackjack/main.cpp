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
	User house{};
	int num_cards_pulled{};
	vector<Card> deck{ createDeck() };
	shuffleDeck(deck);

	if (!userDraws(current_user, deck, num_cards_pulled)) {
		cout << " Game Over!" << endl;
	}
	else {
		houseDraws(house, current_user, deck, num_cards_pulled);
	}
}

bool userDraws(User &current_user, vector<Card> &deck, int &num_cards_pulled) {
	while (true) {
		char user_answer{};
		cout << endl << " Draw a card? y/n: ";
		cin >> user_answer;
		system("cls");

		switch (tolower(user_answer)) {
		case 'y':
			current_user.addToHand(deck[num_cards_pulled++]);
			system("cls");
			current_user.printHand();
			break;
		case 'n':
			cout << " " << endl;
			return true;
		default:
			break;
		}
		if (current_user.hand_total > 21) {
			system("cls");
			cout << endl << " Total score exceeds 21. You lose!" << endl;
			return false;
		}
	}
}

void houseDraws(User &house, User &current_user, vector<Card>& deck, int& num_cards_pulled) {

	while (num_cards_pulled < deck.size()) {
		int temp_total{ house.hand_total };
		house.addToHand(deck[num_cards_pulled++]);

		if (house.hand_total > 21) {
			house.hand_total = temp_total;
			house.hand.pop_back();
			num_cards_pulled--;
			break;
		}
	}
}