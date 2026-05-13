#include "../include/history.h"
//AI make UI
void show_history(vector<GameRecord> records) {
    string thick = "========================================================";
    string thin  = "--------------------------------------------------------";

    for (const GameRecord& r : records) {
        double diff = r.jsonData.balance.after_playing - r.jsonData.balance.starting_balance;
        string overall = (diff > 0) ? "WIN" : (diff < 0) ? "LOSE" : "DRAW";

        cout << "\n  " << thick << "\n";
        printf("  | Time:  %s\n", r.createdAt.c_str());
        printf("  | Session: %s\n", r.gameSession.c_str());
        cout << "  " << thin << "\n";

        // BALANCE
        printf("  | Balance : %.1f -> %.1f  (%+.1f)  [%s]\n",
               r.jsonData.balance.starting_balance,
               r.jsonData.balance.after_playing,
               diff, overall.c_str());

        cout << "  " << thin << "\n";
        cout << "  | DEALER\n";
        cout << "  " << thin << "\n";

        // DEALER
        const RecordHand& dh = r.jsonData.dealer.hand;
        string dealer_cards = "";
        for (const RecordCard& c : dh.hand)
            dealer_cards += c.name_card + "(" + c.type_card[0] + ") ";

        string dealer_actions = "";
        for (const string& a : dh.action)
            dealer_actions += a + " ";

        printf("  | Score  : %d %s\n", dh.score, dh.hand_is_bust ? "[BUST]" : "");
        printf("  | Cards  : %s\n", dealer_cards.c_str());
        printf("  | Actions: %s\n", dealer_actions.empty() ? "-" : dealer_actions.c_str());

        cout << "  " << thin << "\n";
        cout << "  | PLAYER\n";
        cout << "  " << thin << "\n";

        // PLAYER INFO
        printf("  | Balance  : %.1f\n", r.jsonData.player.balance);
        printf("  | Insurance: %.1f\n", r.jsonData.player.insurance);
        printf("  | Surrender: %s\n", r.jsonData.player.surrender ? "Yes" : "No");
        

        // PLAYER HANDS
        for (int i = 0; i < r.jsonData.player.hand.size(); i++) {
            const RecordHand& h = r.jsonData.player.hand[i];

            string cards = "";
            for (const RecordCard& c : h.hand)
                cards += c.name_card + "(" + c.type_card[0] + ") ";

            string actions = "";
            for (const string& a : h.action)
                actions += a + " ";

            cout << "  " << thin << "\n";
            printf("  | Hand #%d\n", i + 1);
            printf("  | Score  : %d   Bet: %d   Result: %s %s\n",
                   h.score, h.betting_amount, h.result.c_str(),
                   h.hand_is_bust ? "[BUST]" : "");
            printf("  | Cards  : %s\n", cards.c_str());
            printf("  | Actions: %s\n", actions.empty() ? "-" : actions.c_str());
        }

        cout << "  " << thick << "\n";
    }

    printf("\n  Total games: %zu\n\n", records.size());
}