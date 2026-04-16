#pragma once
#include "Hand.h"

class Dealer {
private:
    Hand hand;
public:
    Hand& get_hand();
    void reset_hand();
};
