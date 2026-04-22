#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ── Struct ───────────────────────────────────────────────────────────────────
struct HandInfo {
    int    hand_index;
    string cards;
    int    score;
    string result;
    bool   bust;
    bool   is_double;
    string actions;
};

// ── Helper ───────────────────────────────────────────────────────────────────
vector<string> splitStr(const string& s, const string& delim) {
    vector<string> tokens;
    size_t start = 0, pos;
    while ((pos = s.find(delim, start)) != string::npos) {
        tokens.push_back(s.substr(start, pos - start));
        start = pos + delim.size();
    }
    tokens.push_back(s.substr(start));
    return tokens;
}

string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t");
    size_t end   = s.find_last_not_of(" \t");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}

// ── Parse ────────────────────────────────────────────────────────────────────
HandInfo parseHand(const string& block) {
    HandInfo h;
    h.bust = false; h.is_double = false;

    string s = block;
    if (s.front() == '[') s = s.substr(1);
    if (s.back()  == ']') s = s.substr(0, s.size() - 1);

    auto parts = splitStr(s, " | ");
    for (auto& part : parts) {
        part = trim(part);
        if      (part.find("hand")    == 0) { size_t c = part.find(": "); h.hand_index = stoi(part.substr(4, c-4)); h.cards = part.substr(c+2); }
        else if (part.find("score:")  == 0) { h.score   = stoi(part.substr(6)); }
        else if (part.find("actions:")== 0) { h.actions = part.substr(8);       }
        else if (part == "BUST")            { h.bust      = true;               }
        else if (part == "DOUBLE")          { h.is_double = true;               }
        else                                { h.result    = part;               }
    }
    return h;
}

vector<HandInfo> parsePlayerHands(const string& str) {
    vector<HandInfo> hands;
    auto blocks = splitStr(str, "]  [");
    for (size_t i = 0; i < blocks.size(); i++) {
        string b = trim(blocks[i]);
        if (b.front() != '[') b = "[" + b;
        if (b.back()  != ']') b = b + "]";
        hands.push_back(parseHand(b));
    }
    return hands;
}

// ── In dealer cards ───────────────────────────────────────────────────────────
void printDealerCards(const string& dealer_cards) {
    cout << "Dealer Cards: ";
    auto cards = splitStr(dealer_cards, ",");
    for (auto& c : cards) {
        size_t dash = c.find('-');
        cout << c.substr(0, dash) << " " << c.substr(dash+1) << " |";
    }
    cout << endl;
}

// ── In player hands ───────────────────────────────────────────────────────────
void printPlayerHands(const string& player_hands_str) {
    auto hands = parsePlayerHands(player_hands_str);
    for (auto& h : hands) {
        cout << "Your Cards: ";
        auto card_list = splitStr(h.cards, ",");
        for (auto& c : card_list) {
            size_t dash = c.find('-');
            cout << c.substr(0, dash) << " " << c.substr(dash+1) << " |";
        }
        cout << endl;

        cout << "Hand " << h.hand_index << ":" << endl;
        if      (h.result == "win")       { cout << "\tYou Win";       if (h.is_double) cout << " (Double!)"; cout << endl; }
        else if (h.result == "blackjack") { cout << "\tBlackjack!!\n"; }
        else if (h.result == "lose")      { cout << "\tYou Lose";      if (h.bust) cout << " (Bust!)"; if (h.is_double) cout << " (Double!)"; cout << endl; }
        else if (h.result == "push")      { cout << "\tTie\n";         }
        else if (h.result == "surrender") { cout << "\tSurrender\n";   }

        cout << "Score  : " << h.score   << endl;
        cout << "Actions: " << h.actions << endl;
        cout << "-----------------------------" << endl;
    }
}

// ── In 1 session hoàn chỉnh ───────────────────────────────────────────────────
void printSession(
    int    id,
    string date,         string time,
    float  bal_before,   float  bal_after,
    float  total_bet,    float  total_earn,  float total_loss,
    int    ins_taken,    float  ins_bet,     string ins_result,
    string dealer_cards, int    dealer_score,
    string player_hands)
{
    cout << "\n============================================" << endl;
    cout <<   " Session #" << id << "  |  " << date << "  " << time        << endl;
    cout <<   " Balance : " << bal_before << " -> " << bal_after
             << "  (" << (bal_after - bal_before) << ")"                    << endl;
    cout <<   " Bet     : " << total_bet
             << "  Earn: "  << total_earn
             << "  Loss: "  << total_loss                                   << endl;

    if (ins_taken) {
        cout << " Insurance: $" << ins_bet << " -> " << ins_result         << endl;
    }

    cout << "--------------------------------------------" << endl;

    printDealerCards(dealer_cards);
    cout << "Dealer Score: " << dealer_score                                << endl;

    cout << "--------------------------------------------" << endl;

    printPlayerHands(player_hands);

    cout << "============================================" << endl;
}
// ── Fake data ─────────────────────────────────────────────────────────────────
int main() {

    // Case 1: Tay đơn thắng
    printSession(1,
        "2026-04-17", "09:00:00",
        1000, 1200, 200, 400, 0,
        0, 0, "none",
        "6-Hearts,10-Clubs,9-Diamonds", 25,
        "[hand1: A-Clubs,K-Diamonds | score:21 | win | actions:stand]"
    );

    // Case 2: Split 2 tay - hand1 bust, hand2 lose
    printSession(2,
        "2026-04-17", "11:30:00",
        1200, 1100, 200, 100, 100,
        0, 0, "none",
        "A-Spades,8-Diamonds", 19,
        "[hand1: 8-Clubs,3-Diamonds,J-Hearts | score:27 | lose | BUST | actions:hit,hit]  [hand2: 8-Spades,Q-Clubs | score:18 | lose | actions:split,stand]"
    );

    // Case 3: Re-split 3 tay
    printSession(3,
        "2026-04-17", "14:00:00",
        1100, 950, 300, 0, 200,
        0, 0, "none",
        "5-Clubs,7-Hearts,9-Spades", 21,
        "[hand1: K-Hearts,Q-Spades | score:20 | lose | actions:split,stand]  [hand2: K-Diamonds,A-Clubs | score:21 | push | actions:split,split,hit,stand]  [hand3: K-Clubs,5-Hearts | score:15 | lose | actions:split,hit,stand]"
    );

    // Case 4: Split + Double Down
    printSession(4,
        "2026-04-18", "10:15:00",
        950, 1050, 300, 200, 100,
        0, 0, "none",
        "7-Diamonds,10-Spades", 17,
        "[hand1: 9-Hearts,Q-Clubs | score:19 | win | DOUBLE | actions:split,double_down]  [hand2: 9-Diamonds,6-Spades,K-Hearts | score:25 | lose | BUST | actions:split,hit,hit]"
    );

    // Case 5: Surrender
    printSession(5,
        "2026-04-19", "10:00:00",
        1000, 950, 100, 0, 50,
        0, 0, "none",
        "A-Diamonds,6-Spades", 17,
        "[hand1: 9-Hearts,7-Clubs | score:16 | surrender | actions:surrender]"
    );

    // Case 6: Insurance win
    printSession(6,
        "2026-04-19", "08:30:00",
        1000, 1050, 100, 150, 0,
        1, 50, "win",
        "A-Spades,K-Hearts", 21,
        "[hand1: K-Clubs,8-Diamonds | score:18 | lose | actions:stand]"
    );

    // Case 7: Split + Surrender 1 tay
    printSession(7,
        "2026-04-19", "11:00:00",
        950, 975, 200, 100, 25,
        0, 0, "none",
        "Q-Hearts,8-Spades", 18,
        "[hand1: 9-Clubs,K-Diamonds | score:19 | win | actions:split,stand]  [hand2: 9-Spades,6-Hearts | score:15 | surrender | actions:split,surrender]"
    );

    // Case 8: Split + Double cả 2 tay
    printSession(8,
        "2026-04-19", "13:30:00",
        975, 575, 400, 0, 400,
        0, 0, "none",
        "6-Clubs,5-Hearts,10-Diamonds", 21,
        "[hand1: 5-Clubs,6-Spades,9-Hearts | score:20 | lose | DOUBLE | actions:split,double_down]  [hand2: 5-Diamonds,5-Hearts,K-Clubs | score:20 | lose | DOUBLE | actions:split,double_down]"
    );

    return 0;
}