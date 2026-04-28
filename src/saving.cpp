#include "../include/saving.h"
#include"../include/Dealer.h"
#include"../include/Player.h"
#include"../include/APIclient.h"

void save_game(Balance balance,Dealer dealer,Player player){
    balance.after_playing=player.get_balance();
    Game game={balance,dealer,player};
    json j=game;
    string response = post("http://localhost:8080/save", j.dump());
    //file << j.dump(4) << endl;
    //file.close();
}

