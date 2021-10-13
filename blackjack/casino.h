#pragma once
#include "user.h"
#include "card.h"

void clearCin();
void mainMenu(User&);
void blackjack(User&, User&, vector<Card>&);
bool userDraws(User&, vector<Card>&, int&);
void houseDraws(User&, User&, vector<Card>&, int&);