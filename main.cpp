/*
Gytis Pankevicius
Week 13 - Passcode Derivation
Finds the shortest possible passcode from Project Euler #79 - correct output: 73162890
*/


//0 problems with CPPCheck
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

//Ensures digit is in the correct position
void insert_digit(std::vector<char>& passcode, char digit, char must_be_before) {
    auto it_digit = find(passcode.begin(), passcode.end(), digit);
    auto it_before = find(passcode.begin(), passcode.end(), must_be_before);

    if (it_digit == passcode.end()) {
        //If digit not in the passcode, insert it
        if (it_before == passcode.end()) {
            //Append if "must_be_before" is not in the passcode
            passcode.push_back(digit);
        } else {
            //Insert digit before "must_be_before"
            passcode.insert(it_before, digit);
        }
    } else {
        //If the digit is already in passcode, move it if needed
        if (it_before != passcode.end() && it_digit > it_before) {
            passcode.erase(it_digit);
            passcode.insert(it_before, digit);
        }
    }
}

//Input validation for login attempts
bool validateLoginAttempt(const std::string& attempt) {
    //Input validation for length
    if (attempt.length() != 3) {
        std::cerr << "Invalid login attempt length: " << attempt << "\n";
        return false;
    }
    //Input validation for characters
    for (char ch : attempt) {
        if (!isdigit(ch)) {
            std::cerr << "Invalid character in login attempt: " << attempt << "\n";
            return false;
        }
    }
    return true;
}

int main () {
    //Using std::string and constant
    //List of login attempts
    const std::vector<std::string> login_attempts = {
        "319", "680", "180", "690", "129", "620", "762",
        "689", "318", "368", "710", "720", "629",
        "168", "160", "716", "731", "736", "729", "316"
    };

    //Passcode sequence
    std::vector<char> passcode;

    //Exception handling
    for (const std::string& attempt : login_attempts) {
        if (!validateLoginAttempt(attempt)) {
            std::cerr << "Skipping invalid login attempt: " << attempt << "\n";
            continue;
        }
        //Integral vulnerabilities security using size_t
        for (size_t i = 0; i < attempt.size(); i++) {
            char current = attempt[i];
            for (size_t j = i + 1; j < attempt.size(); j++) {
                char must_be_before = attempt[j];
                insert_digit(passcode, current, must_be_before);
            }

            //Ensure the current digit is in the passcode
            if (find(passcode.begin(), passcode.end(), current) == passcode.end()) {
                passcode.push_back(current);
            }
        }
    }

    //Output the passcode
    std::cout << "Shortest passcode: ";
    for (char digit: passcode) {
        std::cout << digit;
    }
    std::cout << "\n";

    return 0;   
}
