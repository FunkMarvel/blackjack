#pragma once
// main header for casino library and Compulsory 2 project.

#include "user.h"  // includes both card.h and user.h.

// definitions of functions in casino.cpp:
void clearCin();
void casino();
void mainMenu(User&);
void blackjack(User&, User&, vector<Card>&, int&);
bool userDraws(User&, vector<Card>&, int&);
void houseDraws(User&, User&, vector<Card>&, int&);
void bet(User&, User&, int&);
void printBet(User&, User&, int, int&);
void printCash(User&, User&);