#include "../include/service.h"
#include "../include/input.h"
#include"../include/saving.h"
#include <iostream>

using namespace std;

void show_card(Dealer dealer, Player player) {
    cout << "Dealer Cards: ";
    dealer.get_hand().show_all_card();
    cout << "\nYour Cards:";
    for (int i = 0; i < player.get_hands_size(); i++) {
        player.get_hand(i).show_all_card();
        cout << "Your score:" << player.get_hand(i).get_score() << endl;
    }
    cout << endl;
    cout << "Dealer score:" << dealer.get_hand().get_score() << endl;
}

void deal_initial_cards(Player& player, Deck& d, Dealer& dealer) {
    player.get_hand(0).add_card(d.draw());
    dealer.get_hand().add_card(d.draw());
    player.get_hand(0).add_card(d.draw());
    dealer.get_hand().add_card(d.draw());
}

bool check_blackjack(Dealer dealer, Player& player, int bet_amount) {
    if (dealer.get_hand().is_black_jack() && player.get_hand(0).is_black_jack()) {
        show_card(dealer, player);
        player.get_hand(0).set_result("tie");
        cout << "\nTie\n";
        if (player.get_insurance() >= 1) {
        cout << "\nLosing the insurance :((" << endl;
        player.take_balance(player.get_insurance());
        cout<<"Insurance take: "<<player.get_insurance();
    }
        return true;
    } else if (dealer.get_hand().is_black_jack()) {
        show_card(dealer, player);
        cout << "\nDealer win\n";
        player.take_balance(player.get_hand(0).get_bet());
        cout << "You lose hand: " << bet_amount<<endl;
        player.get_hand(0).set_result("lose");
        if (player.get_insurance() >= 1) {
            cout << "\nYou win the insurance\n";
            cout << "You got:" << player.get_insurance() << " from the insurance." << endl;
            player.set_balance(player.get_insurance() * 2);
        }
        return true;
    } else if (player.get_hand(0).is_black_jack()) {
        show_card(dealer, player);
        cout << "\nYou Win\n";
        player.get_hand(0).set_result("win");
        player.set_balance(bet_amount * 1.5);
        cout << "You got: " << bet_amount * 1.5 << endl;
        if (player.get_insurance() >= 1) {
            cout << "\nYou win the insurance\n";
            cout << "You got:" << player.get_insurance() << " from the insurance." << endl;
            player.set_balance(player.get_insurance() * 2);
        }
        return true;
    }
    return false;
}

void player_turn(Player& player, Deck& d, Dealer dealer, int betting_amount) {
    int i = 0;
    int split_count = 0;
    while (i < player.get_hands_size()) {
        int selection;
        if (player.get_hand(i).get_size_of_hand() == 1 &&
            (player.get_hand(i).get_card().name_card == "A")) {
            player.get_hand(i).add_card(d.draw());
            i++;
        } else {
            int hitOpt = 1;
            int standOpt = 2;
            int splitOpt = -1;
            int doubleOpt = -1;
            int surrOpt = -1;
            int option = 3;
            cout << "-----------------------------" << endl;
            cout << "Your balance: " << player.get_balance() << endl;
            cout << "Dealer card: ";
            cout << dealer.get_hand().get_card().name_card << " + ? " << endl;
            for (int j = 0; j < player.get_hands_size(); j++) {
                if (!player.get_hand(j).is_bust() && i == j) {
                    cout << "Hand " << j + 1 << "\tBet: " << player.get_hand(j).get_bet()
                         << "\t<------CURRENT\n";
                } else if (i < j) {
                    cout << "Hand " << j + 1 << "\tBet: " << player.get_hand(j).get_bet()
                         << "\tWaiting\n";
                } else if (i > j && !player.get_hand(j).is_bust()) {
                    if (player.get_hand(j).is_doubled_down()) cout << "*";
                    cout << "Hand " << j + 1 << "\tBet: " << player.get_hand(j).get_bet()
                         << "\tWaiting for the dealer turn\n";
                } else {
                    if (player.get_hand(j).is_doubled_down()) cout << "*";
                    cout << "Hand " << j + 1 << "\tBet: " << player.get_hand(j).get_bet()
                         << ": Bust\n";
                }
                player.get_hand(j).show_all_card();
                cout << "\nScore:" << player.get_hand(j).get_score();
                cout << endl;
            }
            cout << "\n-----------------------------" << endl;
            cout << "\tOptions:" << endl;
            cout << "\n1.Hit\n";
            cout << "2.Stand\n";
            if (player.get_hand(i).has_pair() &&
                (player.get_balance() > player.get_total_bet()) && split_count < 4 &&
                !(player.get_hand(i).get_bet() * 2 > player.get_balance())) {
                splitOpt = option;
                cout << option++ << ".Split\n";
            }
            if (player.get_hand(i).get_size_of_hand() == 2 && split_count == 0 &&
                player.get_hand(i).get_bet() != 0) {
                surrOpt = option;
                cout << option++ << ".Surrender\n";
            }
            if (player.can_double(i) && player.get_hand(i).get_size_of_hand() == 2 &&
                player.get_hand(i).get_bet() != 0) {
                doubleOpt = option;
                cout << option++ << ".Double\n";
            }
            if (player.get_hand(i).get_score() < 16)
                cout << "You should hit more\n";
            do {
                cout << "\nHand " << i + 1 << " chosing...\n";
                cout << "Your selection: ";
                cin >> selection;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    selection = -1;
                }
            } while (selection < 1 || selection > option);
            cout << "-----------------------------" << endl;

            if (selection == hitOpt) {
                player.get_hand(i).add_action("Hit");
                player.get_hand(i).add_card(d.draw());
                if (player.get_hand(i).is_bust() || player.get_hand(i).get_score() == 21)
                    i++;
                system("cls");
                cout << endl;
            } else if (selection == standOpt) {
                player.get_hand(i).add_action("Stand");
                i++;
                system("cls");
            } else if (selection == splitOpt) {
                player.split_hand(i, player.get_hand(i).get_bet());
                player.get_hand(i).add_action("Split");
                player.get_hand(i+1).add_action("Split");
                split_count++;
                system("cls");
            } else if (selection == doubleOpt) {
                player.get_hand(i).add_action("Double");
                player.get_hand(i).set_double_down();
                player.get_hand(i).add_card(d.draw());
                i++;
                system("cls");
            } else if (selection == surrOpt) {
                int option2;
                do {
                    cout << "Are you sure to surrender ?" << endl;
                    cout << "1.Yes\n";
                    cout << "2.No\n";
                    cout << "Your option:";
                    cin >> option2;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        option2 = -1;
                    }
                } while (option2 < 1 || option2 > 2);
                if (option2 == 1) {
                    system("cls");
                    player.set_surrendered();
                    player.get_hand(i).add_action("Surrender");
                    return;
                }
                system("cls");
            } else {
                system("cls");
            }
        }
    }
}

void dealer_turn(Dealer& dealer, Deck& d) {
    while (!(dealer.get_hand().get_score() >= 17)) {
        dealer.get_hand().add_card(d.draw());
        dealer.get_hand().add_action("Hit");
    }
    if(dealer.get_hand().get_score() <= 21)
    dealer.get_hand().add_action("Stand");
    else
    dealer.get_hand().add_action("Bust");
dealer.get_hand().is_bust();

}

void compare_result(Dealer dealer, Player& player, int bet_amount) {
    cout << "Summaries: \n";

    cout << "Starting balance:" << player.get_balance() << endl;
    cout << "Dealer cards:";
    dealer.get_hand().show_all_card();
    if (player.get_insurance() > 0) {
        cout << "\nLosing the insurance :((" << endl;
        player.take_balance(player.get_insurance());
        cout<<"Insurance take: "<<player.get_insurance();
    }
    cout << endl;
    for (int i = 0; i < player.get_hands_size(); i++) {
        if (dealer.get_hand().get_score() == player.get_hand(i).get_score() && !player.get_hand(i).is_bust()) {
            cout << "Your Cards: ";
            player.get_hand(i).show_all_card();
            cout << "\nHand " << i + 1 << ": ";
            player.get_hand(i).set_result("tie");
            cout << "\n\tTie\n";
            cout << "You earn: nothing :))" << endl;
            cout << "-----------------------------" << endl;
        } else if ((dealer.get_hand().get_score() > player.get_hand(i).get_score()) &&
                   !dealer.get_hand().is_bust()) {
            cout << "Your Cards: ";
            player.get_hand(i).show_all_card();
            cout << "\nHand " << i + 1 << ": ";
            if (player.get_hand(i).is_doubled_down()) {
                player.take_balance(player.get_hand(i).get_bet() * 2);
                cout << "You lose double: " << player.get_hand(i).get_bet();
                player.set_loss(player.get_hand(i).get_bet() * 2);
            } else {
                player.take_balance(player.get_hand(i).get_bet());
                cout << "You lose: " << player.get_hand(i).get_bet();
                player.set_loss(player.get_hand(i).get_bet());
            }
            player.get_hand(i).set_result("lose");
            cout << "\n-----------------------------" << endl;
        } else if ((dealer.get_hand().get_score() < player.get_hand(i).get_score()) &&
                   !player.get_hand(i).is_bust()) {
            cout << "Your Cards: ";
            player.get_hand(i).show_all_card();
            cout << "\nHand " << i + 1 << ": ";
            cout << "\n\tYou Win\n";
            if (player.get_hand(i).is_doubled_down()) {
                player.set_balance(player.get_hand(i).get_bet() * 2);
                cout << "You earn double: " << player.get_hand(i).get_bet() << " + "
                     << player.get_hand(i).get_bet() << endl;
                player.set_earn(player.get_hand(i).get_bet() * 2);
            } else {
                player.set_balance(player.get_hand(i).get_bet());
                cout << "You earn: " << player.get_hand(i).get_bet() << endl;
                player.set_earn(player.get_hand(i).get_bet());
            }
            player.get_hand(i).set_result("win");
            cout << "\n-----------------------------" << endl;
        } else if (player.get_hand(i).is_bust() ||
                   (player.get_hand(i).is_bust() && dealer.get_hand().is_bust())) {
            cout << "Your Cards: ";
            player.get_hand(i).show_all_card();
            cout << "\nHand " << i + 1 << ": ";
            cout << "\n\tYou Lose:\n";
            if (player.get_hand(i).is_doubled_down()) {
                player.take_balance(player.get_hand(i).get_bet() * 2);
                cout << "You lose double: " << player.get_hand(i).get_bet();
                player.set_loss(player.get_hand(i).get_bet() * 2);
            } else {
                player.take_balance(player.get_hand(i).get_bet());
                cout << "You lose: " << player.get_hand(i).get_bet();
                player.set_loss(player.get_hand(i).get_bet());
            }
            player.get_hand(i).set_result("lose");
        } else {
            cout << "Your Cards: ";
            player.get_hand(i).show_all_card();
            cout << "\nHand " << i + 1 << ": ";
            cout << "\n\tYou Win\n";
            if (player.get_hand(i).is_doubled_down()) {
                player.set_balance(player.get_hand(i).get_bet() * 2);
                cout << "You earn double: " << player.get_hand(i).get_bet() << " + "
                     << player.get_hand(i).get_bet() << endl;
                player.set_earn(player.get_hand(i).get_bet() * 2);
            } else {
                player.set_balance(player.get_hand(i).get_bet());
                cout << "You earn: " << bet_amount << endl;
                player.set_earn(player.get_hand(i).get_bet());
            }
            player.get_hand(i).set_result("win");
        }
         cout<<"\nYour action: [ ";
        for (string s:player.get_hand(i).get_action()){
           cout<<s<<" ";
        }
        cout << "]\n-----------------------------" << endl;
    }
    if (player.get_hands_size() > 1) {
        cout << "\nTotal earn:" << player.get_earn() << endl;
        cout << "\nTotal loss:" << player.get_loss() << endl;
        cout << "NET:" << player.get_net() << endl;
    }
    
}

void put_cards_back(Deck& d, Player& player, Dealer& dealer) {
    for (int i = 0; i < player.get_hands_size(); i++) {
        cout << "Hand " << i + 1 << ":\n";
        Hand& h_player = player.get_hand(i);
        for (int j = 0; j < h_player.get_size_of_hand(); j++) {
            card c = h_player.get_card(j);
            d.take_card_back(c);
        }
        h_player.clear_hand();
    }
    Hand& h_dealer = dealer.get_hand();
    for (int i = 0; i < h_dealer.get_size_of_hand(); i++) {
        card c = h_dealer.get_card(i);
        d.take_card_back(c);
    }
    h_dealer.clear_hand();
    
}

void play_game(Player& player) {
    Balance balance;
    balance.starting_balance=player.get_balance();
    Deck d;
    d.shuffle();
    Dealer dealer;
    while (true) {
        if (player.get_balance() > 0) {
            system("cls");
            Hand player_hand;
            player.reset_hand();
            dealer.get_hand().clear_hand();
            player.add_hand(player_hand);
            player.set_bet_amount(0);
            deal_initial_cards(player, d, dealer);
            int ask_continue;
            if (dealer.get_hand().get_card().name_card == "A" &&
                player.get_hand(0).get_bet() >= 2 &&
                (1 + player.get_hand(0).get_bet()) <= player.get_balance()) {
                int select;
                cout << "Dealer Card: " << dealer.get_hand().get_card().name_card
                     << " +  ? " << endl;
                do {
                    cout << "Would you like to buy insurance?\n";
                    cout << "1.Yes\n";
                    cout << "2.No\n";
                    cout << "Your option:";
                    cin >> select;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        select = -1;
                    }
                } while (select < 1 || select > 2);
                if (select == 1) {
                    int insurance_betting;
                    do {
                        cout << "How much would you like to pay for the insurane ?  (1"<<" < bet < "<< player.get_hand(0).get_bet()/2 << endl;
                        cout << "Betting:";
                        cin >> insurance_betting;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            insurance_betting = -1;
                        }
                    } while (insurance_betting < 1 ||
                             insurance_betting * 2 > player.get_hand(0).get_bet() ||
                             (insurance_betting + player.get_hand(0).get_bet()) >
                                 player.get_balance());
                    system("cls");
                    player.set_insurance(insurance_betting);
                }
            }
            if (check_blackjack(dealer, player, player.get_hand(0).get_bet())) {
                save_game(balance,dealer,player);
                if (!ask_user_for_continue(ask_continue, player)){
                    
                    return;
                }
                    
            } else {
                player_turn(player, d, dealer, player.get_hand(0).get_bet());
                if (!player.has_surrendered()) {
                    dealer_turn(dealer, d);
                    compare_result(dealer, player, player.get_hand(0).get_bet());
                } else {
                    cout << "You surrender\n";
                    cout << "You lose 50% money\n";
                    player.deduct_surrender_penalty();
                    //put_cards_back(d, player, dealer);
                }
                save_game(balance,dealer,player);
                if (ask_user_for_continue(ask_continue, player) == false){
                    
                    return;
                }
            }
        } else {
            cout << "-----------------------------" << endl;
            cout << "Please deposit more money" << endl;
            cout << "-----------------------------" << endl;
            save_game(balance,dealer,player);
            break;
        }
        put_cards_back(d, player, dealer);
    }
}
