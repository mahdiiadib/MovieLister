#pragma once

#include"all_headers.h"
using namespace std;

struct Movie
{
    int id;
    string title, releaseDate;
    double budget;
    vector<string> cast, category;
    
    struct cmp
    {
        bool operator()(const Movie &a, const Movie &b) { return a.title < b.title; }
    };

    void PrintMovie(string addi="  ")
    {
        cout<<addi.substr(0,addi.size()-2)<<"{\n";
        cout<<addi<<"  Id: "<<id<<",\n";
        cout<<addi<<"  Title: "<<title<<",\n";
        cout<<addi<<"  Category: "<<category<<",\n";
        cout<<addi<<"  ReleaseDate: "<<releaseDate<<",\n";
        cout<<addi<<"  Budget: "<<budget<<",\n";
        cout<<addi<<"  Cast: "<<cast<<"\n";
        cout<<addi.substr(0,addi.size()-2)<<"}\n\n";
    }
};