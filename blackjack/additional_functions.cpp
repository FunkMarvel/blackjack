#include "blackjackLib.h"

void clearCin() {
    // Function that clears cin buffer.
    // Courtesy of Johannes Skjeltorp-Borgaas.

    std::cin.clear();
    std::cin.ignore(32767, '\n');
}