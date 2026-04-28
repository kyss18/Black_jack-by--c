#include "../include/input.h"
#include "../include/service.h"
#include "../include/APIclient.h"
#include "../include/json.hpp"

#include <iostream>
using json = nlohmann::json;
using namespace std;

bool ask_user_for_continue(int& selection, Player player) {
    cout << "Your Balance:" << player.get_balance() << endl;
    cout << "Do you want to continue?\n";
    cout << "1. Yes\n";
    cout << "(Any number). Back to menu\n";
    cout << "Your choice: ";
    cin >> selection;
    if (selection == 1)
        return true;
    return false;
}

void deposit(Player& player) {
    double amount;
    cout << "Press \"-1\" to cancel deposit\n";
    do {
        cout << "How much would you like to deposit : ";
        cin >> amount;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            amount = 0;
        }
    } while (amount < -1 || amount == 0);
    if (amount > 0) {
        int choose;
        do {
            cout << "Confirm deposit of $" << amount << " to your account? \n";
            cout << "1.Of course\n";
            cout << "2.No\n";
            cout << "Your option:";
            cin >> choose;
             if (cin.fail()) {
            cin.clear();            // reset trạng thái lỗi
            cin.ignore(1000, '\n'); // bỏ input rác trong buffer
            choose = 0;             // reset về giá trị invalid để loop tiếp
    }
        } while (choose < 1 || choose > 2);
        if (choose == 1) {
            player.add_balance(amount);
            cout << "You deposited $" << amount << " successfully\n";
        } else {
            cout << "You canceled deposit\n";
        }
    } else {
        cout << "You canceled deposit\n";
    }
}

void show_menu() {
    cout << fixed;
    cout.precision(0);
    int balance;
    int choose_menu;
    do {
        cout << "Input your balance: ";
        cin >> balance;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            balance = 0;
        }
    } while (balance <= 0);
    Player player(balance);
    while (true) {
        cout << "\n===== BLACKJACK =====\n";
        cout << "Balance: $" << player.get_balance() << endl;
        cout << "1. Play blackjack\n";
        cout << "2. History\n";
        cout << "5. Deposit\n";
        cout << "6. Check Balance\n";
        cout << "9. Exit\n";
        cout << "Your option: ";
        cin >> choose_menu;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            choose_menu = -1;
        }
        switch (choose_menu) {
            case 1: {
                system("cls");
                play_game(player);
                
            } break;
            case 2:
            {
                 // GET
            string history = get("http://localhost:8080/history");
            json j = json::parse(history);
            cout << j.dump(4) << endl;  
            }
                break;
            case 3:
                cout << "To be continue\n";
                break;
            case 4:
                cout << "To be continue\n";
                break;
            case 5: {
                deposit(player);
            } break;
            case 6: {
                cout << "\n-----------------------------\n" << endl;
                cout << "Your balance:" << player.get_balance() << "$" << endl;
                cout << "\n-----------------------------\n" << endl;
            } break;
            case 7:
                cout << "To be continue\n";
                break;
            case 8:
                cout << "To be continue\n";
                break;
            case 9:
                return;
            default:
                system("cls");
                break;
        }
    }
}
