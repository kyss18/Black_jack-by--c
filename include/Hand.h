#pragma once
#include <vector>
#include <iostream>
#include "card.h"


using namespace std;

class Hand {
private:
    vector<card> hand;
    vector <string> action;
    int score = 0;
    int ace_count = 0;
    int betting_amount = 0;
    bool is_doubling_down = false;
    bool hand_is_bust = false;
    string result;
public:
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(Hand, hand, action, score, betting_amount, is_doubling_down, hand_is_bust,result)
    card get_card();
    card get_card(int i);
    int get_score();
    const vector<string> get_action() const;
    void set_double_down();
    void set_result(string status);
    string get_result();
    bool is_doubled_down();
    int get_size_of_hand();
    bool is_same_ace();
    void add_card(card c);
    void show_all_card();
    bool is_bust();
    bool is_black_jack();
    void clear_hand();
    bool has_pair();
    card pop_card();
    void set_betting_amount(int amount);
    int get_bet();
    void add_action(string s);
};
