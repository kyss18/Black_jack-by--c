#include "GameRecord.h"

void from_json(const json& j, RecordCard& c) {
    j.at("name_card").get_to(c.name_card);
    j.at("type_card").get_to(c.type_card);
}

void from_json(const json& j, RecordHand& h) {
    j.at("action").get_to(h.action);
    j.at("betting_amount").get_to(h.betting_amount);
    j.at("hand").get_to(h.hand);
    j.at("hand_is_bust").get_to(h.hand_is_bust);
    j.at("is_doubling_down").get_to(h.is_doubling_down);
    j.at("result").get_to(h.result);
    j.at("score").get_to(h.score);
}

void from_json(const json& j, RecordDealer& d) {
    j.at("hand").get_to(d.hand);
}

void from_json(const json& j, RecordPlayer& p) {
    j.at("balance").get_to(p.balance);
    j.at("hand").get_to(p.hand);
    j.at("insurance").get_to(p.insurance);
    j.at("surrender").get_to(p.surrender);
    j.at("totalearn").get_to(p.totalearn);
    j.at("totalloss").get_to(p.totalloss);
}

void from_json(const json& j, RecordBalance& b) {
    j.at("after_playing").get_to(b.after_playing);
    j.at("starting_balance").get_to(b.starting_balance);
}

void from_json(const json& j, RecordGame& g) {
    j.at("balance").get_to(g.balance);
    j.at("dealer").get_to(g.dealer);
    j.at("player").get_to(g.player);
}

void from_json(const json& j, GameRecord& r) {
    j.at("id").get_to(r.id);
    j.at("createdAt").get_to(r.createdAt);
    j.at("gameSession").get_to(r.gameSession);
    j.at("jsonData").get_to(r.jsonData);
}