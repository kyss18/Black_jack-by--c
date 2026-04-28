#include "../include/saving.h"
#include"../include/Dealer.h"
#include"../include/Player.h"

void save_game(Balance balance,Dealer dealer,Player player){
    balance.after_playing=player.get_balance();
    Game game={balance,dealer,player};
    json j=game;
     cout << j.dump(4) << endl;
}

