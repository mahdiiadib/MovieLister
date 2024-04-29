#include "bits/stdc++.h"
#include "bleh.h"
#include "json.hpp"

using namespace std;


struct Movie {
    string title, category, releaseDate;
    double budget;
    vector<string> cast;
    
    struct cmp {
        bool operator()(const Movie &a, const Movie &b) { return a.title < b.title; }
    };
};


struct User {
    string email;
    set<Movie, Movie::cmp> favorites;
    
    struct cmp {
        bool operator()(const User &a, const User &b) { return a.email < b.email; }
    };
};


class MovieLists
{
public:
    set<Movie, Movie::cmp> AllMovies;
    
    MovieLists()
    {
        ifstream file("movies.json");
        if (!file.is_open()) cerr<<"Error opening file!\n";

        nlohmann::json jsonData;
        try {
            jsonData=nlohmann::json::parse(file);
            // cout<<setw(4)<<jsonData<<'\n';
        }
        catch (nlohmann::json::parse_error& e) {
            cerr<<"Parse error: "<<e.what()<<'\n';
        }

        for (auto& movieData : jsonData)
        {
            Movie movie;
            movie.title=movieData["title"];
            movie.cast=movieData["cast"];
            movie.category=movieData["category"];
            movie.releaseDate=movieData["release_date"];
            movie.budget=movieData["budget"];
            AllMovies.insert(movie);
        }
    }

    static void ShowAllMovies(const set<Movie, Movie::cmp>& st, string addi="  ")
    {
        // sort(AllMovies.begin(), AllMovies.end(), Movie::cmp());
        for(const Movie& m : st)
        {
            cout<<addi.substr(0,addi.size()-2)<<"{\n";
            cout<<addi<<"  Title: "<<m.title<<",\n";
            cout<<addi<<"  Category: "<<m.category<<",\n";
            cout<<addi<<"  ReleaseDate: "<<m.releaseDate<<",\n";
            cout<<addi<<"  Budget: "<<m.budget<<",\n";
            cout<<addi<<"  Cast: "<<m.cast<<"\n";
            cout<<addi.substr(0,addi.size()-2)<<"}\n\n";
        }
    }
};


class UserList
{
public:
    set<User, User::cmp> AllUsers;
    
    UserList()
    {
        ifstream file("users.json");
        if (!file.is_open()) cerr<<"Error opening file!\n";

        nlohmann::json jsonData;
        try {
            jsonData=nlohmann::json::parse(file);
        }
        catch (nlohmann::json::parse_error& e) {
            cerr<<"Parse error: "<<e.what()<<'\n';
        }

        for (auto& userData : jsonData)
        {
            User user;
            user.email=userData["email"];
            for (auto& f : userData["favorites"])
            {
                Movie movie;
                movie.title = f["title"];
                movie.cast = f["cast"];
                movie.category = f["category"];
                movie.releaseDate = f["release_date"];
                movie.budget = f["budget"];
                user.favorites.insert(movie);
            }
            AllUsers.insert(user);
        }
    }

    void ShowAllUsers()
    {
        for(const User& u : AllUsers)
        {
            cout<<"{\n";
            cout<<"  email: "<<u.email<<",\n";
            cout<<"  Favorites: "<<"\n";
            MovieLists::ShowAllMovies(u.favorites, "    ");
            cout<<"}\n\n";
        }
    }
};


int main()
{
    MovieLists ml;
    // ml.ShowAllMovies(ml.AllMovies);

    UserList ul;
    ul.ShowAllUsers();
}