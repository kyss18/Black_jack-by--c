#include<iostream>
#include<vector>
//#include <algorithm>
#include <random>
#include<math.h>
//#include <cstdlib>
#include <ctime>

using namespace std;
typedef struct card{
    string name_card;
    string type_card;
    int value;
}card;


class Deck {
    private:
    vector<card> deck;
    vector <card> discard_tray;

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
        //  card draw(){
        //     int r = 0;
        //     card c=deck[r];
        //      deck.erase(deck.begin()+r);
        //     return c;
        // }
        void take_card_back(card card){
            discard_tray.push_back(card);
        }
        
};
class Hand {
    private:
     vector<card> hand;
     int score=0;
     int ace_count=0;
     int betting_amount=0;
     bool is_doubling_down=false;
     bool hand_is_bust=false;
    public:
        card get_card(){
            return hand[0];
        }
        int get_score(){
            return score;
        }
        void set_doubling(){
            this->is_doubling_down=true;
        }
        bool check_doubling(){
            return is_doubling_down;
        }
        int get_size_of_hand(){
            return hand.size();
        }
        bool is_same_ace(){
            return (hand.size()==2 && hand[0].value==hand[1].value);
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
        void show_all_card(){
            for (auto x:hand){
             cout<<x.name_card<<" "<<x.type_card<<" "<<"|";
        }
    }
        bool is_bust(){
                if (score>21)
                    hand_is_bust=true;
                return hand_is_bust;
        }
        bool is_black_jack(){
            return (hand[0].value ==10 && hand[1].value==11)||((hand[0].value ==11 && hand[1].value==10));
        }
        void clear_hand(){
            hand.clear();
            is_doubling_down=false;
            hand_is_bust=false;
            score=0;
            ace_count=0;
        }
        bool same_two_value_card(){
            return (hand[0].value==hand[1].value)&&hand.size()==2;
        }
        card pop_card(){
            card c=hand.back();
            score=score-c.value;
            hand.pop_back();
            return c;
        }
        void set_betting_amount(int amount){
            this->betting_amount=amount;
        }
        int getBet(){
            return betting_amount;
        }
};
class Player {
    private:
        vector<Hand> hand;
        int total_bet;
        int insurance=0;
        bool surrender =false;
        double balance;
        int totalloss=0;
        int totalearn=0;
    public:
        Player(double balance){
            this->balance=balance;
        }
        Hand &get_hand(int i){
            return hand[i];
        }
        void set_bet_amount(int i){
    int bet_amount;
    cout<<"Your balance:"<<balance<<endl;
    do{
        cout<<"Input your bet Amount: ";
        cin>>bet_amount;
        }while(bet_amount<0||bet_amount>balance);
        hand[i].set_betting_amount(bet_amount);
}
    void reset_hand(){
        hand.clear();
        surrender=false;
        insurance=0;
        totalloss=0;
        totalearn=0;

    }
        void set_balance(int bet_amount){
             balance+=(bet_amount);
        }
        void take_balance (int bet_amount){
             balance-=bet_amount;
        }
        void update_blance_surr(){
            this->balance=this->balance-(hand[0].getBet()/2);
        }
        void add_balance(int bet_amount){
             balance +=bet_amount;
        }
         double  get_balance(){
             return balance;
        }
        
        int getTotalBet() {
            int sum = 0;
            for (int i = 0; i < hand.size(); i++) {
                sum += hand[i].getBet();
            }
            return sum;
}

       void add_hand(Hand &new_hand){
            this->hand.push_back(new_hand);
       }
       int get_hands_size(){
        return hand.size();
       }
       void get_card_from_hand(int i,int money){
        Hand new_hand;
        new_hand.add_card(hand[i].pop_card());
        new_hand.set_betting_amount(money);
        hand.insert(hand.begin()+i+1,new_hand);
       }
       bool can_double(int i){
        return hand[i].getBet()*2 <=balance;
       }
       void set_insurance(int insurance_betting){
        this->insurance=insurance_betting;
       }
       int get_insurance(){
        return insurance;
       }
       void set_surr(){
        this->surrender=true;
       }
       bool is_surr(){
        return surrender;
       }
       void set_loss(int loss){
            this->totalloss+=loss;
       }
       void set_earn(int win){
        this->totalearn+=win;
       }
       int get_loss(){
        return totalloss;
       }
       int get_earn(){
        return totalearn;
       }
       int get_Net(){
        return totalearn-totalloss;
       }
};
class Dealer{
    private :
        Hand hand;
    public:
        Hand &get_hand(){
            return hand;
        }
        void reset_hand(){
            hand.clear_hand();
    }
};
void show_card(Dealer dealer,Player player){
        cout<<"Dealer Cards: ";
        dealer.get_hand().show_all_card();
        cout<<"\nYour Cards:";
        for (int i=0;i<player.get_hands_size();i++){
            player.get_hand(i).show_all_card();
            cout<<"Your score:"<<player.get_hand(i).get_score()<<endl;
        }
        
        cout<<endl;
        
        cout<<"Dealer score:"<<dealer.get_hand().get_score()<<endl;
    }
bool ask_user_for_continue(int &selection,Player player){
        cout<<"Your Balance:"<<player.get_balance()<<endl;
        
        cout << "Do you want to continue?\n";
        cout << "1. Yes\n";
        cout << "(Any number). Back to menu\n";
        cout << "Your choice: ";
        cin >> selection;
        cout<<selection;
        if(selection == 1){
               return true;
        }
        return false;
}
void deal_initial_cards(Player &player, Deck &d,Dealer &dealer){
    player.get_hand(0).add_card(d.draw());
    dealer.get_hand().add_card(d.draw());
    player.get_hand(0).add_card(d.draw());
    dealer.get_hand().add_card(d.draw());
}
bool check_blackjack(Dealer dealer,Player &player,int bet_amount){
    if (dealer.get_hand().is_black_jack() && player.get_hand(0).is_black_jack()){
            show_card(dealer,player);
            cout<<"\nTie\n";
            cout<<"You get: "<<bet_amount<<endl;
            if (player.get_insurance()>=1){
                cout<<"\nYou win the insurance\n";
                cout<<"You got:"<<player.get_insurance()<<" from the insurance."<<endl;
                player.set_balance(player.get_insurance()*2);
            }
                   return true; 
                }
        else if (dealer.get_hand().is_black_jack()){
            show_card(dealer,player);
            cout<<"\nDealer win\n";
            player.take_balance(player.get_hand(0).getBet());
            cout<<"You lose hand: "<<bet_amount;
            if (player.get_insurance()>=1){
                cout<<"\nYou win the insurance\n";
                cout<<"You got:"<<player.get_insurance()<<" from the insurance."<<endl;
                player.set_balance(player.get_insurance()*2);
            }
                    return true;
                }
        else if (player.get_hand(0).is_black_jack()){
            show_card(dealer,player);
            cout<<"\nYou Win\n";
            player.set_balance(bet_amount*1.5);
            cout<<"You got: "<<bet_amount*1.5<<endl;
            if (player.get_insurance()>=1){
                cout<<"\nYou win the insurance\n";
                cout<<"You got:"<<player.get_insurance()<<" from the insurance."<<endl;
                player.set_balance(player.get_insurance()*2);
            }
                    return true;
                }
            return false;
            
}
void player_turn(Player &player,Deck &d,Dealer dealer,int betting_amount){
        int i=0;
        int split_count=0;
    while (i<player.get_hands_size()){
        int selection;
        if (player.get_hand(i).get_size_of_hand()==1 &&( player.get_hand(i).get_card().name_card == "A")){
            player.get_hand(i).add_card(d.draw());
            i++;
        }
    else {
        int hitOpt = 1;
        int standOpt = 2;
        int splitOpt = -1;
        int doubleOpt = -1;
        int surrOpt= -1;
        int option = 3;
        cout<<"-----------------------------"<<endl;
        cout<<"Your balance: "<<player.get_balance()<<endl;
        cout<<"Dealer card: ";
        cout<<dealer.get_hand().get_card().name_card<<" + ? "<<endl;
         for (int j=0;j<player.get_hands_size();j++){
           
            if (!player.get_hand(j).is_bust()&&i==j){
                 cout<<"Hand "<<j+1<<"\tBet: "<<player.get_hand(j).getBet()<<"\t<------CURRENT\n";
            }
            else if (i<j){
                cout<<"Hand "<<j+1<<"\tBet: "<<player.get_hand(j).getBet()<<"\tWaiting\n";
            }
            else if (i>j&& !player.get_hand(j).is_bust()){
                if (player.get_hand(j).check_doubling()){
                    cout<<"*";
                }
               
                cout<<"Hand "<<j+1<<"\tBet: "<<player.get_hand(j).getBet()<<"\tWaiting for the dealer turn\n";
            }
            else {
                if (player.get_hand(j).check_doubling()){
                    cout<<"*";
                }
                cout<<"Hand "<<j+1<<"\tBet: "<<player.get_hand(j).getBet()<<": Bust\n";
            }
            
            player.get_hand(j).show_all_card();
            cout<<"\nScore:"<<player.get_hand(j).get_score();
            cout<<endl;
         }
         cout<<"\n-----------------------------"<<endl;
         //cout<<player.getBetting(i)*2<<"-"<<player.get_balance();
         cout<<player.get_balance()<<"-"<< player.getTotalBet();
        cout<<"\n1.Hit\n";
        cout<<"2.Stand\n";
        if (player.get_hand(i).same_two_value_card() &&(player.get_balance() > player.getTotalBet())&&split_count<4
    &&!(player.get_hand(i).getBet()*2 > player.get_balance()) ){
        splitOpt = option;
    cout << option++ << ".Split\n";
        }
         if (player.get_hand(i).get_size_of_hand()==2&&split_count==0&& player.get_hand(i).getBet()!=0){
            surrOpt =option;
            cout<<option++<<".Surrender\n";
        }
        if (player.can_double(i)&& player.get_hand(i).get_size_of_hand()==2&& player.get_hand(i).getBet()!=0){
            doubleOpt = option;
                 cout << option++ << ".Double\n";
        }
        if(player.get_hand(i).get_score()<16){
            cout<<"You should hit more\n";
        }
        do{
        cout<<"\nHand "<<i+1<<" chosing...\n";
        cout<<"Your selection: ";
        cin>>selection;
        }while((selection < 1 || selection > option));
        cout<<"-----------------------------"<<endl;
        //cout<<"Selection:"<<selection<<endl;
        
        if (selection== hitOpt){
            //cout<<"i="<<i<<endl;    
            player.get_hand(i).add_card(d.draw());
             if (player.get_hand(i).is_bust()) {
            i++;
             }
        
            system("cls");
            cout<<endl;
        }
        else if (selection == standOpt){
            i++;
            system("cls");
        }
        else if (selection == splitOpt) {

           player.get_card_from_hand(i,player.get_hand(i).getBet());
            split_count++;
            system("cls");
            //cout<<player.getTotalBet();
        
        }
        else if (selection == doubleOpt) {
            player.get_hand(i).set_doubling();
            player.get_hand(i).add_card(d.draw());
            i++;
            system("cls");
    }
        else if (selection==surrOpt){
            int option2;
            do{
                cout<<"Are you sure to surrender ?"<<endl;
                cout<<"1.Yes\n";
                cout<<"2.No\n";
                cout<<"Your option:";
                cin>>option2;
            }while(option2<1|| option2>2);
            if (option2 ==1){
            player.set_surr();
            return ;
            }
            
        }

}
    }
}
void dealer_turn(Dealer &dealer,Deck &d){
    while(!(dealer.get_hand().get_score() >= 17))
        {
            dealer.get_hand().add_card(d.draw());
                            //dealer.show_card();
        }
}
void compare_result(Dealer dealer,Player &player,int bet_amount){
    cout<<"Summaries: \n";
    cout<<"Starting balance:"<<player.get_balance()<<endl;
    cout<<"Dealer cards:";
    dealer.get_hand().show_all_card();
    if (player.get_insurance()>1){
        cout<<"Losing the insurance :(("<<endl;
        player.take_balance(player.get_insurance());
    }
    cout<<endl;
    for (int i=0;i<player.get_hands_size();i++){
    if (dealer.get_hand().get_score()== player.get_hand(i).get_score()){
        // show_card(dealer,player);
        cout<<"Your Cards: ";
        player.get_hand(i).show_all_card();
        cout<<"\nHand "<<i+1<<": ";
        cout<<"\n\tTie\n";
        //player.add_balance(bet_amount);
        cout<<"You earn: nothing :))"<<endl;
        cout<<"-----------------------------"<<endl;
        
    }
    else if((dealer.get_hand().get_score()>player.get_hand(i).get_score())&& !dealer.get_hand().is_bust()){
        //show_card(dealer,player);
        cout<<"Your Cards: ";
        player.get_hand(i).show_all_card();
        cout<<"\nHand "<<i+1<<": ";
        
        if (player.get_hand(i).check_doubling()){
            player.take_balance(player.get_hand(i).getBet()*2);
            cout<<"You lose double: "<<player.get_hand(i).getBet();
            player.set_loss(player.get_hand(i).getBet()*2);

        }
        else {
            player.take_balance(player.get_hand(i).getBet());
            cout<<"You lose: "<<player.get_hand(i).getBet();
            player.set_loss(player.get_hand(i).getBet());
        }
        
        cout<<"\n-----------------------------"<<endl;                
        }
    else if ((dealer.get_hand().get_score()<player.get_hand(i).get_score()) && !player.get_hand(i).is_bust()){
        //show_card(dealer,player);
        cout<<"Your Cards: ";
        player.get_hand(i).show_all_card();
        cout<<"\nHand "<<i+1<<": ";
        cout<<"\n\tYou Win\n";
        if (player.get_hand(i).check_doubling()){
            player.set_balance(player.get_hand(i).getBet()*2);
            cout<<"You earn double: "<<player.get_hand(i).getBet()<<" + "<<player.get_hand(i).getBet()<<endl;
            player.set_earn(player.get_hand(i).getBet()*2);
        }
        else {
           player.set_balance(player.get_hand(i).getBet());
            cout<<"You earn: "<<bet_amount<<endl;
            player.set_earn(player.get_hand(i).getBet());
        }
        
        cout<<"\n-----------------------------"<<endl;
    }
    else if (player.get_hand(i).is_bust()||(player.get_hand(i).is_bust()&&dealer.get_hand().is_bust())){
        cout<<"Your Cards: ";
        player.get_hand(i).show_all_card();
         cout<<"\nHand "<<i+1<<": ";
        cout<<"\n\tYou Lose:\n";
        if (player.get_hand(i).check_doubling()){
            player.take_balance(player.get_hand(i).getBet()*2);
            cout<<"You lose double: "<<player.get_hand(i).getBet();
            player.set_loss(player.get_hand(i).getBet()*2);
        }
        else {
            player.take_balance(player.get_hand(i).getBet());
            cout<<"You lose: "<<player.get_hand(i).getBet();
            player.set_loss(player.get_hand(i).getBet());
        }
             cout<<"\n-----------------------------"<<endl;
    }
    else { //this case for dealer bust
        //show_card(dealer,player);
        cout<<"Your Cards: ";
        player.get_hand(i).show_all_card();
        cout<<"\nHand "<<i+1<<": ";
        cout<<"\n\tYou Win\n";
        // player.set_balance_win(bet_amount);
        // cout<<"You get: "<<bet_amount*2<<endl;
        if (player.get_hand(i).check_doubling()){
            player.set_balance(player.get_hand(i).getBet()*2);
            cout<<"You earn double: "<<player.get_hand(i).getBet()<<" + "<<player.get_hand(i).getBet()<<endl;
            player.set_earn(player.get_hand(i).getBet()*2);
        }
        else {
           player.set_balance(player.get_hand(i).getBet());
            cout<<"You earn: "<<bet_amount<<endl;
            player.set_earn(player.get_hand(i).getBet());
        }

        
        cout<<"\n-----------------------------"<<endl;
    }
}
        if(player.get_hands_size()>1){
        cout<<"\nTotal earn:"<<player.get_earn()<<endl;
        cout<<"\nTotal loss:"<<player.get_loss()<<endl;
        cout<<"NET:"<<player.get_Net()<<endl;
        }
}
void Play_game(Player &player){
     
    while(true){
            if (player.get_balance() >0)
                {
                system("cls");
                Deck d;
                Dealer dealer;
                Hand player_hand;
                player.reset_hand();
                dealer.get_hand().clear_hand();
                player.add_hand(player_hand);  ///lam toi day 
                player.set_bet_amount(0);
                deal_initial_cards(player,d,dealer);
                int ask_continue;
                if (dealer.get_hand().get_card().name_card=="A"&& player.get_hand(0).getBet()>=2
                        && (1+player.get_hand(0).getBet())<=player.get_balance()){
                    int select;
                    cout<<"Dealer Card: "<<dealer.get_hand().get_card().name_card<<" +  ? "<<endl;
                    do {
                        cout<<"Would you like to buy insurance?\n";
                        cout<<"1.Yes\n";
                        cout<<"2.No\n";
                        cout<<"Your option:";
                        cin>>select;
                    }while(select<1||select>2);
                    if (select==1){
                        int insurance_betting;
                        do{
                            cout<<"How much would you like to pay for the insurane ?"<<endl;
                            cout<<"Betting:";
                            cin>>insurance_betting;
                        }while(insurance_betting <1 ||insurance_betting*2>player.get_hand(0).getBet()||
                    (insurance_betting+player.get_hand(0).getBet())>player.get_balance());
                        player.set_insurance(insurance_betting);

                    }
                }
                if (check_blackjack(dealer,player,player.get_hand(0).getBet())){
                    
                    if (!ask_user_for_continue(ask_continue,player))
                            return;
                }
                else {
                    
                     player_turn(player,d,dealer,player.get_hand(0).getBet());
                     
                     if (!player.is_surr()){
                        dealer_turn(dealer,d);
                        compare_result(dealer,player,player.get_hand(0).getBet());
                     }
                    else {
                        cout<<"You surrender\n";
                        cout<<"You lose 50% money\n";
                        player.update_blance_surr();
                    }
                        if(ask_user_for_continue(ask_continue,player)==false)
                            return;
                        
                    }
                
            }
        
            else {
                cout<<"-----------------------------"<<endl;
                cout<<"Please deposit more money"<<endl;
                cout<<"-----------------------------"<<endl;
                break;
            }
            //cout<<"khoa";

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
    cout << fixed;
cout.precision(0);
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
        system("cls");
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
}