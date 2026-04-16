#pragma once
#include "card.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Deck {
private:
  vector<card> cards;
  vector<card> discard_tray;
  int initial_size;
  bool need_shuffle;

  vector<string> suits = {"Hearts", "Diamonds", "Clubs", "Spades"};
  vector<string> ranks = {"A", "2", "3",  "4", "5", "6", "7",
                          "8", "9", "10", "J", "Q", "K"};

public:
  Deck();

  void shuffle();
  void show_card();
  bool needs_shuffle();
  card draw();
  void take_card_back(card card);
  void show_tray();
  void merge();
};