// Compulsory 2, Anders P. Asbo
#include "casino.h"

int main() {
	User current_user{};
	User house{};
	vector<Card> deck{ createDeck() };

	while (true) {
		mainMenu(current_user);

		system("cls");
		cout << " Welcome " << current_user.getUsername() << ", to the Lucky 38!" << endl;

		char user_answer{ 'y' };
		while (true) {
			if (tolower(user_answer) == 'n') {
				break;
			}
			else if (tolower(user_answer) == 'y') {
				house.clearHand();
				current_user.clearHand();
				blackjack(house, current_user, deck);
			}
			cout << " Play again? y/n: ";
			cin >> user_answer;
			system("cls");
		}
	}

	return 0;
}

void mainMenu(User &current_user) {
	char user_selection{};

	while (true) {
		system("cls");
		cout << " Welcome to the Lucky 38!" << endl;
		cout << " 1. Log in" << endl;
		cout << " 2. New user" << endl;
		cout << " 3. Exit (q)" << endl;
		cout << " Select menu item: ";
		cin >> user_selection;

		switch (tolower(user_selection)) {
		case '1': case 'l':
			current_user = login();
			return;
		case '2': case 'n':
			current_user = newUser();
			return;
		case 'q': case '3':
			exit(0);
		default:
			break;
		}
	}
}

void blackjack(User &house, User &current_user, vector<Card> &deck) {
	int num_cards_pulled{};
	shuffleDeck(deck);
	

	if (!userDraws(current_user, deck, num_cards_pulled)) {
		cout << " House wins!" << endl;
		return;
	}
	else {
		houseDraws(house, current_user, deck, num_cards_pulled);
	}

	cout << " " << current_user.getUsername() << ":" << endl;
	current_user.printHand();
	cout << endl;

	cout << " House:" << endl;
	house.printHand();
	cout << endl;

	if ((house.hand_total < current_user.hand_total || house.hand_total > 21) && current_user.hand_total <= 21) {
		cout << " You win!" << endl;
	}
	else if (house.hand_total > current_user.hand_total && house.hand_total <= 21) {
		cout << " House wins!" << endl;
	}
	else {
		cout << " It's a draw!" << endl;
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
			return true;
		default:
			break;
		}
		if (current_user.hand_total > 21) {
			system("cls");
			current_user.printHand();
			return false;
		}
	}
}

void houseDraws(User &house, User &current_user, vector<Card>& deck, int& num_cards_pulled) {

	while (num_cards_pulled < deck.size()) {
		// int temp_total{ house.hand_total };
		house.addToHand(deck[num_cards_pulled++]);

		if (house.hand_total > current_user.hand_total) {
			break;
		}

		/*if (house.hand_total > 21) {
			house.hand_total = temp_total;
			house.hand.pop_back();
			num_cards_pulled--;
			break;
		}*/
	}
}