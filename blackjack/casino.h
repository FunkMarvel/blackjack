#pragma once
#include "user.h"
#include "card.h"

void clearCin();
void casino();
void mainMenu(User&);
void blackjack(User&, User&, vector<Card>&, int&);
bool userDraws(User&, vector<Card>&, int&);
void houseDraws(User&, User&, vector<Card>&, int&);
void bet(User&, User&, int&);
void printBet(User&, User&, int, int&);
void printCash(User&, User&);