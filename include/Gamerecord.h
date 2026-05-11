#pragma once
#include <string>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

struct RecordCard {
    string name_card;
    string type_card;
};

struct RecordHand {
    vector<string> action;
    int betting_amount;
    vector<RecordCard> hand;
    bool hand_is_bust;
    bool is_doubling_down;
    string result;
    int score;
};

struct RecordDealer {
    RecordHand hand;
};

struct RecordPlayer {
    double balance;
    vector<RecordHand> hand;
    double insurance;
    bool surrender;
    double totalearn;
    double totalloss;
};

struct RecordBalance {
    double after_playing;
    double starting_balance;
};

struct RecordGame {
    RecordBalance balance;
    RecordDealer dealer;
    RecordPlayer player;
};

struct GameRecord {
    string createdAt;
    string gameSession;
    int id;
    RecordGame jsonData;
};

void from_json(const json& j, RecordCard& c);
void from_json(const json& j, RecordHand& h);
void from_json(const json& j, RecordDealer& d);
void from_json(const json& j, RecordPlayer& p);
void from_json(const json& j, RecordBalance& b);
void from_json(const json& j, RecordGame& g);
void from_json(const json& j, GameRecord& r);