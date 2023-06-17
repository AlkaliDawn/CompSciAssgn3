#include <iostream>
#include <string>
#include <random>
#include <conio.h>

using namespace std;

#define reset "\033[0m"

#define rock "\033[38;2;88;129;166m\033[1m"
#define scissor "\033[38;2;235;0;133m"
#define paper "\033[38;2;96;209;160m\033[1m"

#define good "\033[38;2;0;217;15m"
#define bad "\033[38;2;240;6;10m"
#define neutral "\033[38;2;240;255;31m"

int getint(void) { // Get an integer from the user
    string scrubber;
    cin >> scrubber;
    try { return stoi(scrubber); } catch (...) { return -1;}
}

int main(void) {
    int bet;        // bet amount
    char input;     // user input
    int money;      // money amount
    bool win;       // win or lose
    
    bool hasrun = false; // has run before
    
    std::random_device rd;
    srand(rd());
    
    for (int i = 0; i < rand() % 5000; i++) {
        rand();
    }
    
    money = rand() % 1000 + 1; // random money amount

    while (true) { // main loop
        cout << good "\nWelcome" << (hasrun ? " back " : " ")
             << "to the Dakota Casino, in the Rock, Paper, Scissors Area! You have $" << money << endl << reset;
        hasrun = true;
        while (true) { // get bet
            cout << neutral "\nHow much do you want to bet?  > " reset;
            bet = getint();
            if (bet > 0 && bet <= money) { // if bet is valid
                break;
            }
            cout << bad "Bet must be between $1 and $" << money << "!\n\n" reset;
        }
        
        win = rand() % 3 - 1; // win or lose
        
        cout << good "\nAlright! Rock, Paper, or Scissors (R | P | S)?  > " reset;
        
        while (true) { // get input
            input = _getch();
            
            switch (input) { // check input
                case 'R':
                case 'r': {
                    cout << rock << input << reset << endl;
                    if (win) { // win
                        cout << good "I choose Scissors. Since Rock crushes Scissors, you win $" << bet
                             << ". You now have $" << money + bet << reset;
                        money += bet;
                    } else { // lose
                        cout << bad "I choose Scissors. Since Paper covers Rock, you lose $" << bet
                             << ". You now have $" << money - bet << reset;
                        money -= bet;
                    }
                    break;
                }
                case 'P':
                case 'p': { // paper
                    cout << paper << input << reset << endl;
                    if (win) { // win
                        cout << good "I choose Rock. Since Paper covers Rock, you win $" << bet << ". You now have $"
                             << money + bet << reset;
                        money += bet;
                    } else { // lose
                        cout << bad "I choose Scissors. Since Scissors cut Paper, you lose $" << bet
                             << ". You now have $" << money - bet << reset;
                        money -= bet;
                    }
                    break;
                }
                case 'S':
                case 's': { // scissors
                    cout << scissor << input << reset << endl;
                    if (win) { // win
                        cout << good "I choose Paper. Since Scissors cut Paper, you win $" << bet << ". You now have $"
                             << money + bet << reset;
                        money += bet;
                    } else { // lose
                        cout << bad "I choose Rock. Since Rock crushes Scissors, you lose $" << bet
                             << ". You now have $" << money - bet << reset;
                        money -= bet;
                    }
                    break;
                }
            }
            if (string("RrPpSs").find(input) != string::npos) { // if input is valid
                break;
            }
        }
        if (money < 1) { // if out of money
            cout << bad "Sorry, you ran out of money!!\n" reset;
            _getch();
            return 0;
        }
        cout << good "\n\nWould you like to play again? ( Y / N )  > " reset;
        while (true) { // get input
            input = _getch();
            
            switch (input) { // check input
                case 'Y':
                case 'y': { // yes
                    cout << good << input << reset << endl;
                    cout << "\nAlright!...\n\n";
                    break;
                }
                case 'N':
                case 'n': { // no
                    cout << bad << input << reset << endl;
                    cout << neutral "You leave with $" << money << ". Come again soon!\n" reset;
                    _getch();
                    return 0;
                }
            }
            if (input == 'y' || input == 'Y') { // if input is valid
                break;
            }
        }
    }
}