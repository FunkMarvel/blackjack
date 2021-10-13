#include "casino.h"

void clearCin() {
    // Function that clears cin buffer.
    // Courtesy of Johannes Skjeltorp-Borgaas.

    std::cin.clear();
    std::cin.ignore(32767, '\n');
}

void casino() {

	while (true) {
		User current_user{};
		mainMenu(current_user);

		User house{};
		vector<Card> deck{ createDeck() };
		int betting_pool{};

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
				blackjack(house, current_user, deck, betting_pool);
			}
			if (current_user.cash <= 0) {
				cout << endl << " You are out of money. Better luck next time!" << endl;
				system("pause");
				break;
			}
			else if (house.cash <= 0) {
				cout << endl << " Congratulations! You have won all our money!" << endl;
				system("pause");
				break;
			}

			cout << endl << " Play again? y/n: ";
			cin >> user_answer;
			system("cls");
		}
	}
}

void mainMenu(User& current_user) {
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

void blackjack(User& house, User& current_user, vector<Card>& deck, int& betting_pool) {
	int num_cards_pulled{};
	shuffleDeck(deck);

	cout << " Buy inn is $10." << endl;
	betting_pool += 20;
	current_user.cash -= 10;
	house.cash -= 10;
	cout << " Current betting pool is $" << betting_pool << "." << endl;

	if (!userDraws(current_user, deck, num_cards_pulled)) {
		system("cls");
		cout << " Your hand of " << current_user.hand_total << " exeeded 21! House wins!" << endl;

		house.cash += betting_pool;
		betting_pool = 0;

		printCash(house, current_user);
		return;
	}
	else {
		houseDraws(house, current_user, deck, num_cards_pulled);
	}

	bet(house, current_user, betting_pool);
	system("pause");
	system("cls");

	cout << " " << current_user.getUsername() << ":" << endl;
	current_user.printHand();
	cout << endl;

	cout << " House:" << endl;
	house.printHand();
	cout << endl << endl;

	if ((house.hand_total < current_user.hand_total || house.hand_total > 21) && current_user.hand_total <= 21) {
		cout << " You win $" << betting_pool << "!" << endl;
		current_user.cash += betting_pool;
		betting_pool = 0;
	}
	else if (house.hand_total > current_user.hand_total && house.hand_total <= 21) {
		cout << " House wins!" << endl;
		house.cash += betting_pool;
		betting_pool = 0;
	}
	else {
		cout << " It's a draw!" << endl;
	}
	cout << endl;
	printCash(house, current_user);
}

bool userDraws(User& current_user, vector<Card>& deck, int& num_cards_pulled) {
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

void houseDraws(User& house, User& current_user, vector<Card>& deck, int& num_cards_pulled) {

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

void bet(User& house, User& current_user, int& betting_pool) {
	while (true) {
		string user_input{};
		int user_bet{};
		system("cls");
		printCash(house, current_user);


		cout << " You can bet any whole number amount of cash less than or equal to the House's cash ($" << house.cash << ")." << endl;
		cout << " To go all in, type 'all in', 'all', 'a', or simply bet $" << current_user.cash << "." << endl;
		cout << " To pass, type 'pass', 'p', or simply bet $0." << endl;
		cout << " Type the amount you wish to bet: ";

		clearCin();
		getline(cin, user_input);
		system("cls");

		if (user_input == "all in" || user_input == "all" || user_input == "a") {
			if (current_user.cash <= house.cash) {
				user_bet = current_user.cash;
				printBet(house, current_user, user_bet, betting_pool);
				return;
			}
			else {
				user_bet = house.cash;
				printBet(house, current_user, user_bet, betting_pool);
				return;
			}
		}
		else if (user_input == "pass" || user_input == "p") {
			user_bet = 0;
			printBet(house, current_user, user_bet, betting_pool);
			return;
		}
		else {
			try {
				user_bet = std::stoi(user_input);
				if (user_bet < 0) throw 1;
				printBet(house, current_user, user_bet, betting_pool);
				return;
			}
			catch (...) {
				continue;
			}
		}
	}
}

void printBet(User& house, User& current_user, int user_bet, int& betting_pool) {
	betting_pool += 2 * user_bet;

	cout << " You bet $" << user_bet << "." << endl;
	cout << " House bet $" << user_bet << "." << endl;
	cout << " Current betting pool is $" << betting_pool << "." << endl << endl;

	current_user.cash -= user_bet;
	house.cash -= user_bet;

	printCash(house, current_user);
}

void printCash(User& house, User& current_user) {
	cout << " You have $" << current_user.cash << " remaining." << endl;
	cout << " The House has $" << house.cash << " remaining." << endl;
}