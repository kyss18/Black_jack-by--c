#pragma once
#include "Hand.h"

class Dealer {
private:
    Hand hand;
public:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Dealer, hand)
    Hand& get_hand();
    void reset_hand();
};
