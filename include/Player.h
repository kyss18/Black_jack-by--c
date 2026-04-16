#pragma once
#include <vector>
#include <iostream>
#include "Hand.h"

using namespace std;

class Player {
private:
    vector<Hand> hand;
    int total_bet;
    int insurance = 0;
    bool surrender = false;
    double balance;
    int totalloss = 0;
    int totalearn = 0;
public:
    Player(double balance);
    Hand& get_hand(int i);
    void set_bet_amount(int i);
    void reset_hand();
    void set_balance(int bet_amount);
    void take_balance(int bet_amount);
    void deduct_surrender_penalty();
    void add_balance(int bet_amount);
    double get_balance();
    int get_total_bet();
    void add_hand(Hand& new_hand);
    int get_hands_size();
    void split_hand(int i, int money);
    bool can_double(int i);
    void set_insurance(int insurance_betting);
    int get_insurance();
    void set_surrendered();
    bool has_surrendered();
    void set_loss(int loss);
    void set_earn(int win);
    int get_loss();
    int get_earn();
    int get_net();
};
