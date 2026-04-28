#include "../include/Hand.h"

card Hand::get_card() {
    return hand[0];
}

card Hand::get_card(int i) {
    return hand[i];
}

int Hand::get_score() {
    return score;
}

void Hand::set_double_down() {
    this->is_doubling_down = true;
}
void Hand::set_result(string status){
    this->result=status;
}
string Hand::get_result(){
    return this->result;
}
bool Hand::is_doubled_down() {
    return is_doubling_down;
}

int Hand::get_size_of_hand() {
    return hand.size();
}

bool Hand::is_same_ace() {
    return (hand.size() == 2 && hand[0].value == hand[1].value);
}

void Hand::add_card(card c) {
    hand.push_back(c);
    score += c.value;
    if (c.name_card == "A")
        ace_count++;

    while (score > 21 && ace_count > 0) {
        score -= 10;
        ace_count--;
    }
}

void Hand::show_all_card() {
    for (auto x : hand) {
        cout << x.name_card << " " << x.type_card << " " << "|";
    }
}

bool Hand::is_bust() {
    if (score > 21)
        hand_is_bust = true;
    return hand_is_bust;
}

bool Hand::is_black_jack() {
    return hand.size() == 2 && ((hand[0].value == 10 && hand[1].value == 11) ||
           (hand[0].value == 11 && hand[1].value == 10));
}

void Hand::clear_hand() {
    hand.clear();
    action.clear();
    is_doubling_down = false;
    hand_is_bust = false;
    score = 0;
    ace_count = 0;
}

bool Hand::has_pair() {
    return hand.size() == 2 && (hand[0].value == hand[1].value);
}

card Hand::pop_card() {
    card c = hand.back();
      if (c.name_card == "A"){
        score -= 1; 
        ace_count--;
      }
    else
        score -= c.value;
    hand.pop_back();
    return c;
}
void Hand::add_action(string s){
    action.push_back(s);
}
void Hand::set_betting_amount(int amount) {
    this->betting_amount = amount;
}
const vector<string> Hand::get_action() const {
    return action;
}
int Hand::get_bet() {
    return betting_amount;
}
