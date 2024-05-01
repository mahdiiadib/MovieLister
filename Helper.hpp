#pragma once

#include"all_headers.h"
using namespace std;

namespace Helper
{
    vector<string> tokenize(string& s)
    {
        vector<string> tokens;
        stringstream ss(s);
        string token;
        while(ss>>token) tokens.push_back(token);
        return tokens;
    }

    bool containsWord(string& str, string& word)
    {
        stringstream ss(str);
        string token;
        while(ss>>token) if(token==word) return true;
        return false;
    }

    void ToLower(string& s)
    {
        for(char& c : s) c=tolower(c);
    }

    void Pause()
    {
        #if defined(_WIN32) || defined(_WIN64)
            system("pause");
        #else
            cout<<"Press any key to continue . . . ";
            cin.get();
        #endif
    }

    void ClearScreen()
    {
        #if defined(_WIN32) || defined(_WIN64)
            system("cls");
        #else
            system("clear");
        #endif
    }
};