#include <iostream>
#include <iomanip>
#include <random>
#include <conio.h>
#include <unordered_map>

#ifndef UNICODE
#define UNICODE
#endif

using std::cout;
using std::cin;
using std::endl;
using std::string;

std::vector<int> ways {
    0, 0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1
};

std::unordered_map<int, string> diceart = {
    {1, ".______________.\n"
        "|              |\n"
        "|              |\n"
        "|       &#     |\n"
        "|      +1      |\n"
        "|     ^#       |\n"
        "|              |\n"
        "!______________!\n" },

    {2, ".--------------.\n"
        "|              |\n"
        "|  &2          |\n"
        "|   #^         |\n"
        "|         &%   |\n"
        "|          2^  |\n"
        "|              |\n"
        "!--------------!\n" },

    {3, ".______________.\n"
        "|  _           |\n"
        "| (3)          |\n"
        "|       _      |\n"
        "|      (3)     |\n"
        "|           _  |\n"
        "|          (3) |\n"
        "!______________!\n" }, 

   {4,  ".______________.\n"
        "|              |\n"
        "|  4%      &4  |\n"
        "|  ``      ``  |\n"
        "|              |\n"
        "|  &4      4%  |\n"
        "|  ``      ``  |\n"
        "!--------------!\n" },    

    {5, ".--------------.\n"
        "| !5       !5  |\n"
        "|  ^        ^  |\n"
        "|      !5      |\n"
        "|       ^      |\n"
        "| !5        !5 |\n"
        "|  ^         ^ |\n"
        "!--------------!\n" },

    {6, ".______________.\n"
        "|              |\n"
        "|  [6]    [6]  |\n"
        "|              |\n"
        "|  [6]    [6]  |\n"
        "|              |\n"
        "|  [6]    [6]  |\n"
        "!______________!\n" }     

    

};

#define bold "\033[1m"

#define reset "\033[0m"

#define underline "\033[4m"

#define nounderline "\033[24m"

#define good "\033[38;2;0;217;15m"
#define bad "\033[38;2;240;6;10m"
#define neutral "\033[38;2;240;255;31m"

#define magic "\033[38;2;235;0;133m"

#define casino "\033[38;2;107;255;171m"

int main(void) {
    int bet;
    int roll;
    int money;
    int dice1;
    int dice2;
    int dicetotal;
    
    char x;

    string scrubber;

    bool hasRun = false;

    std::random_device rd;
    srand(rd());

    for (int i = 0; i < rand() % 5000; i++) {
        rand();
    }

    money = rand() % 1000 + 1;
    
    while (money > 1) {
        cout << bold underline casino "WELCOME" << (hasRun ? " BACK" : "") << " TO THE BET ZONE!!!" reset bold good "\nYOU HAVE " << money << " DOLLARS! \n\n" reset;
        hasRun = true;

        while (true) {
            cout << "How much would you like to bet?  > ";
            cin >> scrubber;
            try { bet = stoi(scrubber); } catch (...) { cout << "INVALID INPUT! Please enter an amount " underline "from $1" << " to $" << money << nounderline "\n\n";
                continue;
            } 
            if (bet < 0 || bet > money + 1) {
                cout << "INVALID INPUT! Please enter an amount " underline "from $1" << " to $" << money << nounderline "\n\n";
                continue;
            }
            else break;
        }

        while (true) {
            cout << "What do you think the roll will be?  > ";
            cin >> roll;
            if (roll < 2 || roll > 12) {
                cout << "INVALID INPUT! Please enter a number from 2 to 12\n";
                continue;
            }
            else break;
        }

        cout << "Rolling...";
        for (int i = 0; i < 13; i++) {
            _sleep(70);
            cout << ".";
        }
        dice1 = rand() % 6 + 1;
        dice2 = rand() % 6 + 1;
        dicetotal = dice1 + dice2;

        cout << "\n\n" magic << diceart.at(dice1) << diceart.at(dice2) << reset << endl;

        cout << "YOU ROLLED " << dice1 << " AND " << dice2 << " FOR A TOTAL OF " << dicetotal << "...\n";
        cout << "MEANING YOU ";

        if (roll == dicetotal) {
            cout << good "WIN $" << bet << " * 20 / " << ways[roll] << " ( there " << (ways[roll] == 1 ? "is " : "are ") << ways[roll] << " way" << (ways[roll] == 1 ? " " : "s ") << "to roll " << roll << ") !!!!!!!! CONGRATS!\n" reset ;
            money += bet * 20 / ways[roll];
        }

        else {
            cout << bad "LOST (" << (roll > dicetotal ? roll : dicetotal) << " - " << (roll < dicetotal ? roll : dicetotal) << ") * $" << bet << " * " << ways[roll] << " (there " << (ways[roll] == 1 ? "is " : "are ") << ways[roll] << " way" << (ways[roll] == 1 ? " " : "s ") << "to roll " << roll << ") = $" << (roll > dicetotal ? roll - dicetotal : dicetotal - roll) * bet * ways[roll] << "!!!! LOL GET REKTTTT!!!!!!!! XD XD\n\n" reset;
            money -= (roll > dicetotal ? roll - dicetotal : dicetotal - roll) * bet * ways[roll];
        }
        
        cout << neutral underline "Your current balance: $" << money << reset << endl;

    
        if (money > 0) {
            cout << "\n " underline "PLAY AGAIN ? (y/n)  >" reset " ";
            bool a = true;
            while (a) {
                x = getchar();
                switch (x) {
                    case 'Y':
                    case 'y': {
                        cout << reset "y\n\n\n";
                        a = false;
                        break;
                    }
                    case 'N':
                    case 'n': {
                        cout << reset "n";
                        cout << "\n\npress any key to exit...";
                        return 2;
                    }
                }
            }
        }
        else break;
    }
    cout << "\n\033[1m\033[4mSorry, you ran out of money!\033[0m \n\npress any key to exit...";
    _getch();
    return 1;
}