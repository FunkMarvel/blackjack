#pragma once
#include "user.h"
#include "card.h"

void clearCin();
void mainMenu(User&);
void blackjack(User&);
bool userDraws(User& current_user, vector<Card>& deck, int& num_cards_pulled);
void houseDraws(User& current_user, vector<Card>& deck, int& num_cards_pulled);