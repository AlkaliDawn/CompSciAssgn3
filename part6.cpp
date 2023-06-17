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

int getint(void) {
    string scrubber;
    cin >> scrubber;
    try { return stoi(scrubber); } catch (...) { return -1;}
}

int main(void) {
    char input;
    int ninput;
    int sum = 0;
    
    bool run = true;
    
    vector<int> sem1grades = {};
    vector<int> sem2grades = {};
    
    std::random_device rd;
    srand(rd());
    
    for (int i = 0; i < rand() % 5000; i++) {
        rand();
    }
    
    cout << good "Welcome. ";
    
    while (true) {
        cout << good "(I)nput data,  (P)rint average,  (H)onour roll status,  e(X)it.  Choice?  > " << reset;

        while (true) {
            input = _getch();
    
            if (string("IiPpHhXx").find(input) != string::npos) {
                cout << input << endl;
            }
            
            switch (input) {
                case 'I':
                case 'i': {
                    run = true;
                    while (run) {
                        cout << "(F)irst term or (S)econd term?  > ";
                        input = _getche();
                        cout << endl;
                        switch (input) {
                            case 'F':
                            case 'f': {
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
                            case 's': {
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
                case 'p': {
                    run = true;
                    while (run) {
                        cout << "(F)irst term, (S)econd term, or (O)verall?  > ";
                        input = _getche();
                        cout << endl;
                        switch (input) {
                            case 'F':
                            case 'f': {
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
                            case 's': {
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
                            case 'o': {
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
                case 'h': {
                    run = true;
                    while (run) {
                        cout << "(F)irst term, (S)econd term, or (O)verall?  > ";
                        input = _getche();
                        cout << endl;
                        switch (input) {
                            case 'F':
                            case 'f': {
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
                            case 's': {
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
                            case 'o': {
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
                case 'x': {
                    return 12;
                }
            }
            if (string("IiPpHhXx").find(input) != string::npos) {
                break;
            }
        }
    }
}