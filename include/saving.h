#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "Dealer.h"
#include "Player.h"
#include"service.h"
using json = nlohmann::json;
using namespace std;

typedef struct Game {
    Balance balance;
    Dealer dealer;
    Player player;
} Game;

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Game, balance, player, dealer)
void save_game(Balance balance,Dealer dealer, Player player);
void save_json(Game game );

