#include "../include/saving.h"
#include"../include/Dealer.h"
#include"../include/Player.h"
#include"../include/APIclient.h"
#include<iostream>

void save_game(Balance balance,Dealer dealer,Player player){
    balance.after_playing=player.get_balance();
    Game game={balance,dealer,player};
    json j=game;
    string response = post("http://localhost:8080/save", j.dump());
    if (response.empty()) { 
        cout << "Failed to save" << endl; 
        return; 
    }
    else {
        cout<<"History saved success "<<endl;
    }
    //file << j.dump(4) << endl;
    //file.close();
}

