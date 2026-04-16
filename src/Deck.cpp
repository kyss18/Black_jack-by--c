#include "../include/Deck.h"
#include <algorithm>
#include <random>

Deck::Deck() {
    need_shuffle = false;

    for (int d = 0; d < 3; d++) {
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

    initial_size = cards.size();
}

void Deck::shuffle() {
    random_device rd;
    mt19937 g(rd());
    shuffle(cards.begin(), cards.end(), g);
}

void Deck::show_card() {
    for (auto &c : cards) {
        cout << c.name_card << " " << c.type_card << endl;
    }
}

bool Deck::needs_shuffle() {
    return need_shuffle;
}

card Deck::draw() {
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