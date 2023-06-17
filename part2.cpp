#include <iostream>
#include <string>
#include <iomanip>
#include <cfenv>

using namespace std;

    bool isprime;                   // Boolean to store whether or not number is prime
    long long int nums;             // Number of numbers to check
    long long int num_prime;        // Number of prime numbers
    string scrubber;                // String to store user input
    long long int input;            // Long long int to store user input
    long long int most_factors;     // Number with most factors
    long long int most_factors_num; // Number of factors of number with most factors
    long long int sum_factors;      // Sum of factors
    long long int num_factors;      // Number of factors
    long long int num_even = 0;     // Number of even numbers

string factors(long long int num) { // function to calculate factors of a number
    string factors = "";

    num_factors = 0;

    for (long long int i = 1; i < num + 1; i++) { // calculate factors
        if (num % i == 0 && i != num) {
            factors += to_string(i) + ", ";
            num_factors++;
        }
        else if (num % i == 0) { // on last factor, don't add comma
            factors += to_string(i);
            num_factors++;
        }
    }

    if (num_factors == 2) { // check if prime
        isprime = true; // if so, set isprime to true
        num_prime++;
    }
    else  // otherwise, set isprime to false
        isprime = false; 
    
    if (!isprime && num_factors > most_factors) {  // check if most factors
            most_factors = num_factors;
            most_factors_num = num;
        }

    else if (most_factors == 0 && most_factors_num == 0) { // if first number, set as most factors
            most_factors = num_factors;
            most_factors_num = num;
        }

    sum_factors += num_factors; // add to total number of factors for avg calc later

    return factors;
}

int main(void) { // main function

    cout << setprecision(3); // Set decimal precision to 3 places for std_out
    std::fesetround(FE_DOWNWARD); // Set rounding mode to round down
    while (true){
    cout << "Enter amount of numbers to check:  ";
    cin >> scrubber;
    try { nums = stoll(scrubber); }
    catch (...) { cout << "Invalid input! Amount must be a number greater than 0. Please try again." << endl;
    continue; 
    }
    if (nums > 0)
        break;
    else
        cout << "Invalid input! Amount must be a number greater than 0. Please try again." << endl;
    }

    for (long long int i = 1; i < nums + 1; i++) {
         while (true) {
            cout << "Enter value #" << i << " (an integer greater than 1): "; // Prompt user for input
            cin >> scrubber; // Store input in string

            try { input = stoll(scrubber); } // Attempt to convert string to long long int
            catch (...) {  // If conversion fails, print error message and restart loop
                cout << "Invalid input! Please enter an integer greater than 1." << endl;
                continue;
            } 

            if (input > 1)  // If conversion succeeds, check if input is greater than 2
                break; // If input is greater than 2, break out of loop

            else // If input is less than 2, print error message and restart loop
                cout << "Invalid input. Please enter an integer greater than 1." << endl; 
 
        }

        if (input % 2 == 0) // check if even
            num_even++;

        cout << input << " is " << (input % 2 == 1 ? "odd" : "even") << ", and its factors are " << factors(input) << "." << endl;

        cout << input << " has " << num_factors << " factors, so it is" << (isprime ? " prime. " : " composite. ") << endl;
    }

    if (num_even == 0)
        cout << "Of the " << nums << " number" << (nums ? "s" : "") << ", there was 0(0.000%) even numbers, and " << nums << "(100%) odd numbers." << endl;  
    else 
        cout << "Of the " << nums << " number" << (nums ? "s" : "") << ", there was " << num_even << "(" << (float)num_even / (float)nums * 100 + 0.0001 << "%) even numbers, and " << nums - num_even << "(" << (float)(nums - num_even) / (float)nums * 100 + 0.0001 << "%) odd numbers, \n";
        
  if (num_prime == 0)
        cout << "Of the " << nums << " number" << (nums ? "s" : "") << ", there was 0(0.000%) even numbers, and " << nums << "(100%) odd numbers." << endl;  
    else 
        cout << "Of the " << nums << " number" << (nums ? "s" : "") << ", there was " << num_prime << "(" << (float)num_prime / (float)nums * 100 + 0.0001 << "%) prime numbers, and " << nums - num_prime << "(" << (float)(nums - num_prime) / (float)nums * 100 + 0.0001 << "%) composite numbers.\n";
        
    cout << "On average, the numbers had " << (float)sum_factors / (float)nums << " factors, and the number with the most factors was " << most_factors_num << " with " << most_factors << " factors." << endl;

    return 0;

}