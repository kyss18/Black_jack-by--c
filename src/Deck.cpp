#include "../include/Deck.h"
#include <algorithm>
#include <random>
using namespace std;
Deck::Deck() {
    need_shuffle = false;

    for (int d = 0; d < 3; d++)     
     {
        for (auto& suit : suits) {
            for (auto& rank : ranks) {

                int value;

                if (rank == "A") value = 11;
                else if (rank == "J" || rank == "Q" || rank == "K") value = 10;
                else value = stoi(rank);

                cards.push_back({rank, suit, value});
            }
        }
    }
    //SPLIT (A + A)
//     cards.push_back({"4",  "Clubs",    4});   // dealer hit (5+8=13 < 17, hit thêm)
// cards.push_back({"K",  "Spades",  10});   // hand 2 lá 2 (sau split)
// cards.push_back({"K",  "Clubs",   10});   // hand 1 lá 2 (sau split)
// cards.push_back({"8",  "Hearts",   8});   // dealer lá 2
// cards.push_back({"A",  "Spades",  11});   // player lá 2
// cards.push_back({"5",  "Diamonds", 5});   // dealer lá 1
// cards.push_back({"A",  "Clubs",   11});   // player lá 1   // player lá 1
    //Double
    // cards.push_back({"9", "Hearts", 9});    // dealer lá 2
    // cards.push_back({"6", "Spades", 6});    // player lá 2
    // cards.push_back({"7", "Diamonds", 7});  // dealer lá 1
    // cards.push_back({"5", "Clubs", 5});     // player lá 1
    // cards.push_back({"9", "Hearts", 9});    // dealer lá 2
    // cards.push_back({"6", "Spades", 6});    // player lá 2
    // cards.push_back({"7", "Diamonds", 7});  // dealer lá 1
    // cards.push_back({"5", "Clubs", 5});     // player lá 1
    //Player blackjack
//     cards.push_back({"5",  "Hearts",   5});
// cards.push_back({"6",  "Diamonds", 6});
//     cards.push_back({"8",  "Diamonds", 8});   // dealer card 2  [draw 4]
// cards.push_back({"K",  "Clubs",   10});   // player card 2  [draw 3]
// cards.push_back({"9",  "Hearts",   9});   // dealer card 1  [draw 2]
// cards.push_back({"A",  "Spades",  11});   // player card 1  [draw 1]
//Tie
    // cards.push_back({"5",  "Hearts",   5});   // extra
    // cards.push_back({"6",  "Diamonds", 6});   // extra
    // cards.push_back({"8",  "Hearts",   8});   // dealer card 2  [draw 4]
    // cards.push_back({"9",  "Clubs",    9});   // player card 2  [draw 3]
    // cards.push_back({"10", "Diamonds",10});   // dealer card 1  [draw 2]
    // cards.push_back({"9",  "Spades",   9});   // player card 1  [draw 1]
// extra dealer hit if needed

    initial_size = cards.size();
}

void Deck::shuffle() {
    random_device rd;
    mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

void Deck::show_card() {
    for (auto &c : cards) {
        cout << c.name_card << " " << c.type_card << endl;
    }
}

card Deck::draw() {
    if (need_shuffle) {
         cards.insert(cards.end(), discard_tray.begin(), discard_tray.end());
        discard_tray.clear();
        initial_size = cards.size();
        need_shuffle = false;
        random_device rd;
        mt19937 g(rd());
        std::shuffle(cards.begin(), cards.end(), g);
    }
    card c = cards.back();
    cards.pop_back();

    if (cards.size() < initial_size * 0.25) {
        need_shuffle = true;
    }

    return c;
}

void Deck::take_card_back(card card) {
    discard_tray.push_back(card);
}

void Deck::show_tray() {
    for (auto &x : discard_tray) {
        cout << x.name_card << " ";
    }
    cout << endl;
}

void Deck::merge() {
    cards.insert(cards.end(), discard_tray.begin(), discard_tray.end());
    discard_tray.clear();
    initial_size = cards.size();
    need_shuffle = false;
}