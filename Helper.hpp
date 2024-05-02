#pragma once

#include"all_headers.h"
using namespace std;

namespace Helper
{
    vector<string> tokenize(string& s)
    {
        // Tokenize the input string and return the tokens
        vector<string> tokens;
        stringstream ss(s);
        string token;
        while(ss>>token) tokens.push_back(token);
        return tokens;
    }

    bool containsWord(string& str, string& word)
    {
        // Tokenize the input string and check if it contains the word
        // Return true if word is found, otherwise false
        stringstream ss(str);
        string token;
        while(ss>>token) if(token==word) return true;
        return false;
    }

    void ToLower(string& s)
    {
        for(char& c : s) c=tolower(c); // Convert each character in the string to lowercase
    }

    bool isValidEmail(string& email)
    {
        // Validate email using regular expression pattern
        Helper::ToLower(email);
        regex emailPattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
        return regex_match(email, emailPattern);
    }

    void Pause() // Pause execution
    {
        #if defined(_WIN32) || defined(_WIN64)
            system("pause");
        #else
            cout<<"Press ENTER key to continue . . . ";
            cin.get();
        #endif
    }

    void ClearScreen() // Clear the console screen
    {
        #if defined(_WIN32) || defined(_WIN64)
            system("cls");
        #else
            system("clear");
        #endif
    }
};