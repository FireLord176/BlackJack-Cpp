#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to calculate the total value of a hand
int calculateHandValue(int hand[], int numCards)
{
    int value = 0;
    int numAces = 0;

    for (int i = 0; i < numCards; i++) {
        if (hand[i] == 1) {
            value += 11;
            numAces++;
        } else if (hand[i] > 10) {
            value += 10;
        } else {
            value += hand[i];
        }
    }

    // Adjust the value if there are aces and the total value is greater than 21
    while (value > 21 && numAces > 0) {
        value -= 10;
        numAces--;
    }

    return value;
}

// Function to display the player's hand
void displayHand(int hand[], int numCards)
{
    for (int i = 0; i < numCards; i++) {
        switch (hand[i]) {
            case 1:
                cout << "A ";
                break;
            case 11:
                cout << "J ";
                break;
            case 12:
                cout << "Q ";
                break;
            case 13:
                cout << "K ";
                break;
            default:
                cout << hand[i] << " ";
                break;
        }
    }
}

// Function to play the blackjack game
void playBlackjack(string playerName, int& bankBalance, int& betamount)
{
    const int NUM_CARDS = 52;
    const int MAX_HAND_SIZE = 10;
    const int BLACKJACK_VALUE = 21;
    const int DEALER_MIN_VALUE = 17;
    const int BUST_BARRIER = 22;

    int deck[NUM_CARDS];
    int numCards = 0;
    int playerHand[MAX_HAND_SIZE];
    int dealerHand[MAX_HAND_SIZE];
    int playerNumCards = 0;
    int dealerNumCards = 0;
    int playerBalanceChange = 0;

    // Initialize the deck
    for (int i = 0; i < NUM_CARDS; i++) {
        deck[i] = (i % 13) + 1;
    }

    // Shuffle the deck
    srand(time(0));
    for (int i = 0; i < NUM_CARDS; i++) {
        int j = rand() % NUM_CARDS;
        int temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }

    // Deal initial cards
    playerHand[playerNumCards++] = deck[numCards++];
    dealerHand[dealerNumCards++] = deck[numCards++];
    playerHand[playerNumCards++] = deck[numCards++];
    dealerHand[dealerNumCards++] = deck[numCards++];

    // Display initial hands
    cout << "-----------------------------" << endl;
    cout << "Player: " << playerName << endl;
    cout << "Balance: R" << bankBalance << endl;
    cout << playerName <<"'s Hand: ";
    displayHand(playerHand, playerNumCards);
    cout << endl;
    cout <<playerName << "'s Total: " <<calculateHandValue(playerHand, playerNumCards);
    cout << endl;
    cout << "Dealer's Hand: ";
    displayHand(dealerHand, dealerNumCards);
    cout << endl;
    cout <<"Dealer Total: " <<calculateHandValue(dealerHand, dealerNumCards);
    cout << endl;

    // Player's turn
    while (true) {
        int choice;
        cout << "1. Hit" << endl;
        cout << "2. Stand" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            playerHand[playerNumCards++] = deck[numCards++];
            cout << playerName <<"'s Hand: ";
            displayHand(playerHand, playerNumCards);
            cout << endl;           
            cout << playerName << "'s Total: " << calculateHandValue(playerHand, playerNumCards);
            cout << endl;

            if (calculateHandValue(playerHand, playerNumCards) > BLACKJACK_VALUE) {
                cout << "Player busts! You lose." << endl;
                playerBalanceChange = -10;
                break;
            }
        } else if (choice == 2) {
            break;
        }
    }

    // Dealer's turn
    while (calculateHandValue(dealerHand, dealerNumCards) < DEALER_MIN_VALUE) {
        dealerHand[dealerNumCards++] = deck[numCards++];
    }
    cout << "Dealer's Hand: ";
    displayHand(dealerHand, dealerNumCards);
    cout << endl;    
    cout << "Dealer's Total: " <<calculateHandValue(dealerHand, dealerNumCards);
    cout << endl;

    // Determine the winner
    int playerValue = calculateHandValue(playerHand, playerNumCards);
    int dealerValue = calculateHandValue(dealerHand, dealerNumCards);

    if ((playerValue > dealerValue || dealerValue > BLACKJACK_VALUE) && playerValue < BUST_BARRIER) {
        cout << playerName << " wins!" << endl;
        playerBalanceChange = betamount;
    } else if (dealerValue > playerValue || playerValue > BLACKJACK_VALUE) {
        cout << "Dealer wins!" << endl;
        playerBalanceChange = -betamount;
    } else {
        cout << "Push! It's a tie." << endl;
    }

    // Update player's bank balance
    bankBalance += playerBalanceChange;
    cout << "-----------------------------" << endl;
    cout << "Player: " << playerName << endl;
    cout << "Balance: R" << bankBalance << endl;
    cout << "-----------------------------" << endl;
}

int main()
{
    string playerName;
    int bankBalance;
    int betamount;

    cout << "Welcome to Blackjack!" << endl;
    cout << "Please enter your name: ";
    cin >> playerName;

    cout << "What is your starting bank balance?" << endl;
    cin >> bankBalance;

    char playAgain;
    do {
        cout << "How much would you like to gamble?" << endl;
        cin >> betamount;
        playBlackjack(playerName, bankBalance,betamount);

        cout << "Play again? (Y/N): ";
        cin >> playAgain;
    } while (playAgain == 'Y' || playAgain == 'y');

    cout << "Thank you for playing! Goodbye!" << endl;

    return 0;
}