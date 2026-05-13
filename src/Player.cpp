#include "../include/Player.h"

Player::Player(double balance) {
    this->balance = balance;
}

Hand& Player::get_hand(int i) {
    return hand[i];
}

void Player::set_bet_amount(int i) {
     string thick = "========================================";
    string thin  = "----------------------------------------";
    int bet_amount;

    cout << "\n  " << thick << "\n";
    cout << "  |            P L A C E   B E T          |\n";
    cout << "  " << thick << "\n";
    printf("  |  Balance : $%-26.1f|\n", balance);
    cout << "  " << thick << "\n";

    do {
        cout << "  Your bet: $";
        cin >> bet_amount;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  [!] Invalid input. Please enter a number.\n";
            bet_amount = -1;
        } else if (bet_amount < 0) {
            cout << "  [!] Bet cannot be negative.\n";
        } else if (bet_amount > balance) {
            printf("  [!] Insufficient balance. Max bet: $%.1f\n", balance);
        }

    } while (bet_amount < 0 || bet_amount > balance);

    cout << "  " << thin << "\n";
    printf("  |  Bet placed: $%-24d|\n", bet_amount);
    cout << "  " << thick << "\n";

    hand[i].set_betting_amount(bet_amount);
}


void Player::reset_hand() {
    hand.clear();
    surrender = false;
    insurance = 0;
    totalloss = 0;
    totalearn = 0;
}

void Player::set_balance(int bet_amount) {
    balance += bet_amount;
}

void Player::take_balance(int bet_amount) {
    balance -= bet_amount;
}

void Player::deduct_surrender_penalty() {
    this->balance = this->balance - (hand[0].get_bet() / 2);
}

void Player::add_balance(int bet_amount) {
    balance += bet_amount;
}

double Player::get_balance() {
    return balance;
}

int Player::get_total_bet() {
    int sum = 0;
    for (int i = 0; i < (int)hand.size(); i++) {
        sum += hand[i].get_bet();
    }
    return sum;
}

void Player::add_hand(Hand& new_hand) {
    this->hand.push_back(new_hand);
}

int Player::get_hands_size() {
    return hand.size();
}

void Player::split_hand(int i, int money) {
    Hand new_hand;
    new_hand.add_card(hand[i].pop_card());
    new_hand.set_betting_amount(money);
    hand.insert(hand.begin() + i + 1, new_hand);
}

bool Player::can_double(int i) {
    return hand[i].get_bet() * 2 <= balance;
}

void Player::set_insurance(int insurance_betting) {
    this->insurance = insurance_betting;
}

int Player::get_insurance() {
    return insurance;
}

void Player::set_surrendered() {
    this->surrender = true;
}

bool Player::has_surrendered() {
    return surrender;
}

void Player::set_loss(int loss) {
    this->totalloss += loss;
}

void Player::set_earn(int win) {
    this->totalearn += win;
}

int Player::get_loss() {
    return totalloss;
}

int Player::get_earn() {
    return totalearn;
}

int Player::get_net() {
    return totalearn - totalloss;
}
