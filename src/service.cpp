#include "../include/service.h"
#include "../include/input.h"
#include"../include/saving.h"
#include <iostream>

using namespace std;

void show_card(Dealer dealer, Player player) {
    string thick = "========================================";
string thin  = "----------------------------------------";

cout << "\n  " << thick << "\n";
cout << "  |         C A R D   T A B L E           |\n";
cout << "  " << thick << "\n";
cout << "  |  DEALER                               |\n";
cout << "  " << thin << "\n";
cout << "  |  Cards : ";
dealer.get_hand().show_all_card();
printf("  |  Score : %-29d|\n", dealer.get_hand().get_score());
cout << "  " << thick << "\n";
cout << "  |  PLAYER                               |\n";
cout << "  " << thin << "\n";

for (int i = 0; i < player.get_hands_size(); i++) {
    printf("  |  Hand #%d                              |\n", i + 1);
    cout << "  |  Cards : ";
    player.get_hand(i).show_all_card();
    printf("  |  Score : %-29d|\n", player.get_hand(i).get_score());
    if (i < player.get_hands_size() - 1)
        cout << "  " << thin << "\n";
}

cout << "  " << thick << "\n";
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
         cout << "\n  ================================\n";
    cout << "  |         T I E  !              |\n";
    cout << "  |  Both have Blackjack!         |\n";
    cout << "  ================================\n";
        if (player.get_insurance() >= 1) {
        cout << "  --------------------------------\n";
         printf("  |  Insurance lost : $%-9d|\n", player.get_insurance());
         cout << "  --------------------------------\n";
        player.take_balance(player.get_insurance());
        cout<<"Insurance take: "<<player.get_insurance();
    }
        return true;
    } else if (dealer.get_hand().is_black_jack()) {
        show_card(dealer, player);
player.take_balance(player.get_hand(0).get_bet());
player.get_hand(0).set_result("lose");

cout << "\n  ================================\n";
cout << "  |       D E A L E R  W I N      |\n";
cout << "  --------------------------------\n";
printf("  |  You lost : $%-15d|\n", bet_amount);
cout << "  ================================\n";

if (player.get_insurance() >= 1) {
    player.set_balance(player.get_insurance() * 2);
    cout << "  --------------------------------\n";
    cout << "  |  Insurance WON!               |\n";
    printf("  |  You got  : $%-15d|\n", player.get_insurance());
    cout << "  --------------------------------\n";
}
        return true;
    } else if (player.get_hand(0).is_black_jack()) {
       show_card(dealer, player);
player.get_hand(0).set_result("win");
player.set_balance(bet_amount * 1.5);

cout << "\n  ================================\n";
cout << "  |     B L A C K J A C K !       |\n";
cout << "  |       Y O U   W I N !         |\n";
cout << "  --------------------------------\n";
printf("  |  You won  : $%-15.1f|\n", bet_amount * 1.5);
cout << "  ================================\n";

if (player.get_insurance() >= 1) {
    player.set_balance(player.get_insurance() * 2);
    cout << "  --------------------------------\n";
    cout << "  |  Insurance WON!               |\n";
    printf("  |  You got  : $%-15d|\n", player.get_insurance());
    cout << "  --------------------------------\n";
}
        return true;
    }
    return false;
}

void player_turn(Player& player, Deck& d, Dealer dealer, int betting_amount) {
    int i = 0;
    int split_count = 0;
    string thick = "========================================";
    string thin  = "----------------------------------------";

    while (i < player.get_hands_size()) {
        int selection;
        if (player.get_hand(i).get_size_of_hand() == 1 &&
            (player.get_hand(i).get_card().name_card == "A")) {
            player.get_hand(i).add_card(d.draw());
            i++;
        } else {
            int hitOpt = 1, standOpt = 2, splitOpt = -1;
            int doubleOpt = -1, surrOpt = -1, option = 3;

            system("cls");
            cout << "\n  " << thick << "\n";
            cout << "  |          P L A Y E R   T U R N        |\n";
            cout << "  " << thick << "\n";
            printf("  |  Balance : $%-26.1f|\n", player.get_balance());
            printf("  |  Dealer  : %-27s|\n",
                   (dealer.get_hand().get_card().name_card + " + ?").c_str());
            cout << "  " << thin << "\n";

            // show all hands
            for (int j = 0; j < player.get_hands_size(); j++) {
                string status = "";
                if (i == j && !player.get_hand(j).is_bust())
                    status = "<-- CURRENT";
                else if (i < j)
                    status = "Waiting";
                else if (i > j && !player.get_hand(j).is_bust())
                    status = player.get_hand(j).is_doubled_down() ? "Done *" : "Done";
                else
                    status = player.get_hand(j).is_doubled_down() ? "BUST *" : "BUST";

                printf("  |  Hand %d | Bet: $%-5d | %-14s|\n",
                       j + 1,
                       player.get_hand(j).get_bet(),
                       status.c_str());

                // show cards inline
                cout << "  |  Cards : ";
                player.get_hand(j).show_all_card();
                printf("  |  Score : %-30d|\n", player.get_hand(j).get_score());

                if (j < player.get_hands_size() - 1)
                    cout << "  " << thin << "\n";
            }

            cout << "  " << thick << "\n";
            cout << "  |            O P T I O N S              |\n";
            cout << "  " << thin << "\n";
            cout << "  |  [1]  Hit                             |\n";
            cout << "  |  [2]  Stand                           |\n";

            if (player.get_hand(i).has_pair() &&
                player.get_balance() > player.get_total_bet() &&
                split_count < 4 &&
                !(player.get_hand(i).get_bet() * 2 > player.get_balance())) {
                splitOpt = option;
                printf("  |  [%d]  Split                           |\n", option++);
            }
            if (player.get_hand(i).get_size_of_hand() == 2 &&
                split_count == 0 &&
                player.get_hand(i).get_bet() != 0) {
                surrOpt = option;
                printf("  |  [%d]  Surrender                       |\n", option++);
            }
            if (player.can_double(i) &&
                player.get_hand(i).get_size_of_hand() == 2 &&
                player.get_hand(i).get_bet() != 0) {
                doubleOpt = option;
                printf("  |  [%d]  Double Down                     |\n", option++);
            }

            if (player.get_hand(i).get_score() < 16) {
                cout << "  " << thin << "\n";
                cout << "  |  * Tip: Score < 16, consider Hit      |\n";
            }

            cout << "  " << thick << "\n";

            do {
                printf("  Hand %d your selection: ", i + 1);
                cin >> selection;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "  [!] Invalid input.\n";
                    selection = -1;
                }
            } while (selection < 1 || selection > option);

            if (selection == hitOpt) {
                player.get_hand(i).add_action("Hit");
                player.get_hand(i).add_card(d.draw());
                if (player.get_hand(i).is_bust() || player.get_hand(i).get_score() == 21)
                    i++;

            } else if (selection == standOpt) {
                player.get_hand(i).add_action("Stand");
                i++;

            } else if (selection == splitOpt) {
                player.split_hand(i, player.get_hand(i).get_bet());
                player.get_hand(i).add_action("Split");
                player.get_hand(i + 1).add_action("Split");
                split_count++;

            } else if (selection == doubleOpt) {
                player.get_hand(i).add_action("Double");
                player.get_hand(i).set_double_down();
                player.get_hand(i).add_card(d.draw());
                i++;

            } else if (selection == surrOpt) {
                int option2;
                system("cls");
                cout << "\n  " << thick << "\n";
                cout << "  |          S U R R E N D E R ?          |\n";
                cout << "  " << thin << "\n";
                cout << "  |  You will get back half your bet      |\n";
                cout << "  " << thin << "\n";
                cout << "  |  [1]  Yes                             |\n";
                cout << "  |  [2]  No                              |\n";
                cout << "  " << thick << "\n";

                do {
                    cout << "  Your option: ";
                    cin >> option2;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        option2 = -1;
                    }
                } while (option2 < 1 || option2 > 2);

                if (option2 == 1) {
                    player.set_surrendered();
                    player.get_hand(i).add_action("Surrender");
                    cout << "  " << thin << "\n";
                    cout << "  |  Surrendered!                         |\n";
                    cout << "  " << thick << "\n";
                    return;
                }
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
    string thick = "========================================";
    string thin  = "----------------------------------------";

    system("cls");
    cout << "\n  " << thick << "\n";
    cout << "  |           S U M M A R Y               |\n";
    cout << "  " << thick << "\n";
    printf("  |  Balance  : $%-25.1f|\n", player.get_balance());
    cout << "  |  Dealer   : ";
    dealer.get_hand().show_all_card();
    printf("  |  Score    : %-26d|\n", dealer.get_hand().get_score());

    if (player.get_insurance() > 0) {
        cout << "  " << thin << "\n";
        cout << "  |  Insurance LOST                       |\n";
        printf("  |  Lost     : $%-25d|\n", player.get_insurance());
        player.take_balance(player.get_insurance());
    }

    cout << "  " << thick << "\n";

    for (int i = 0; i < player.get_hands_size(); i++) {
        printf("  |  Hand #%d                              |\n", i + 1);
        cout << "  |  Cards : ";
        player.get_hand(i).show_all_card();
        printf("  |  Score : %-29d|\n", player.get_hand(i).get_score());

        // actions
        string actions = "";
        for (string s : player.get_hand(i).get_action())
            actions += s + " ";
        printf("  |  Actions: %-28s|\n", actions.c_str());

        cout << "  " << thin << "\n";

        // TIE
        if (dealer.get_hand().get_score() == player.get_hand(i).get_score() &&
            !player.get_hand(i).is_bust()) {
            player.get_hand(i).set_result("tie");
            cout << "  |  Result  : TIE                        |\n";
            cout << "  |  Earn    : nothing :))                |\n";

        // DEALER WIN
        } else if ((dealer.get_hand().get_score() > player.get_hand(i).get_score()) &&
                   !dealer.get_hand().is_bust()) {
            player.get_hand(i).set_result("lose");
            int loss = player.get_hand(i).is_doubled_down()
                       ? player.get_hand(i).get_bet() * 2
                       : player.get_hand(i).get_bet();
            player.take_balance(loss);
            player.set_loss(loss);
            cout << "  |  Result  : LOSE                       |\n";
            printf("  |  Lost    : $%-26d|\n", loss);
            if (player.get_hand(i).is_doubled_down())
                cout << "  |  (Double Down)                        |\n";

        // PLAYER BUST
        } else if (player.get_hand(i).is_bust()) {
            player.get_hand(i).set_result("lose");
            int loss = player.get_hand(i).is_doubled_down()
                       ? player.get_hand(i).get_bet() * 2
                       : player.get_hand(i).get_bet();
            player.take_balance(loss);
            player.set_loss(loss);
            cout << "  |  Result  : BUST - LOSE                |\n";
            printf("  |  Lost    : $%-26d|\n", loss);

        // PLAYER WIN
        } else {
            player.get_hand(i).set_result("win");
            int earn = player.get_hand(i).is_doubled_down()
                       ? player.get_hand(i).get_bet() * 2
                       : player.get_hand(i).get_bet();
            player.set_balance(earn);
            player.set_earn(earn);
            cout << "  |  Result  : WIN !                      |\n";
            printf("  |  Earned  : $%-26d|\n", earn);
            if (player.get_hand(i).is_doubled_down())
                cout << "  |  (Double Down)                        |\n";
        }

        cout << "  " << thick << "\n";
    }

    // MULTI HAND SUMMARY
    if (player.get_hands_size() > 1) {
        cout << "  |          T O T A L S                  |\n";
        cout << "  " << thin << "\n";
        printf("  |  Total Earn : $%-23.1f|\n", player.get_earn());
        printf("  |  Total Loss : $%-23.1f|\n", player.get_loss());
        printf("  |  NET        : $%-23.1f|\n", player.get_net());
        cout << "  " << thick << "\n";
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
                    string thick = "========================================";
                    string thin  = "----------------------------------------";

                    cout << "\n  " << thick << "\n";
                    cout << "  |           I N S U R A N C E           |\n";
                    cout << "  " << thick << "\n";
                    cout << "  |  Dealer has an Ace!                   |\n";
                    cout << "  |  Buy insurance? (costs half your bet) |\n";
                    cout << "  " << thin << "\n";
                    cout << "  |  [1]  Yes                             |\n";
                    cout << "  |  [2]  No                              |\n";
                    cout << "  " << thick << "\n";
                    cout << "  Your option: ";
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
                       string thick = "========================================";
        string thin  = "----------------------------------------";

            cout << "\n  " << thick << "\n";
cout << "  |        I N S U R A N C E   B E T      |\n";
cout << "  " << thick << "\n";
printf("  |  Max insurance : $%-20d|\n", player.get_hand(0).get_bet() / 2);
printf("  |  Min insurance : $%-20d|\n", 1);
cout << "  " << thin << "\n";
cout << "  |  Enter amount between 1 and max       |\n";
cout << "  " << thick << "\n";
cout << "  Your insurance: $";
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
                    cout << "\n  ================================\n";
                    cout << "  |       S U R R E N D E R       |\n";
                    cout << "  --------------------------------\n";
                    printf("  |  You lost : $%-15.1f|\n", player.get_hand(0).get_bet() * 0.5);
                    cout << "  |  50% of your bet returned     |\n";
                    cout << "  ================================\n";
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
