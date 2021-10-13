#include "casino.h"

void clearCin() {
    // Function that clears cin buffer.
    // Courtesy of Johannes Skjeltorp-Borgaas.
    std::cin.clear();
    std::cin.ignore(32767, '\n');
}

void casino() {
	// Function starting entire game.

	while (true) {  // primary loop, displays main menu and runs game-loop.
		User current_user{};  // player user
		mainMenu(current_user);

		// if user login was successful the below code will be executed:
		User house{};  // ai user
		vector<Card> deck{ createDeck() };  // making deck of cards using function from card.cpp.
		int betting_pool{};

		system("cls");
		cout << " Welcome " << current_user.getUsername() << ", to the Lucky 38!" << endl;

		// the below loop runs each game of blackjack:
		char user_answer{ 'y' };  // default to 'y' makes a game of blackjack run on first loop.
		while (true) {
			if (tolower(user_answer) == 'n') {  // breaks loop if player wants to stop playing.
				break;
			}
			else if (tolower(user_answer) == 'y') {  // runs a game of blackjack if user wants to play.
				house.clearHand();  // resets house's hand.
				current_user.clearHand();  // resets user's hand.
				blackjack(house, current_user, deck, betting_pool);  // runs the actual game.
			}
			if (current_user.cash <= 0) {  // stops player for playing more rounds when they're out of money.
				cout << endl << " You are out of money. Better luck next time!" << endl;
				system("pause");
				break;
			}
			else if (house.cash <= 0) { // stops player for playing more rounds when the house is out of money.
				cout << endl << " Congratulations! You have won all our money!" << endl;
				system("pause");
				break;
			}

			// allows user to play again if there's still money to use:
			cout << endl << " Play again? y/n: ";
			cin >> user_answer;
			system("cls");
		}
	}
}

void mainMenu(User& current_user) {
	// Function displaying the login menu.
	// 
	// Args:
	//	current_user -- reference to object of class User to replace with
	//					player's User object after successful login.

	// input variable and menu loop:
	char user_selection{};
	while (true) {

		// displaying menu options and asking for selection:
		system("cls");
		cout << " Welcome to the Lucky 38!" << endl;
		cout << " 1. Log in" << endl;
		cout << " 2. New user" << endl;
		cout << " 3. Exit (q)" << endl;
		cout << " Select menu item: ";
		cin >> user_selection;

		switch (tolower(user_selection)) {
		case '1': case 'l':
			// current_user becomes player's user after successful login:
			current_user = login();
			return;
		case '2': case 'n':
			// current_user becomes player's user after succesful creation of new user:
			current_user = newUser();
			return;
		case 'q': case '3':
			exit(0);  // exits if user wants to.
		default:
			break;  // invalid input just reprints menu.
		}
	}
}

void blackjack(User& house, User& current_user, vector<Card>& deck, int& betting_pool) {
	// Function performing a single game of blackjack. Returns when one round is complete.
	// 
	// Args:
	//	house -- refrence to object of class User that represents ai.
	//	current_user -- refrence to object of class User that represents player.
	//	deck -- refrence to vector of Card objects representing the deck of cards.
	//	betting_pool -- refrence to integer storing the current money pool of bets.

	int num_cards_pulled{};  // variable keeping track of number of cards pulled from deck.
	shuffleDeck(deck);  // function defined in card.cpp.

	// performing initial buy in:
	cout << " Buy-in is $10." << endl;
	betting_pool += 20;
	current_user.cash -= 10;
	house.cash -= 10;
	cout << " Current betting pool is $" << betting_pool << "." << endl;

	if (!userDraws(current_user, deck, num_cards_pulled)) {  // calls function letting player draw cards.
		// if player's hand exceeds 21 player loses automatically:
		system("cls");
		cout << " Your hand of " << current_user.hand_total << " exceeded 21! House wins!" << endl;

		// Distributing winnings:
		house.cash += betting_pool;
		betting_pool = 0;

		printCash(house, current_user);
		return;  // returning on house win.
	}
	else {
		// House draws cards if player's hand doesn't exceed 21:
		houseDraws(house, current_user, deck, num_cards_pulled);
	}

	// performs betting phase:
	bet(house, current_user, betting_pool);
	system("pause");
	system("cls");

	// printing player's hand and house's hand:
	cout << " " << current_user.getUsername() << ":" << endl;
	current_user.printHand();
	cout << endl;

	cout << " House:" << endl;
	house.printHand();
	cout << endl << endl;

	if ((house.hand_total < current_user.hand_total || house.hand_total > 21) && current_user.hand_total <= 21) {
		// Updates cash and betting pool if player wins:
		cout << " You win $" << betting_pool << "!" << endl;
		current_user.cash += betting_pool;
		betting_pool = 0;
	}
	else if (house.hand_total > current_user.hand_total && house.hand_total <= 21) {
		// Updates cash and betting pool if player loses:
		cout << " House wins!" << endl;
		house.cash += betting_pool;
		betting_pool = 0;
	}
	else {
		// betting pool persists to next game if it's a draw:
		cout << " It's a draw!" << endl;
	}
	cout << endl;
	printCash(house, current_user);
}

bool userDraws(User& current_user, vector<Card>& deck, int& num_cards_pulled) {
	// Function allowing player to draw cards. Returns true if user finishes drawing cards without losing.
	// Returns false if player's hand exceeds 21. Drawn cards are stored as elements in hand-vector within
	// current_user object. The index of the current top-most card of the deck is stored in num_cards_pulled.
	// 
	// Args:
	//	current_user -- refrence to object of class User that represents player.
	//	deck -- refrence to vector of Card objects representing the deck of cards.
	//	num_cards_pulled -- refrence to integer storing number of drawn cards.

	// loops until player no longer wants to draw cards, hand exceeds 21 or no more cards in deck:
	while (num_cards_pulled < deck.size()) {

		// asks user if card should be drawn:
		char user_answer{};
		cout << endl << " Draw a card? y/n: ";
		cin >> user_answer;
		system("cls");

		switch (tolower(user_answer)) {
		case 'y':  // adds top-most card from deck to player's hand:
			current_user.addToHand(deck[num_cards_pulled++]);
			system("cls");
			current_user.printHand();  // prints player's current hand.
			break;
		case 'n':
			return true;  // returns if player finished without losing.
		default:
			break;  // invalid input is ignored and promt is reprinted.
		}
		if (current_user.hand_total > 21) {  // returns if player's hand exceeds 21.
			system("cls");
			current_user.printHand();
			return false;
		}
	}
}

void houseDraws(User& house, User& current_user, vector<Card>& deck, int& num_cards_pulled) {
	// Function allowing house ai to draw cards. Drawn cards are stored as elements in hand-vector within
	// house object. The index of the current top-most card of the deck is stored in num_cards_pulled.
	//
	// Args:
	//	house -- refrence to object of class User that represents ai.
	//	current_user -- refrence to object of class User that represents player.
	//	deck -- refrence to vector of Card objects representing the deck of cards.
	//	num_cards_pulled -- refrence to integer storing number of drawn cards.

	// loops until no more cards in deck:
	while (num_cards_pulled < deck.size()) {
		// draws top-most card and adds to house's hand:
		house.addToHand(deck[num_cards_pulled++]);

		// returns if house's hand exceeds player's hand:
		if (house.hand_total > current_user.hand_total) {
			return;
		}
	}
}

void bet(User& house, User& current_user, int& betting_pool) {
	// Function performing the betting phase of the game. Updates the cash variables of house
	// and current_user, and adds bets to betting_pool.
	// 
	// Args:
	//	house -- refrence to object of class User that represents ai.
	//	current_user -- refrence to object of class User that represents player.
	//	betting_pool -- refrence to integer storing the current money pool of bets.

	while (true) {  // loops until valid bet is made.
		string user_input{};  // player's input
		int user_bet{};  // number of dollars bet corresponding to player's input.
		system("cls");
		printCash(house, current_user);

		// printing instructions:
		cout << " You can bet any whole number amount of cash less than or equal to the House's cash ($" << house.cash << ")." << endl;
		cout << " To go all in, type 'all in', 'all', 'a', or simply bet $" << current_user.cash << "." << endl;
		cout << " To pass, type 'pass', 'p', or simply bet $0." << endl;
		cout << " Type the amount you wish to bet: ";

		// geting input:
		clearCin();
		getline(cin, user_input);
		system("cls");

		if (user_input == "all in" || user_input == "all" || user_input == "a") {
			if (current_user.cash <= house.cash) {
				// if house has more money than player, player goes all in and house matches bet:
				user_bet = current_user.cash;
				printBet(house, current_user, user_bet, betting_pool);
				return;
			}
			else {  // if house has less money than player, house goes all in and player matches bet:
				user_bet = house.cash;
				printBet(house, current_user, user_bet, betting_pool);
				return;
			}
		}
		else if (user_input == "pass" || user_input == "p") {
			// passing is equivalent to betting $0:
			user_bet = 0;
			printBet(house, current_user, user_bet, betting_pool);
			return;
		}
		else {
			// if player inputs number, that number of dollars is the players bet. House matches bet.
			try {
				// exception is thrown at invalid input:
				user_bet = std::stoi(user_input);
				if (user_bet < 0) { throw 1; }
				
				// player betting more than they or the house have is equivalent to all in:
				else if (user_bet > house.cash) { user_bet = house.cash; }
				else if (user_bet > current_user.cash) { user_bet = current_user.cash; }

				printBet(house, current_user, user_bet, betting_pool);
				return;
			}
			catch (...) {
				continue;  // catches invalid input and ignores it, reprinting the betting menu.
			}
		}
	}
}

void printBet(User& house, User& current_user, int user_bet, int& betting_pool) {
	// Function printing bets and remaining cash, as well as updating the betting_pool,
	// house's cash and player's cash.
	// 
	// Args:
	//	house -- refrence to object of class User that represents ai.
	//	current_user -- refrence to object of class User that represents player.
	//	user_bet -- integer corresponding to amount player bet.
	//	betting_pool -- refrence to integer storing the current money pool of bets.

	betting_pool += 2 * user_bet;  // adding both bets, house and player always bet the same.

	// printing info:
	cout << " You bet $" << user_bet << "." << endl;
	cout << " House bet $" << user_bet << "." << endl;
	cout << " Current betting pool is $" << betting_pool << "." << endl << endl;

	// removing bets from player's and house's cash:
	current_user.cash -= user_bet;
	house.cash -= user_bet;

	printCash(house, current_user);
}

void printCash(User& house, User& current_user) {
	// Function printing remaining cash.
	// 
	// Args:
	//	house -- refrence to object of class User that represents ai.
	//	current_user -- refrence to object of class User that represents player.

	cout << " You have $" << current_user.cash << " remaining." << endl;
	cout << " The House has $" << house.cash << " remaining." << endl;
}