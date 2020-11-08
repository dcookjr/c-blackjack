#include <iostream>
using namespace std;

void endgame();
void clearScreen();
void reset();
void hit();
void stand();
void display();
void dealerturn();

class game{
    public:
        int money = 100;
        int playerhand[10];
        int dealerhand[10];
        char answer;

        void initialize(){
            cout << "This is a game of blackjack, you can hit or stand." << endl;
            cout << "Every turn there will be a display of how many cards are in your hand," << endl;
            cout << "As well as the values of your cards. Try not to exceed 21." << endl;
            cout << "Do you want to play a game? (y or n) ";
            cin >> answer;
            if(answer == 'y'){
               clearScreen();
            }
            if(answer == 'n'){
                endgame();
            }
        }


        void draw(int* hand){
            try{
                for(int x = 0; x < 10; x++){
                    if(*(hand + x) == 0){
                        *(hand + x) = 2 + (rand() % 14);
                        x = 10;
                    }
                }
            }
            catch(exception &ex){
                cout << "Exception caught: " << ex.what() << endl;
            }
        }

        int hardsum(int* hand){
            int total = 0;
            int totalAces = 0;
            for(int x = 0; x < 10; x++){
                if(*(hand + x) == 15 && totalAces != 0){
                    total += 1;
                    totalAces += 1;
                }
                else if (*(hand + x) > 10)
                    total += 11;
                else
                    total += *(hand + x);
            }
            return total;
        }

        int softsum(int* hand){
            int total = 0;
            int totalAces = 0;
            for(int x = 0; x < 10; x++){
                if(*(hand + x) == 15)
                    total += 1;
                else if(*(hand + x) > 10)
                    total += 11;
                else
                    total += *(hand + x);
            }
            return total;
        }
        int sum(int* hand){
            int soft = softsum(hand);
            int hard = hardsum(hand);
            if(hard < 21 && hard > soft)
                return hard;
            else
                return soft;
        }

};

game currentGame;
int *player = currentGame.playerhand;
int *dealer = currentGame.dealerhand;
string cards[14] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};

int main(void){
    bool inPlay = true;
    string answer;
    srand(time(NULL));
    currentGame.initialize();
    reset();
    while(inPlay){
        clearScreen();
        display();
        cout << endl << "Do you want to hit or stand? ";
        cin >> answer;
        if(answer == "hit"){
            currentGame.draw(player);
        }
        else if(answer == "stand"){
            dealerturn();
        }

    }
    return 0;
}

void reset(){
    for(int x = 0; x < 10; x++){
        *(player + x) = 0;
        *(dealer + x) = 0;
    }
    currentGame.draw(player);
    currentGame.draw(player);
    currentGame.draw(dealer);
}



void hit(){
    char answer;
    bool answered = false;
    currentGame.draw(player);
    if(currentGame.hardsum(player) > 21 && currentGame.softsum(player) > 21){
        while(!answered){
            clearScreen();
            cout << "You busted..." << endl << "Would you like to play again? ";
            cin >> answer;
            if(answer = 'y'){
                reset();
                answered = true;
            }
            else if(answer == 'n')
                endgame();
        }
    }

}

void dealerturn(){
    char answer;
    while(true){
        if(currentGame.hardsum(dealer) < 15 || currentGame.softsum(dealer) < 6){
            currentGame.draw(dealer);
            if(currentGame.hardsum(dealer) > 21 && currentGame.softsum(dealer) > 21){
                clearScreen();
                display();
                cout << "Congratulations, the Dealer Busted!" << endl << "Would you like to play again? ";
                cin >> answer;
            }
        }
        else{
            if(currentGame.sum(player) > currentGame.sum(dealer)){
                clearScreen();
                display();
                cout << "Congratulations, you won!" << endl << "Would you like to play again? ";
                cin >> answer;
            }
            else{
                clearScreen();
                display();
                cout << "Sorry, you lost..." << endl << "Would you like to play again? ";
                cin >> answer;
            }
        }
        if(answer == 'y'){
            reset();
            break;
        }
        else if(answer == 'n'){
            endgame();
        }

    }
}

void display(){
    cout << "Dealer Hand: ";
    for(int x = 0; x < 10; x++){
        if(*(dealer + x) != 0)
            cout << cards[*(dealer + x) - 2] << " ";
    }
    cout << endl << endl << endl;
    cout << "Player Hand: ";
    for(int x = 0; x < 10; x++){
        if(*(player + x) != 0)
            cout << cards[*(player + x) - 2] << " ";
    }
    cout << endl << endl << endl;
}

void endgame(){
    exit(0);
}
void clearScreen(){
    cout << "\033[2J\033[1;1H";
}
