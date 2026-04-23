// Entry point of the Blackjack game
#include <ctime>
#include "include/input.h"

int main() {
    srand(time(0)); // seed random number generator with current time
    show_menu();
}
