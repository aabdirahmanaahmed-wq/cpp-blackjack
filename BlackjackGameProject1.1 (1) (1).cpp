#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <random>
#include <algorithm>
#include <unistd.h>
#include <limits>

using namespace std;
// Game rules include:
// - Single-deck shoe
// - 3:2 Blackjack payout
// - Dealer must hit on soft 17
// - Player may hit always, stand always, and double-down on any hand
// - Shoe cutoff occurs when there are 11 or less cards remaining in the deck


// Deck of Cards represented by a Vector.

vector<int> cardDeck{2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11,
    2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11,
    2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11,
    2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};


int main () {
    int playerHandtot = 0;
    int pcomp1 = 0;
    int pcomp2 = 0;
    int dealerHandtot = 0;
    int dcomp1 = 0;
    int dcomp2 = 0;
    int startStack;
    int currentStack;
    int finalStack;
    int cardsRemaining;
    int i;
    int x;
    int y;
    int temp = 0;
    int randomIndex = 0;
    int timesDealt;
    float Bet;
    float win;
    string name;
    string decision;

    // Shuffle function for deck of cards using mt19937.
    random_device rd;
    mt19937 g(rd());
    shuffle(cardDeck.begin(), cardDeck.end(), g);


    //Game start interface
    
    cout << "Enter your first name: ";
    cin >> name;
    cout << "Welcome to Blackjack, " << name << "!" << endl;
    cout << "How many chips will you be playing with? (Min: 100, Max: 1000): ";
    
    do {
        cin >> currentStack;
        if (currentStack < 100) {
            cout << "Not enough chips to play. Please re-enter: ";
        }
        else if (currentStack > 1000) {
            cout << "Too many chips are on the table. Please re-enter: ";
        }
        else {
            break;
        } 
    } while (true);



    cout << "You have " << currentStack << " chips." << endl;
    startStack = currentStack;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    do {
        cout << "Ready to start? Enter yes or no. (Default: yes)" << endl;
        getline(cin, decision);
        if (decision.empty()) {
            decision = "yes";
        }
    } while (decision != "yes");



    cardsRemaining = 52;
    do{
        timesDealt = 0;
        dealerHandtot = 0;
        playerHandtot = 0;
        pcomp1 = 0;
        pcomp2 = 0;
        dcomp1 = 0;
        dcomp2 = 0;
        cout << "You have " << currentStack << " chips." << endl;
        cout << "Place your bet (Min: 5, Max: 200): ";
        do {
            cin >> Bet;
            if (Bet < 5) {
                cout << "Invalid bet. Bet must be at least 5. Please re-enter bet: " << endl;
            }
            else if (Bet > 200) {
                cout << "Invalid bet. Bet cannot be larger than 200. Please re-enter bet: " << endl;;
            }
            else if (Bet > currentStack) {
                cout << "Invalid bet. Not enough chips in stack. Please re-enter bet: " << endl;
            }
            else {
                break;
            }
        } while (true); 



        cout << "Dealing Cards..." << endl;
        
        sleep(1);//delay for 1-2 seconds

        y = cardDeck.back();
        pcomp1 = pcomp1 + y;
        cardDeck.pop_back();
        cardsRemaining -= 1;

        y = cardDeck.back();
        dcomp1 = dcomp1 + y;
        cardDeck.pop_back();
        cardsRemaining -= 1;

        y = cardDeck.back();
        pcomp2 = pcomp2 + y;
        cardDeck.pop_back();
        cardsRemaining -= 1;

        y = cardDeck.back();
        dcomp2 = dcomp2 + y;
        cardDeck.pop_back();
        cardsRemaining -= 1;

        playerHandtot = pcomp1 + pcomp2;
        dealerHandtot = dcomp1 + dcomp2;

        timesDealt += 1;
        
        // Check for immediate Blackjack conditions or early busts on initialization
        if (timesDealt == 1) {
            if (playerHandtot > 21) {
                playerHandtot -= 10;
            }
            else if ((dealerHandtot == 21) && (playerHandtot == 21)) {
                cout << "Push. " << name << " keeps bet." << endl;
            }
            else if ((dealerHandtot == 21) && (playerHandtot < 21)) {
                cout << "\033[31mDealer has Blackjack. " << name << " loses " << Bet << " chips.\033[0m" << endl;
                currentStack -= Bet;
            }
            else if ((dealerHandtot < 21) && (playerHandtot == 21)) {
                cout << "BLACKJACK!" << endl;
                Bet = Bet * 1.5;
                win = Bet * 2;
                cout << "\033[32m" << name << " wins " << win << " chips!\033[0m" << endl;
                currentStack += Bet;
            }
        }

        cout << "Dealer has: " << dcomp1 << endl;
        cout << "Player has: " << playerHandtot << endl;


        // Player hand options

        do{ 
            cout << "Player options: Hit, Stand, or Double-down?" << endl;   // Player options only modify playerHandtot
            cout << "Enter h, s, or d (case-sensitive): ";
            cin >> decision;
            if (decision == "h") {
                y = cardDeck.back();
                playerHandtot = playerHandtot + y;
                cardDeck.pop_back();
                cardsRemaining -= 1;
                timesDealt += 1;
                cout << "Dealer has: " << dcomp1 << endl;
                cout << "Player has: " << playerHandtot << endl;
                if (playerHandtot > 21 && pcomp1 != 11) {
                    cout << "\033[31mPlayer has " << playerHandtot << " and busts. Player loses " << Bet << " chips.\033[0m" << endl;
                    
                }
                else if (playerHandtot > 21 && pcomp2 != 11) {
                    cout << "\033[31mPlayer has " << playerHandtot << " and busts. Player loses " << Bet << " chips.\033[0m" << endl;
                    
                }
                else if (playerHandtot > 21 && y != 11) {
                    cout << "\033[31mPlayer has " << playerHandtot << " and busts. Player loses " << Bet << " chips.\033[0m" << endl;
                    
                }
                else if (playerHandtot > 21 && pcomp1 == 11) {
                    playerHandtot = playerHandtot - 10;
            
                }
                else if (playerHandtot > 21 && pcomp2 == 11) {
                    playerHandtot = playerHandtot - 10;
                    
                }
                else if (playerHandtot > 21 && y == 11) {
                    playerHandtot = playerHandtot - 10;
                    
                }
            }
            else if(decision == "s") {
                break;
            }
            else if (decision == "d") {
                y = cardDeck.back();
                playerHandtot = playerHandtot + y;
                cardDeck.pop_back();
                cardsRemaining -= 1;
                timesDealt += 1;
                Bet = (Bet * 2);
                currentStack -= Bet;
                cout << "Dealer has: " << dcomp1 << endl;
                cout << "Player has: " << playerHandtot << endl;
                break;
            }
        } while ((dealerHandtot < 21) && (playerHandtot < 21));

        dealerHandtot = dcomp1 + dcomp2;
        if (dealerHandtot > 21) {
            dealerHandtot = dealerHandtot - 10;
        }

        cout << "Dealer flips over their down card..." << endl;
        sleep(1);

        cout << "Dealer has: " << dealerHandtot << endl;
        cout << "Player has: " << playerHandtot << endl;

        // Completing the dealer's hand

        do{
            if ((dealerHandtot >= 17) && (dcomp1 == 11 || dcomp2 == 11)) {
                dealerHandtot = dealerHandtot - 10;
                if (dealerHandtot < 17) {
                    y = cardDeck.back();
                    dealerHandtot = dealerHandtot + y;
                    cardDeck.pop_back();
                    cardsRemaining -= 1;
                    cout << "Dealer has: " << dealerHandtot << endl;
                    cout << "Player has: " << playerHandtot << endl;
                    if (dealerHandtot >= 17 && dealerHandtot <= 21) {
                        break;
                    }
                    else if (dealerHandtot > 21 && y == 11) {
                        dealerHandtot = dealerHandtot - 10;
                    }
                    else if (dealerHandtot > 21 && y != 11) {
                        cout << "Dealer busts!" << endl;
                        break;
                    }
                    else if (dealerHandtot == 21) {
                        cout << "Oh no! Dealer has 21!" << endl;
                        break;
                    }
                    else {
                        break;
                    }
                }
                else if (dealerHandtot >= 17 && dealerHandtot <= 21) {
                    break;
                }
                else if (playerHandtot > 21) {
                    break;
                }
                else {
                    break;
                }
            }
            else if ((dealerHandtot < 17) && (dcomp1 != 11 || dcomp2 != 11)) {
                y = cardDeck.back();
                dealerHandtot = dealerHandtot + y;
                cardDeck.pop_back();
                cardsRemaining -= 1;
                timesDealt += 1;
                cout << "Dealer has: " << dealerHandtot << endl;
                cout << "Player has: " << playerHandtot << endl;
                if (dealerHandtot >= 17 && dealerHandtot <= 21) {
                    break;
                }
                else if (dealerHandtot > 21 && y == 11) {
                    dealerHandtot = dealerHandtot - 10;
                }
                else if (dealerHandtot > 21 && y != 11) {
                    cout << "Dealer busts!" << endl;
                    break;
                }
                else if ((dealerHandtot >= 17) && (dealerHandtot <=21)) {
                    cout << "Dealer hand finished." << endl;
                    break;
                }
                else if (playerHandtot > 21) {
                    break;
                }
            
            }
            else {
                break;
            }
        } while(true);

        cout << "Dealer has: " << dealerHandtot << endl;
        cout << "Player has: " << playerHandtot << endl;

        if (playerHandtot > 21) {
            cout << "\033[31mPlayer busts. The dealer wins the hand, and the player loses " << Bet << " chips.\033[0m" << endl;
            currentStack -= Bet;
        }
        else if (dealerHandtot > 21) {
             cout << "\033[32mDealer busts! The player wins the hand and " << Bet << " chips!\033[0m" << endl;
             currentStack += Bet;
        }
        else if (dealerHandtot < playerHandtot) {
            cout << "\033[32mThe player wins the hand and " << Bet << " chips!\033[0m" << endl;
            currentStack += Bet;
        }
        else if(playerHandtot < dealerHandtot) {
            cout << "\033[31mThe dealer wins the hand, and the player loses " << Bet << " chips.\033[0m" << endl;
            currentStack -= Bet;
        }
        else if(dealerHandtot == playerHandtot) {
            cout << "Push. The player keeps their original bet." << endl;
        }
        
    } while (cardsRemaining > 11);

    finalStack = currentStack;
    cout << "Shoe has ended." << endl;
    if (finalStack < startStack) {
        cout << "You lost " << startStack - finalStack << " chips during the shoe." << endl;
        cout << "Better luck next time.";
    }
    else if (finalStack > startStack) {
        cout << "You won " << finalStack - startStack << " chips during the shoe!" << endl;
        cout << "Come back and play again anytime!";
    }

    return 0;
}
