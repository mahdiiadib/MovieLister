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
    string moviesJsonFileName="movies.json";
    map<int,Movie> AllMovies;
    
    MovieLists()
    {
        readMoviesFromJsonFile();
    }

    void readMoviesFromJsonFile()
    {
        ifstream file(moviesJsonFileName);
        if (!file.is_open())
        {
            cerr<<"Error opening file!\n";
            return;
        }

        nlohmann::json jsonData;
        try {
            jsonData=nlohmann::json::parse(file);
            // cout<<setw(4)<<jsonData<<'\n';
        }
        catch (nlohmann::json::parse_error& e) {
            cerr<<"Parse error: "<<e.what()<<'\n';
        }
        file.close();

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

    void writeMoviesToJsonFile()
    {
        ofstream file(moviesJsonFileName);
        if(!file.is_open())
        {
            cerr<<"Error opening file for writing: "<<moviesJsonFileName<<'\n';
            return;
        }

        nlohmann::json jsonData;
        for(auto& p : AllMovies)
        {
            Movie& movie=p.second;
            jsonData.push_back({
                {"id", movie.id},
                {"title", movie.title},
                {"cast", movie.cast},
                {"category", movie.category},
                {"release_date", movie.releaseDate},
                {"budget", movie.budget}
            });
        }

        // file<<setw(4)<<jsonData<<"\n";
        file<<jsonData.dump(4)<<"\n";
        file.close();
    }

    void DisplayMovies(vector<int> movieIds=vector<int>{-1}, string addi="  ")
    {
        if(!movieIds.empty() && movieIds[0]==-1)
        {
            for(auto& p : AllMovies) p.second.PrintMovie(addi);
            return;
        }
        for(int& i : movieIds) AllMovies[i].PrintMovie(addi);
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

    vector<Movie> searchMovies(string& titleQuery, string& castQuery, string& categoryQuery, vector<int> movieIndices=vector<int>{})
    {
        map<int, Movie> movieMap;
        if(movieIndices.empty()) movieMap=AllMovies;
        else for(int& i : movieIndices) movieMap[i]=AllMovies[i];

        vector<Movie> result;
        for (auto& p : movieMap)
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

            dbg(matchesTitle, matchesCast, matchesCategory);

            if(titleQuery.empty() && castQuery.empty() && categoryQuery.empty()) result.push_back(p.second);
            else if(titleQuery.empty() && castQuery.empty() && matchesCategory) result.push_back(p.second);
            else if(titleQuery.empty() && matchesCast && categoryQuery.empty()) result.push_back(p.second);
            else if(matchesTitle && castQuery.empty() && categoryQuery.empty()) result.push_back(p.second);
            else if(matchesTitle || (matchesCast && matchesCategory)) result.push_back(p.second);
        }
        sort(result.begin(), result.end(), Movie::cmp());
        return result;
    }
};


class UserList
{
public:
    string usersJsonFileName="users.json";
    map<string, vector<int>> AllUsers;
    
    UserList()
    {
        readUsersFromJsonFile();
    }

    void readUsersFromJsonFile()
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
        file.close();

        for (auto& userData : jsonData)
        {
            User user;
            user.email=userData["email"];
            for (auto& f : userData["favorites"]) user.favorites.push_back(f);
            AllUsers[user.email]=user.favorites;
        }
    }

    void writeUsersToJsonFile()
    {
        ofstream file(usersJsonFileName);
        if(!file.is_open())
        {
            cerr<<"Error opening file for writing: "<<usersJsonFileName<<"\n";
            return;
        }

        nlohmann::json jsonData;
        for (auto& p : AllUsers)
        {
            string email=p.first;
            vector<int>& favorites=p.second;
            jsonData.push_back({
                {"email", email},
                {"favorites", favorites}
            });
        }

        file<<jsonData.dump(4)<<"\n";
        file.close();
    }

    void ShowUserDetails(MovieLists& ml, string email="")
    {
        if(email=="")
        {
            for(auto& p : AllUsers)
            {
                cout<<"{\n";
                cout<<"  email: "<<p.first<<",\n";
                cout<<"  Favorites: "<<"\n";
                ml.DisplayMovies(p.second, "    ");
                cout<<"}\n\n";
            }
        }
        else
        {
            if(userExists(email))
            {
                cout<<"{\n";
                cout<<"  email: "<<email<<",\n";
                cout<<"  Favorites: "<<"\n";
                ml.DisplayMovies(AllUsers[email], "    ");
                cout<<"}\n\n";
            }
            else cout<<"User "<<email<<" does not already exist\n";
        }
    }

    bool userExists(string email)
    {
        return AllUsers.find(email)!=AllUsers.end();
    }

    bool isValidEmail(string& email)
    {
        regex emailPattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
        return regex_match(email, emailPattern);
    }

    void addUser(string email)
    {
        if(!isValidEmail(email)) cout<<email<<" is an invalid email address.\n";
        else if(userExists(email)) cout<<"User "<<email<<" already exists\n";
        else
        {
            User newUser;
            newUser.email=email;
            AllUsers[email]=vector<int>{};
            cout<<"New user "<<email<<" has been added to user list\n";
        }
    }

    void addFavoriteMovie(string email, int movieId)
    {
        MovieLists ml;
        if(ml.AllMovies.find(movieId) == ml.AllMovies.end())
        {
            cout<<"Movie ID: "<<movieId<<" is not present in the movie list\n";
            return;
        }

        if(AllUsers.find(email)!=AllUsers.end())
        {
            for(int& i : AllUsers[email])
            {
                if(i==movieId)
                {
                    cout<<"Movie ID: "<<movieId<<" is already present in the favorites of "<<email<<"\n";
                    return;
                }
            }
            AllUsers[email].push_back(movieId);
            cout<<"Movie ID: "<<movieId<<" has been added to favorites of "<<email<<"\n";
        }
        else cout<<"User not found: "<<email<<'\n';
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
                    cout<<"Movie ID: "<<movieId<<" has been removed from favorites of "<<email<<"\n";
                    return;
                }
            }
            cout<<"Movie ID: "<<movieId<<" is not found in favorites of "<<email<<"\n";
            return;
        }
        cout<<"User not found: "<<email<<'\n';
    }
};


class Session
{
    MovieLists ml;
    UserList ul;
    string currentUserEmail;

    bool Login(string& email)
    {
        if (ul.userExists(email)) return currentUserEmail=email, cout<<"Logged in as "<<email<<"\n", true;
        else return cout<<"User not found: "<<email<<"\n", false;
    }

    void Logout()
    {
        cout<<"Logged out from "<<currentUserEmail<<"\n";
        currentUserEmail="";
    }

    void SearchMovies(vector<int> movieIndices=vector<int>{})
    {
        string title, cast, category;
        cout<<"1. Enter Movie Title (Press ENTER without typing any characters to give blank input): ", getline(cin, title);
        cout<<"2. Enter Movie Cast (Press ENTER without typing any characters to give blank input): ", getline(cin, cast);
        cout<<"3. Enter Movie Category (Press ENTER without typing any characters to give blank input): ", getline(cin, category);
        dbg(title,cast,category);

        vector<Movie> v=ml.searchMovies(title, cast, category, movieIndices);
        for(Movie& m : v) m.PrintMovie();
    }

public:
    Session()
    {
        currentUserEmail="";
    }

    ~Session()
    {
        ml.writeMoviesToJsonFile();
        ul.writeUsersToJsonFile();
    }

    void StartSession()
    {
        while(true)
        {
            system("cls");
            cout<<"0. Quit\n1. Search Movies\n2. Register\n3. Enter Profile\n";
            cout<<"\nChoose an option: ";
            string input; cin>>input, cin.ignore();

            if(input=="0") break;
            else if(input=="1") SearchMovies();
            else if(input=="2")
            {
                string email;
                cout<<"Enter email: \n", getline(cin, email);
                ul.addUser(email);
            }
            else if(input=="3")
            {
                string email;
                cout<<"Enter email: \n", getline(cin, email);

                if(Login(email))
                {
                    system("pause");
                    system("cls");
                    while(true)
                    {
                        system("cls");
                        cout<<"User: "<<currentUserEmail<<'\n';
                        cout<<"\n0. Exit Profile\n1. Search Movies\n2. View Personal Details\n3. Search in Favorites\n4. Add to Favorites\n5. Remove from Favorites\n";
                        cout<<"\nChoose an option: ";
                        string option; cin>>option, cin.ignore();

                        if(option=="0")
                        {
                            Logout();
                            break;
                        }
                        else if(option=="1") SearchMovies();
                        else if(option=="2") ul.ShowUserDetails(ml, currentUserEmail);
                        else if(option=="3") SearchMovies(ul.AllUsers[currentUserEmail]);
                        else if(option=="4")
                        {
                            int movieId;
                            cout<<"Enter movie index to add: ", cin>>movieId, cin.ignore();
                            ul.addFavoriteMovie(currentUserEmail, movieId);
                        }
                        else if(option=="5")
                        {
                            int movieId;
                            cout<<"Enter movie index to remove: ", cin>>movieId, cin.ignore();
                            ul.removeFavoriteMovie(currentUserEmail, movieId);
                        }
                        else cout<<"Invalid option! Try again.\n";

                        system("pause");
                    }
                }
            }
            else cout<<"Invalid input! Try again.\n";

            system("pause");
        }
    }
};


int main()
{
    Session session;
    session.StartSession();
}