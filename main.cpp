#include "bits/stdc++.h"
#include "bleh.h"
#include "json.hpp"

using namespace std;


struct Movie {
    int id;
    string title, releaseDate;
    double budget;
    vector<string> cast, category;
    
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
        int pos=str.find(word);
        while(pos!=string::npos)
        {
            if((pos==0 || !isalnum(str[pos-1])) && (pos+word.size()==str.size() || !isalnum(str[pos+word.length()]))) return true;
            pos=str.find(word, pos+1);
        }
        return false;
    }

    void toLower(string& s)
    {
        for(char& c : s) c=tolower(c);
    }

    vector<Movie> searchMovies(string& titleQuery, string& castQuery, string& categoryQuery)
    {
        vector<Movie> result;
        for (auto& p : AllMovies)
        {
            Movie m=p.second;

            toLower(titleQuery), toLower(castQuery), toLower(categoryQuery);
            toLower(m.title);
            for(auto& s : m.category) toLower(s);
            for(auto& s : m.cast) toLower(s);

            vector<string> titleTokens=tokenize(m.title);
            vector<string> castTokens=tokenize(castQuery);
            vector<string> categoryTokens=tokenize(categoryQuery);

            bool matchesTitle=false;
            for(string& titleToken : titleTokens)
            {
                for(string& queryToken : tokenize(titleQuery))
                {
                    if(containsWord(titleToken, queryToken))
                    {
                        matchesTitle=true;
                        break;
                    }
                }
                if(matchesTitle) break;
            }
            if(titleQuery.empty()) matchesTitle=true;

            bool matchesCast=false;
            for(string& castToken : castTokens)
            {
                for(string& castMember : m.cast)
                {
                    for(string& queryToken : tokenize(castToken))
                    {
                        if(containsWord(castMember, queryToken))
                        {
                            matchesCast=true;
                            break;
                        }
                    }
                    if(matchesCast) break;
                }
                if(matchesCast) break;
            }
            if(castQuery.empty()) matchesCast=true;

            bool matchesCategory=false;
            for(string& categoryToken : categoryTokens)
            {
                for(string& catg : m.category) {
                    for(string& queryToken : tokenize(categoryToken))
                    {
                        if(containsWord(catg, queryToken))
                        {
                            matchesCategory=true;
                            break;
                        }
                    }
                    if(matchesCategory) break;
                }
                if(matchesCategory) break;
            }
            if(categoryQuery.empty()) matchesCategory=true;

            dbg(matchesTitle, matchesCast, matchesCategory);

            if(matchesTitle && matchesCast && matchesCategory) result.push_back(p.second);
        }
        sort(result.begin(), result.end(), Movie::cmp());
        return result;
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
    MovieLists ml;
    ml.ShowAllMovies();

    UserList ul;
    ul.addFavoriteMovie("user3@example.com", 15);
    ul.ShowAllUsers();

    system("pause");

    while(1)
    {
        system("cls");
        cout<<"Choose an option: \n";
        cout<<"0.Quit\n1. Search\n";
        int input; cin>>input;
        cin.ignore();
        if(input)
        {
            string title, cast, category;
            cout<<"1. Enter movie title: ", getline(cin, title);
            cout<<"2. Enter movie cast: ", getline(cin, cast);
            cout<<"3. Enter movie category: ", getline(cin, category);
            dbg(title,cast,category);

            vector<Movie> v=ml.searchMovies(title, cast, category);
            for(Movie& m : v) m.PrintMovie();

            system("pause");
        }
        else break;
    }
    
}