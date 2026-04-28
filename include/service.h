#pragma once
#include "Player.h"
#include "Dealer.h"
#include "Deck.h"
typedef struct Balance{
    double starting_balance;
    double after_playing;
}Balance;
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Balance,starting_balance , after_playing);
void show_card(Dealer dealer, Player player);
void deal_initial_cards(Player& player, Deck& d, Dealer& dealer);
bool check_blackjack(Dealer dealer, Player& player, int bet_amount);
void player_turn(Player& player, Deck& d, Dealer dealer, int betting_amount);
void dealer_turn(Dealer& dealer, Deck& d);
void compare_result(Dealer dealer, Player& player, int bet_amount);
void put_cards_back(Deck& d, Player& player, Dealer& dealer);
void play_game(Player& player);
