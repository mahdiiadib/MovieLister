#pragma once

#include"all_headers.h"
using namespace std;

struct User
{
    string email; // Email address of the user
    vector<int> favorites; // List of favorite movie IDs
    
    // Comparator for sorting users by email
    struct cmp
    {
        bool operator()(const User &a, const User &b) { return a.email < b.email; }
    };
};