#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include <iomanip>

// define ansi colorcodes using 24 bit color
#define GREEN "\033[38;2;7;217;28m"
#define RED "\033[38;2;255;36;58m"
#define BLUE "\033[38;2;0;121;241m"
#define RESET "\033[0m"

using namespace std;

int main(void) {
    long double investment = 0;      // Investment amount
    long double interest = 0;        // Interest rate
    long unsigned int years = 0;     // Number of years
    long double prev_investment;     // Previous investment amount
    long double start_investment;    // Starting investment amount
    int i;                           // Loop counter
    string input;                    // Input string
    
    cout << fixed << setprecision(2); // Set decimal precision to 2 places for std_out
    
    while(true) { // Loop until valid investment amt is entered
        cout << "Enter investment amount (in $): ";
        cin >> input;
        try {
            if (stold(input) > 0) {
                investment = stold(input);
                break;
            } else
                cout << "Invalid input! Investment Must Be A Decimal Or Number Greater Than 0. Please Try Again." << endl;
        }
        catch (...) { cout << "Invalid input! Investment Must Be A Decimal Or Number Greater Than 0. Please Try Again." << endl; }
    }
    while (true) { // Loop until valid interest rate is entered
        cout << "Enter interest rate (in %): ";
        cin >> input;
        try {
            if (stold(input) > 0) {
                interest = stold(input);
                break;
            } else
                cout << "Invalid input! Interest Must Be Decimal or Number Greater Than 0. Please Try Again." << endl;
        }
        catch (...) { cout << "Invalid input! Interest Must Be Decimal or Number Greater Than 0. Please Try Again." << endl; }
    }
    while (true) { // Loop until valid number of years is entered
        cout << "Enter number of years: ";
        cin >> input;
        try {
            if (stoul(input) > 0) {
                years = stoul(input);
                break;
            } else
                cout << "Invalid input! Number Of Years Must Be Number Greater Than 0. Please Try Again." << endl;
        }
        catch (...) { cout << "Invalid input! Number Of Years Must Be Number Greater Than 0. Please Try Again." << endl;}
    }
    
    start_investment = investment;
    
    cout << "STARTING INVESTMENT - $" << investment << endl; // Print starting investment amount
    for (i = 1; i < years + 1; ++i) { // Loop through each year
        prev_investment = investment; // Set previous investment amount
        investment += investment * (interest / 100); // Calculate new investment amount
        cout << "After Year " << i << " --> $" << prev_investment << " + (" << interest << "% * $" << prev_investment << ") = " << investment << endl; // Print investment amount for each year
    }
    cout << "So after " << i - 1 << " years, the investment will be worth $" << investment << endl; // Print final investment amount
    cout << GREEN "You earned $" << investment << " - $" << start_investment << " = $" << investment - start_investment << " in interest." << endl; // Print interest earned
    
    return 0;
}

