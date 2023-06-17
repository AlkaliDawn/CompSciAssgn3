#include <iostream>
#include <iomanip>
#include <cfenv>
#include <random>
#include <conio.h>

using std::cout;
using std::endl;
using std::rand;

#define reset "\033[0m"

#define swamp "\033[38;2;70;112;1m"
#define stone "\033[38;2;62;68;54m"
#define magic "\033[38;2;235;0;133m"

#define north "\033[38;2;88;129;166m\033[1m"
#define south "\033[38;2;209;174;69m\033[1m"
#define east "\033[38;2;184;94;204m\033[1m"
#define west "\033[38;2;96;209;160m\033[1m"
#define quit "\033[38;2;255;200;204m\033[1m"

#define cnorth "\033[38;2;95;136;173m"
#define csouth "\033[38;2;216;181;76m"
#define ceast "\033[38;2;191;101;211m"
#define cwest "\033[38;2;103;216;167m"
#define cquit "\033[38;2;255;217;222m"

#define good "\033[38;2;0;217;15m"
#define bad "\033[38;2;240;6;10m"
#define neutral "\033[38;2;240;255;31m"

std::vector<std::string> goodresults {
"\n\n\033[1mYou begin to walk down a hallway. Coming across a small hatch in the floor, \nyou open it and \033[4mhop down into a new room.\033[24m \nSomething deep inside you tells you that the exit is getting closer. \nLet's keep going. There are 4 routes to choose from.\n\033[0m",
"\n\n\033[1mYou walk for a bit, and come across a small opening. \nYou squeeze through the gap, \033[4mand find yourself at another intersection.\033[24m \nThe pull of energy gets a bit stronger. It seems to be equally strong from all 4 paths.\n\033[0m",
"\n\n\033[1mYou turn the rusted doorknob, and the door opens to a \033[4mlarge room with a fountain in the center.\033[24m \nYou feel the aura of something getting stronger. There are a few ways to go from here.\n\033[0m",
"\n\n\033[1mYou hop up the ledge. \033[4mA room with ornate stone arches\033[24m fills your vision. \nThe heart of the labyrinth beats louder in your head. 4 of the stone arches seem to stand out to you.\n\n\033[0m",
"\n\n\033[1mYou round the corner, and enter a library, filled with colorful, but weathered, leather bound books. \nYou find a disorganized map, but one path seems to glow in the darkness. \nYou follow the directions, and at the end of the path, \033[4myou enter a simple room\033[24m with 4 doors.\n\033[0m"
};

std::vector<bool> used_goodresults = {0, 0, 0, 0, 0}; // binary
std::vector<bool> temp_used_goodresults = {0, 0, 0, 0, 0};

std::vector<std::string> badresults {
"\n\n\033[1mA dismembered hand, covered in warts and moss grabs you! Wrong Direction! \nLet's try that again.\n\033[0m",
"\n\n\033[1mA strong beat of the labirynth's heart knocks you back. \nThat's probably not the right direction.\n\033[0m",
"\n\n\033[1mYou trip on a large stone. Unfortunately, that isn't a stone, it's a giant silverfish! \nYou manage to run away. It's probably a good idea to leave it alone.\n\033[0m",
"\n\n\033[1mThe ground beneath you crumbles, revealing a large pit, and you barely manage to grab the ledge. \nAfter you hoist yourself up, you can see that direction isn't going to work.\n\033[0m",
"\n\n\033[1mA piece of string glances your clothing, instantly setting into motion a complex series of traps. \nBarely making it out, you decide not to go that way.\n\033[0m",
"\n\n\033[1mYou grab a rusty doorknob and try to turn it, but it won't budge. \nIt's probably not worth it anyway, try a different path.\n\033[0m",
"\n\n\033[1mA cave-in is blocking your way, and theres no way to climb over. \nAnother path might be more accessable.\n\033[0m",
"\n\n\033[1mA magical barrier stops you in your tracks. Perhaps this is a sign to try something else.\n\033[0m",
"\n\n\033[1mYou start to get a bad feeling. A really, really bad feeling. \nSomething is very, very wrong. \nYou decide to turn pack and take a different path.\n\033[0m"
};

std::vector<bool> used_badresults = {0, 0, 0, 0, 0, 0, 0}; // binary
std::vector<bool> temp_used_badresults = {0, 0, 0, 0, 0, 0, 0}; 

std::vector<int> current_results = {0, 0, 0, 0}; // analog

std::vector<int> guesses = {0, 0, 0, 0}; // analog

int directiontoint(char x) { // Converts a direction to an integer
    switch (x) {
        case 'N':
        case 'n':
            return 0;
        case 'S':
        case 's':
            return 1;
        case 'E':
        case 'e':
            return 2;
        case 'W':
        case 'w':
            return 3;
    }
    return -1;
}

int main(void) {

    cout << std::setprecision(3); // Set decimal precision to 3 places for std_out
    std::fesetround(FE_DOWNWARD); // Set rounding mode to round down

    std::random_device rd;
    std::srand(rd());

    for (int i = 0; i < rand() % 16215; i++) {
        rand();
    }

    int num_rounds = 0; // Number of rounds

    int rightanswers = 0; // Number of right answers

    char input; // User input

    bool cancel = false; // Cancel the game

    bool level = true; // Level up

    bool get = true; // Get a new result

    // Intro text
    cout << "You are searching an " stone "underground " magic "mystical " swamp "labyrinth" reset ", filled with perils, twists, and turns.\n" reset "You have to find your way to the heart, using your psychic powers. \nYou can go " north "(N)orth, " south "(S)outh, " east "(E)ast, " west "(W)est, " reset "or " quit "(Q)uit. \n" reset;
    cout << "Which direction do you think you should go? \n\n > ";

    while (true) { // Main game loop
        if (rightanswers == 3) {
            cout << magic "\n\033[1mYou feel a surge of energy, and the heart of the labyrinth is revealed to you." good "You have won!\n\n\033[0m";
            cout << reset "\n It took you " << num_rounds << " rounds to reach the heart, so you were right " <<  3 / (float)num_rounds * 100 << "% of the time. (3/" << num_rounds << ")\n";
            cout << " In total, you...\n\n - went North " << guesses[0] << " time" << (guesses[0] != 1 ? "s" : "")  << " (" << (float)guesses[0] / (float)num_rounds * 100 << "%), \n";
            cout << " - went South " << guesses[1] << " time" << (guesses[1] != 1 ? "s" : "")  << " (" << (float)guesses[1] / (float)num_rounds * 100 << "%), \n";
            cout << " - went East " << guesses[2] << " time" << (guesses[2] != 1 ? "s" : "")  << " (" << (float)guesses[2] / (float)num_rounds * 100 << "%), \n";
            cout << " - and went West " << guesses[3] << " time" << (guesses[3] != 1 ? "s" : "")  << " (" << (float)guesses[3] / (float)num_rounds * 100 << "%). \n";
            break;
        }

        level = true; // Reset level

        int ans = std::rand() % 4; // Random answer

        temp_used_badresults = {0, 0, 0, 0, 0, 0, 0}; // Reset temp used bad results

        temp_used_goodresults = {0, 0, 0, 0, 0}; // Reset temp used good results

        for (int i = 0; i < 4; i++) { // For loop to set up results
            if (i != ans) {
                while (true) {
                    int a = rand() % badresults.size();
                    if (a != ans) { // if used and not the answer
                        if (used_badresults[a] || temp_used_badresults[a])
                            continue;
                        else { // break if not used
                            current_results[i] = a; // set current result
                            temp_used_badresults[a] = true; // set temp used
                            break;
                        } 
                    }
                    
                }
            }
        }

        while (true) { // While loop to set up answer
            current_results[ans] = rand() % goodresults.size(); // make sure good answer outcome is within range
            if (used_goodresults[current_results[ans]] || temp_used_goodresults[current_results[ans]]) { // if used
                continue;
            }
            else {// break if not used
                temp_used_goodresults[current_results[ans]] = true; // set temp used
                break;
            } 
        }

    while (level) { // While loop to keep answer the same for each level
        
        while (get) { // While Loop For Input
            input = ' ';
            if (std::string("nNsSwWeEqQ").find(input) != std::string::npos) // if last input was valid
                cout << "\nWhich direction do you think you should go? \nYou can go " north "(N)orth, " south "(S)outh, " east "(E)ast, " west "(W)est, " reset "or " quit "(Q)uit. \n\n " reset "> ";

            input = _getch(); // Get input
            
            get = false; // Reset get

            switch (input) {
            case 'N': // user goes north
            case 'n':
                cout << north << input << reset " ";
                cout << cnorth "You go north." reset << endl;
                break;
            case 'S': // user goes south
            case 's':
                cout << south << input << reset " ";                
                cout << csouth "You go south." reset << endl;
                break;
            case 'E': // user goes east
            case 'e':
                cout << east << input << reset " ";            
                cout << ceast "You go east." reset << endl;
                break;
            case 'W': // user goes west
            case 'w':
                cout << west << input << reset " ";            
                cout << cwest "You go west." reset << endl;
                break;
            case 'Q': // user quits
            case 'q':
                cout << quit << input << reset " ";            
                cout << cquit "Press Q again to confirm. ";
                input = _getch();
                if ( input == 'Q' || input == 'q') { // if user confirms quit
                    cout << bad "\033[1m" << input << " " reset;
                    cout << cquit "Exiting..." reset;
                    return 0;
                }
                else if (input != ' ') { // if user cancels quit
                    cout << bad "\033[1m" << input << " " reset;
                    cout << good "Cancelled.\n" reset;
                    cancel = true;
                }
                else { // if user cancels quit
                    cout << good "Cancelled.\n" reset;
                    cancel = true;
                }
                break;
            default:
                get = true; // reset get
                break;
            }
            cancel = false; // reset cancel
        }

        if (directiontoint(input) == ans) { // input is correct
            rightanswers++;

            if (rightanswers != 3) { // if not last level
                cout << endl << neutral << 3 - rightanswers << " Guess" << (rightanswers - 1 ? "" : "es") << " to go!! \n\n" << reset;
                cout << good << goodresults[current_results[ans]] << reset;
            }

            used_goodresults[current_results[ans]] = true; // set used good results to true
            level = false; // break level
            guesses[ans]++; // add to guesses
            get = true; // reset get
        }
        else { // input is incorrect
            cout << bad << badresults[current_results[directiontoint(input)]] << endl << reset; // print bad result
            used_badresults[current_results[directiontoint(input)]] = true; // set used bad results to true
            guesses[directiontoint(input)]++; // add to guesses
            get = true; // reset get
        }
        num_rounds++; // add to rounds
    }
    
    }  
    _getch(); // wait for input
    return 13;
}