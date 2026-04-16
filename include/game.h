#pragma once
#include "Player.h"
#include "Dealer.h"
#include "Deck.h"

void show_card(Dealer dealer, Player player);
void deal_initial_cards(Player& player, Deck& d, Dealer& dealer);
bool check_blackjack(Dealer dealer, Player& player, int bet_amount);
void player_turn(Player& player, Deck& d, Dealer dealer, int betting_amount);
void dealer_turn(Dealer& dealer, Deck& d);
void compare_result(Dealer dealer, Player& player, int bet_amount);
void put_cards_back(Deck& d, Player& player, Dealer& dealer);
void play_game(Player& player);
