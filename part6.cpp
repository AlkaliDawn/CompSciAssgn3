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
    char input; // user input
    int ninput; // user input (number)
    int sum = 0; // sum of grades
    
    bool run = true; // run loop
    
    vector<int> sem1grades = {}; // first semester grades
    vector<int> sem2grades = {}; // second semester grades
    
    std::random_device rd;
    srand(rd());
    
    for (int i = 0; i < rand() % 5000; i++) {
        rand();
    }
    
    cout << good "Welcome. "; // welcome message
    
    while (true) {
        cout << good "(I)nput data,  (P)rint average,  (H)onour roll status,  e(X)it.  Choice?  > " << reset; // menu

        while (true) {
            input = _getch();
    
            if (string("IiPpHhXx").find(input) != string::npos) { // if input is valid
                cout << input << endl;
            }
            
            switch (input) { // menu
                case 'I':
                case 'i': { // input data
                    run = true;
                    while (run) {
                        cout << "(F)irst term or (S)econd term?  > ";
                        input = _getche();
                        cout << endl;
                        switch (input) {
                            case 'F':
                            case 'f': { // first term
                                cout << "How many first term courses did you take?  > ";
                                ninput = getint();
                                for (int i = 0, numcourses = ninput; i < numcourses; i++) {
                                    cout << "Enter First Term course " << i + 1 << " mark:  > ";
                                    ninput = getint();
                                    sem1grades.push_back(ninput);
                                    cout << endl;
                                    if (ninput > 84)
                                        cout << "CONGRATS – Your course " << i + 1 << " Mark qualifies you for an Award!!!\n";
                                }
                                break;
                            }
                            case 'S':
                            case 's': { // second term
                                cout << "How many second term courses did you take?  > ";
                                ninput = getint();
                                for (int i = 0, numcourses = ninput; i < numcourses; i++) {
                                    cout << "Enter Second Term course " << i + 1 << " mark:  > ";
                                    ninput = getint();
                                    sem2grades.push_back(ninput);
                                    cout << endl;
                                    if (ninput > 84)
                                        cout << "CONGRATS – Your course " << i + 1 << " Mark qualifies you for an Award!!!\n";
                                }
                                break;
                            }
                        }
                        if (string("FfSs").find(input) != string::npos) {
                            break;
                        }
                    }
                    break;
                }
                case 'P':
                case 'p': { // print average
                    run = true;
                    while (run) {
                        cout << "(F)irst term, (S)econd term, or (O)verall?  > ";
                        input = _getche();
                        cout << endl;
                        switch (input) {
                            case 'F':
                            case 'f': { // first term
                                if (!sem1grades.size()) {
                                    cout << "Before you can get an average, you need to enter data first!\n";
                                    input = ' ';
                                    run = false;
                                    break;
                                }
                                sum = 0;
                                for (int sem1grade : sem1grades) {
                                    sum += sem1grade;
                                }
                                cout << "Your 1st Term  Average is " << sum/sem1grades.size() << " from " << sem1grades.size() << " courses\n";
                                break;
                            }
                            case 'S':
                            case 's': { // second term
                                if (!sem2grades.size()) {
                                    cout << "Before you can get an average, you need to enter data first!\n";
                                    input = ' ';
                                    run = false;
                                    break;
                                }
                                sum = 0;
                                for (int sem2grade : sem2grades) {
                                    sum += sem2grade;
                                }
                                cout << "Your 2nd Term Average is " << sum/sem2grades.size() << " from " << sem2grades.size() << " courses\n";
                                break;
                            }
                            case 'O':
                            case 'o': { // overall
                                if (!sem2grades.size() || !sem1grades.size()) {
                                    cout << "Before you can get an average, you need to enter data first!\n";
                                    input = ' ';
                                    run = false;
                                    break;
                                }
                                sum = 0;
                                for (int sem2grade : sem2grades) {
                                    sum += sem2grade;
                                }
                                for (int sem1grade : sem1grades) {
                                    sum += sem1grade;
                                }
                                cout << "Your Overall Average is " << sum / ( sem2grades.size() + sem1grades.size() ) << " from " << sem2grades.size() + sem1grades.size() << " courses\n";
                                break;
                            }
                        }
                        if (string("FfSsOo").find(input) != string::npos) {
                            break;
                        }
                    }
                    break;
                }
                case 'H':
                case 'h': { // honour roll status
                    run = true;
                    while (run) {
                        cout << "(F)irst term, (S)econd term, or (O)verall?  > ";
                        input = _getche();
                        cout << endl;
                        switch (input) {
                            case 'F':
                            case 'f': { // first term
                                if (!sem1grades.size()) {
                                    cout << "Before you can get your honor roll status, you need to enter data first!\n";
                                    input = ' ';
                                    run = false;
                                    break;
                                }
                                sum = 0;
                                for (int sem1grade : sem1grades) {
                                    sum += sem1grade;
                                }
                                if ( sum / sem1grades.size() > 84) {
                                    cout << "You are on the 1st term honour roll - congratulations!\n";
                                }
                                else {
                                    cout << "You are not on the 1st term honour roll - sorry!\n";
                                }
                                break;
                            }
                            case 'S':
                            case 's': { // second term
                                if (!sem2grades.size()) {
                                    cout << "Before you can get your honor roll status, you need to enter data first!\n";
                                    input = ' ';
                                    run = false;
                                    break;
                                }
                                sum = 0;
                                for (int sem2grade : sem2grades) {
                                    sum += sem2grade;
                                }
                                if ( sum / sem2grades.size() > 84) {
                                    cout << "You are on the 2nd term honour roll - congratulations!\n";
                                }
                                else {
                                    cout << "You are not on the 2nd term honour roll - sorry!\n";
                                }
                                break;
                            }
                            case 'O':
                            case 'o': { // overall
                                if (!sem2grades.size() || !sem1grades.size()) {
                                    cout << "Before you can get your honor roll status, you need to enter data first!\n";
                                    input = ' ';
                                    run = false;
                                    break;
                                }
                                sum = 0;
                                for (int sem2grade : sem2grades) {
                                    sum += sem2grade;
                                }
                                for (int sem1grade : sem1grades) {
                                    sum += sem1grade;
                                }
                                if ( sum / ( sem2grades.size() + sem1grades.size() ) > 84) {
                                    cout << "You are on the overall honour roll - congratulations!\n";
                                }
                                else {
                                    cout << "You are not on the overall honour roll - sorry!\n";
                                }
                                break;
                            }
                        }
                        if (string("FfSsOo").find(input) != string::npos) {
                            break;
                        }
                    }
                    break;
                }
                case 'X':
                case 'x': { // exit
                    return 12;
                }
            }
            if (string("IiPpHhXx").find(input) != string::npos) { // if input is valid
                break;
            }
        }
    }
}