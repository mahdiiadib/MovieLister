#pragma once

#include"all_headers.h"
using namespace std;

struct User
{
    string email;
    vector<int> favorites;
    
    struct cmp
    {
        bool operator()(const User &a, const User &b) { return a.email < b.email; }
    };
};