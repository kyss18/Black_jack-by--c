#include "../include/Dealer.h"

Hand& Dealer::get_hand() {
    return hand;
}

void Dealer::reset_hand() {
    hand.clear_hand();
}
