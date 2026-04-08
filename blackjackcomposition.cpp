#include<iostream>
#include<vector>
#include <algorithm>
#include <random>
//#include <cstdlib>
#include <ctime>

using namespace std;
typedef struct card{
    string name_card;
    string type_card;
    int value;
}card;

class Hand {
    protected:
     vector<card> hand;
     int score=0;
     int ace_count=0;
     int balance;
    public:
        card get_card(){
            return hand[0];
        }
        int get_score(){
            return score;
        }
        void add_card( card c) {
            hand.push_back(c);
            score+=c.value;
            if(c.name_card == "A")
        ace_count++;

    while(score > 21 && ace_count > 0)
    {
        score -= 10;
        ace_count--;
    }
            //cout<<player_card[0].name_card;
        }
        vector<card> get_all_card(){
            return hand;
        }
        bool is_bust(){
            return score>21;
        }
        bool is_black_jack(){
            return (hand[0].value ==10 && hand[1].value==11)||((hand[0].value ==11 && hand[1].value==10));
        }
        void clear_hand(){
            hand.clear();
            score=0;
            ace_count=0;
        }
        bool same_two_card(){
            return (hand[0].name_card==hand[1].name_card)&&hand.size()==2;
        }
        card pop_card(){
            card c=hand.back();
            score=score-c.value;
            hand.pop_back();
            return c;
        }
};
class Deck {
    protected:
    vector<card> deck;

    public:
        Deck(){
        deck.push_back({"A","Hearts",11});
        deck.push_back({"3","Hearts",3});
        deck.push_back({"4","Hearts",4});
        deck.push_back({"2","Hearts",2});
        deck.push_back({"3","Hearts",3});
        deck.push_back({"4","Hearts",4});
        deck.push_back({"5","Hearts",5});
        deck.push_back({"6","Hearts",6});
        deck.push_back({"7","Hearts",7});
        deck.push_back({"8","Hearts",8});
        deck.push_back({"9","Hearts",9});
        deck.push_back({"10","Hearts",10});
        deck.push_back({"J","Hearts",10});
        deck.push_back({"Q","Hearts",10});
        deck.push_back({"K","Hearts",10});

        deck.push_back({"A","Space",11});
        deck.push_back({"2","Space",2});
        deck.push_back({"3","Space",3});
        deck.push_back({"4","Space",4});
        deck.push_back({"5","Space",5});
        deck.push_back({"6","Space",6});
        deck.push_back({"7","Space",7});
        deck.push_back({"8","Space",8});
        deck.push_back({"9","Space",9});
        deck.push_back({"10","Space",10});
        deck.push_back({"J","Space",10});
        deck.push_back({"Q","Space",10});
        deck.push_back({"K","Space",10});

        deck.push_back({"A","Diamonds",11});
        deck.push_back({"2","Diamonds",2});
        deck.push_back({"3","Diamonds",3});
        deck.push_back({"4","Diamonds",4});
        deck.push_back({"5","Diamonds",5});
        deck.push_back({"6","Diamonds",6});
        deck.push_back({"7","Diamonds",7});
        deck.push_back({"8","Diamonds",8});
        deck.push_back({"9","Diamonds",9});
        deck.push_back({"10","Diamonds",10});
        deck.push_back({"J","Diamonds",10});
        deck.push_back({"Q","Diamonds",10});
        deck.push_back({"K","Diamonds",10});

        deck.push_back({"A","Clubs",11});
        deck.push_back({"2","Clubs",2});
        deck.push_back({"3","Clubs",3});
        deck.push_back({"4","Clubs",4});
        deck.push_back({"5","Clubs",5});
        deck.push_back({"6","Clubs",6});
        deck.push_back({"7","Clubs",7});
        deck.push_back({"8","Clubs",8});
        deck.push_back({"9","Clubs",9});
        deck.push_back({"10","Clubs",10});
        deck.push_back({"J","Clubs",10});
        deck.push_back({"Q","Clubs",10});
        deck.push_back({"K","Clubs",10});

        }
        void show_card(){
            for (int i=0;i<deck.size();i++){
                cout<<deck[i].name_card<<" "<<deck[i].type_card<<" "<<endl;
            }
            
        }
        
        card draw(){
            int r = rand() % deck.size();
            card c=deck[r];
             deck.erase(deck.begin()+r);
            return c;
        }
        
};
class Player {
    private:
        vector<Hand> hand;
        //Hand hand;
        double balance;
    public:
        Player(double balance){
            this->balance=balance;
        }
        void set_balance_win(int bet_amount){
             balance+=(bet_amount*2);
        }
        void take_balance (int bet_amount){
             balance-=bet_amount;
        }
        void add_balance(int bet_amount){
             balance +=bet_amount;
        }
         double  get_balance(){
             return balance;
        }

        bool is_less_than_16(int i){
            return hand[i].get_score()<16;
        }
        void show_card(int i){
            for (auto x:hand[i].get_all_card()){
                cout<<x.name_card<<" "<<x.type_card<<" "<<"|";
            }
       }
       void add_hand(Hand &new_hand){
            this->hand.push_back(new_hand);
       }
       int get_score(int i){
            return hand[i].get_score();
       }
       void add_card(card c,int i){
            hand[i].add_card(c);
       }
       bool is_black_jack(int i){
            return hand[i].is_black_jack();
       }
       bool is_bust(int i){
        return hand[i].is_bust();
       }
       void clear_hand(){
        hand.clear();
       }
       bool can_split(int i){
        return hand[i].same_two_card();
       }
       int get_hands(){
        return hand.size();
       }
       void get_card_from_hand(int i){
        Hand new_hand;
        new_hand.add_card(hand[i].pop_card());
        hand.insert(hand.begin()+i+1,new_hand);
       }

};
class Dealer{

    private :
        Hand hand;
    public:
       bool check_greater_than_17(){
            return hand.get_score()>=17;
       }
       void show_card(){
            for (auto x:hand.get_all_card()){
                cout<<x.name_card<<" "<<x.type_card<<" "<<"|";
            }
       }
       int get_score(){
            return hand.get_score();
       }
       void add_card(card c){
            hand.add_card(c);
       }
       bool is_black_jack(){
            return hand.is_black_jack();
       }
       bool is_bust(){
        return hand.is_bust();
       }
       void clear_hand(){
        hand.clear_hand();
       }
       card show_a_card(){
           return hand.get_card();
       }
};
void show_card(Dealer dealer,Player player){
        cout<<"Dealer Cards: ";
        dealer.show_card();
        cout<<"\nYour Cards:";
        for (int i=0;i<player.get_hands();i++){
            player.show_card(i);
            cout<<"Your score:"<<player.get_score(i)<<endl;
        }
        
        cout<<endl;
        
        cout<<"Dealer score:"<<dealer.get_score()<<endl;
    }
bool ask_user_for_continue(int &selection,Player player){
        cout<<"Your Balance:"<<player.get_balance()<<endl;
        
        cout << "Do you want to continue?\n";
        cout << "1. Yes\n";
        cout << "(Any number). Back to menu\n";
        cout << "Your choice: ";
        cin >> selection;
        if(selection == 1){
               return true;
        }
        return false;
}
int get_bet_amount(Player player){
    int bet_amount;
    do{
        cout<<"Input your bet Amount: ";
        cin>>bet_amount;
        }while(bet_amount<0||bet_amount>player.get_balance());
        return bet_amount;
}
void deal_initial_cards(Player &player, Deck &d,Dealer &dealer,int num_of_hands){
    cout<<"-----------------------------"<<endl;
    cout<<"Your balance: "<<player.get_balance()<<endl;
    player.add_card(d.draw(),num_of_hands);
    dealer.add_card(d.draw());
    player.add_card(d.draw(),num_of_hands);
    dealer.add_card(d.draw());
    cout<<"Your cards"<<endl;
    player.show_card(num_of_hands);
    //cout<<"Hand:"<<player.get_hands();
    for (int i=0;i<player.get_hands();i++){
    cout<<"\nScore:"<<player.get_score(i);
    
    cout<<endl;
    }
}
bool check_blackjack(Dealer dealer,Player &player,int bet_amount){
    for (int i=0;i<player.get_hands();i++){
    if (dealer.is_black_jack() && player.is_black_jack(i)){
            show_card(dealer,player);
            cout<<"\nTie\n";
            player.add_balance(bet_amount);
            cout<<"You get: "<<bet_amount<<endl;
                   return true; 
                }
        else if (dealer.is_black_jack()){
            show_card(dealer,player);
            cout<<"\nDealer win\n";
                    return true;
                }
        else if (player.is_black_jack(i)){
            show_card(dealer,player);
            cout<<"\nYou Win\n";
            player.set_balance_win(bet_amount);
            cout<<"You get: "<<bet_amount*2<<endl;
                    return true;
                }
            return false;
            }
}
void player_turn(Player &player,Deck &d,Dealer dealer){
    
    int selection;
    cout<<"Dealer card: ";
        cout<<dealer.show_a_card().name_card<<" "<<dealer.show_a_card().type_card <<endl;
        int i=0;
    
    while (i<player.get_hands()){
        if (!player.is_black_jack(i)){
        int maxOption = 2;
        cout<<"-----------------------------"<<endl;
        cout<<"Dealer card: ";
        cout<<dealer.show_a_card().name_card<<endl;
         cout<<"Hand "<<i+1<<":\n";
         player.show_card(i);
        cout<<"\n1.Draw more\n";
        cout<<"2.Skip\n";
        if (player.can_split(i)){
            cout<<"3.Split\n";
            maxOption=3;
        }
        if(player.get_score(i)<16){
            cout<<"You should draw more\n";
        }
        do{
            
          
        cout<<"\nHand "<<i+1<<" chosing...\n";
        cout<<"Your selection: ";
        cin>>selection;
             if (selection == 3 && !player.can_split(i)) {
        cout << "Invalid choice (cannot split)\n";
        continue;
    }

        }while(selection < 1 || selection > maxOption);
        cout<<"-----------------------------"<<endl;
        switch (selection)
        {
        case 1:
            player.add_card(d.draw(),i);
            cout<<"Hand "<<i+1<<":"<<endl;
            player.show_card(i);
           // cout<<player.is_bust(i);
            cout<<"\nScore:"<<player.get_score(i);
             if (player.is_bust(i)) {
            cout << "BUST!\n";
            i++;
        }
            cout<<endl;
            break;
        case 2:
            i++;
            break;
        case 3:
           player.get_card_from_hand(i);
            cout<<"Splited\n";
            cout<<"\nYou have "<<player.get_hands()<<endl;
        }
}
         else {
        cout<<"\nThis hand got black-jack\n";
        i++;
    }
    }
   
}
void dealer_turn(Dealer &dealer,Deck &d){
    while(!dealer.check_greater_than_17())
        {
            dealer.add_card(d.draw());
                            //dealer.show_card();
        }
}
void compare_result(Dealer dealer,Player &player,int bet_amount){
    for (int i=0;i<player.get_hands();i++){
    if (dealer.get_score()== player.get_score(i)){
        show_card(dealer,player);
        cout<<"\n\tTie\n";
        player.add_balance(bet_amount);
        cout<<"You get:"<<bet_amount<<endl;
        cout<<"-----------------------------"<<endl;
        
    }
    else if((dealer.get_score()>player.get_score(i))&& !dealer.is_bust()){
        show_card(dealer,player);
        cout<<"\n\tDealer Win\n";
        cout<<"-----------------------------"<<endl;                
        }
    else if ((dealer.get_score()<player.get_score(i)) && !player.is_bust(i)){
        show_card(dealer,player);
        cout<<"\n\tYou Win\n";
        player.set_balance_win(bet_amount);
        cout<<"You get: "<<bet_amount*2<<endl;
        cout<<"-----------------------------"<<endl;
    }
    else {
        show_card(dealer,player);
        cout<<"\n\tYou Win\n";
        player.set_balance_win(bet_amount);
        cout<<"You get: "<<bet_amount*2<<endl;
        cout<<"-----------------------------"<<endl;
    }
}
}
void Play_game(Player &player){
     
    while(true){
            if (player.get_balance() >0)
                {
                int bet_amount=get_bet_amount(player);
                Deck d;
                Dealer dealer;
                Hand player_hand;
                player.clear_hand();
                dealer.clear_hand();
                player.add_hand(player_hand);
                cout<<player.get_hands();
                
                //player.take_balance(bet_amount);
                deal_initial_cards(player,d,dealer,player.get_hands()-1);
                int ask_continue;
                if (check_blackjack(dealer,player,bet_amount)){
                    if (!ask_user_for_continue(ask_continue,player))
                            return;
                }
                else {
                    player_turn(player,d,dealer);
                    
                    if(player.is_bust(1)){
                        cout<<"\tYou lose\n";
                        cout<<"-----------------------------"<<endl;
                        if(!ask_user_for_continue(ask_continue,player))
                            return;
                    }
                    else {
                        dealer_turn(dealer,d);
                        compare_result(dealer,player,bet_amount);
                        if(!ask_user_for_continue(ask_continue,player))
                            return;
                    }
                }
            }
        
            else {
                cout<<"-----------------------------"<<endl;
                cout<<"Please deposit more money"<<endl;
                cout<<"-----------------------------"<<endl;
                break;
            }
        }
}
void deposit(Player &player){
    double amount;
    cout<<"Press \"-1\" to cancel deposit\n";
    do {
    cout << "How much would you like to deposit : ";
    cin >> amount;
    }while(amount<-1|| amount ==0);
        if (amount >0) {
            int choose;
            do{
                cout<<"Confirm deposit of $"<< amount<<" to your account? \n";
                cout<<"1.Of course\n";
                cout<<"2.No\n";
                cout<<"Your option:";
                cin>>choose;
            }while(choose <1||choose>2);
            if (choose ==1){
                player.add_balance(amount);
                cout<<"You deposited $"<<amount<<" successfully\n";
            }
            else {
                cout<<"You canceled deposit\n";
            }
        }
            else {
                cout<<"You canceled deposit\n";
            }
}
 void Menu (){
    int balance;
    int choose_menu;
    do{
    cout<<"Input your balance: ";
    cin>>balance;
    }while(balance<=0);
    Player player(balance);
    while (true){
    cout<<"\n===== BLACKJACK =====\n";
    cout<<"Balance: $"<<player.get_balance()<<endl;
    cout<<"1. Play blackjack\n";
    cout<<"2. Coin flip\n";
    cout<<"3. Three-Card Game\n";
    cout<<"4. Lucky Number\n";
    cout<<"5. Deposit\n";
    cout<<"6. Check Balance\n";
    cout<<"7. Statistics\n";
    cout<<"8. Game history\n";
    cout<<"9. Exit\n";
    cout<<"Your option: ";
    cin>>choose_menu;
    switch(choose_menu){
        case 1:
        Play_game(player);
        break;
        case 2:
            cout<<"To be continue\n";
            break;
        case 3:
            cout<<"To be continue\n";
            break;
        case 4:
            cout<<"To be continue\n";
            break;
        case 5:
        {
            deposit(player);
        }
        break;
        case 6:
        {
            cout<<"\n-----------------------------\n"<<endl;
            cout<<"Your balance:"<<player.get_balance()<<"$"<<endl;
            cout<<"\n-----------------------------\n"<<endl;
        }
        break;
        case 7:
            cout<<"To be continue\n";
            break;
        case 8:
            cout<<"To be continue\n";
            break;
        case 9:
            
            return;
        default:
            cout<<"Wrong Option";
            break;
        }
        //system("cls");
    }
 }
int main (){
    srand(time(0));
    Menu();

    // Deck d1;
    // //  cout<<"\tBefore suffle"<<endl;
    // //  d1.show_card();
    // cout<<"\tAfter suffle"<<endl;
    // d1.show_card();
    // Player p1(5000);
    //  cout<<"\tPlayer Card"<<endl;
    //   p1.add_card(d1.draw());
    //   //p1.show_card();
    //  // p1.draw_a_card();
    //   p1.add_card(d1.draw());
      

    //   p1.show_card();
    //    cout<<p1.is_bust();
    //    cout<<"\n Black Jack \n";
    //    cout<<p1.is_black_jack();

}