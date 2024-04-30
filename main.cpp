#include "bits/stdc++.h"
#include "bleh.h"
#include "json.hpp"

using namespace std;


struct Movie {
    int id;
    string title, category, releaseDate;
    double budget;
    vector<string> cast;
    
    struct cmp {
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


struct User {
    string email;
    vector<int> favorites;
    
    struct cmp {
        bool operator()(const User &a, const User &b) { return a.email < b.email; }
    };
};


class MovieLists
{
public:
    // vector<Movie> AllMovies;
    map<int,Movie> AllMovies;
    
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
            movie.id=movieData["id"];
            movie.title=movieData["title"];
            movie.cast=movieData["cast"];
            movie.category=movieData["category"];
            movie.releaseDate=movieData["release_date"];
            movie.budget=movieData["budget"];
            AllMovies[movie.id]=movie;
        }
    }

    static void ShowAllMovies(vector<int> movieIds=vector<int>{-1}, string addi="  ")
    {
        MovieLists ml;
        if(!movieIds.empty() && movieIds[0]==-1)
        {
            for(auto& p : ml.AllMovies) p.second.PrintMovie(addi);
            return;
        }
        for(int& i : movieIds) ml.AllMovies[i].PrintMovie(addi);
    }
};


class UserList
{
public:
    map<string, vector<int>> AllUsers;
    
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
            for (auto& f : userData["favorites"]) user.favorites.push_back(f);
            AllUsers[user.email]=user.favorites;
        }
    }

    void ShowAllUsers()
    {
        for(auto& p : AllUsers)
        {
            cout<<"{\n";
            cout<<"  email: "<<p.first<<",\n";
            cout<<"  Favorites: "<<"\n";
            // cout<<p.second<<'\n';
            MovieLists::ShowAllMovies(p.second, "    ");
            cout<<"}\n\n";
        }
    }

    void addUser(string email)
    {
        User newUser;
        newUser.email = email;
        AllUsers[email]=vector<int>{};
    }

    void addFavoriteMovie(string email, int movieId)
    {
        if(AllUsers.find(email)!=AllUsers.end())
        {
            AllUsers[email].push_back(movieId);
            cout<<"Movie ID: "<<movieId<<" added to favorites\n";
            return;
        }
        cout<<"User not found: "<<email<<'\n';
    }

    void removeFavoriteMovie(string email, int movieId)
    {
        if(AllUsers.find(email)!=AllUsers.end())
        {
            for(auto it=AllUsers[email].begin(); it!=AllUsers[email].end(); it++)
            {
                if(*it==movieId)
                {
                    AllUsers[email].erase(it);
                    cout<<"Movie ID: "<<movieId<<" removed from favorites\n";
                    return;
                }
            }
            cout<<"Movie ID: "<<movieId<<" not found in favorites\n";
            return;
        }
        cout<<"User not found: "<<email<<'\n';
    }
};


int main()
{
    // MovieLists ml;
    // ml.ShowAllMovies();

    // UserList ul;
    // ul.ShowAllUsers();

    UserList ul;
    ul.addFavoriteMovie("user3@example.com", 15);
    ul.ShowAllUsers();
}