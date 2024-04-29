#include "bits/stdc++.h"
#include "bleh.h"
#include "json.hpp"

using namespace std;
using json=nlohmann::json;


struct Movie {
    string title, category, releaseDate;
    double budget;
    vector<string> cast;
};


struct User {
    string email;
    vector<Movie> favorites;
};


class MovieLists
{
public:
    vector<Movie> AllMovies;
    
    MovieLists()
    {
        // Open the JSON file
        ifstream file("movies.json");
        if (!file.is_open()) cerr<<"Error opening file!\n";

        // Parse the JSON
        json jsonData;
        try {
            jsonData=json::parse(file);
            // cout<<setw(4)<<jsonData<<'\n';
        }
        catch (json::parse_error& e) {
            cerr<<"Parse error: "<<e.what()<<'\n';
        }

        // Fill up the vector<Movie>
        for (auto& movieData : jsonData)
        {
            Movie movie;
            movie.title=movieData["title"];
            movie.cast=movieData["cast"];
            movie.category=movieData["category"];
            movie.releaseDate=movieData["release_date"];
            movie.budget=movieData["budget"];
            AllMovies.push_back(movie);
        }
    }

    void ShowAllMovies()
    {
        // auto cmp=[](Movie &a, Movie &b) {
        //     return a.title < b.title;
        // };
        // sort(AllMovies.begin(), AllMovies.end(), cmp);

        for(Movie& m : AllMovies)
        {
            cout<<"{\n";
            cout<<"  Title: "<<m.title<<",\n";
            cout<<"  Category: "<<m.category<<",\n";
            cout<<"  ReleaseDate: "<<m.releaseDate<<",\n";
            cout<<"  Budget: "<<m.budget<<",\n";
            cout<<"  Cast: "<<m.cast<<"\n";
            cout<<"}\n\n";
        }
    }
};





int main()
{
    MovieLists ml;
    ml.ShowAllMovies();
}