#pragma once

#include"all_headers.h"
#include"json.hpp"
#include"MovieList.hpp"
#include"User.hpp"
#include"Helper.hpp"
using namespace std;


class UserList
{
    string usersJsonFileName="db/users.json";
    map<string, vector<int>> AllUsers;

public:
    UserList()
    {
        readUsersFromJsonFile();
    }

    void readUsersFromJsonFile()
    {
        ifstream file(usersJsonFileName);
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

    void ShowUserDetails(MovieList& ml, string email="")
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

    User GetUser(string email)
    {
        if(AllUsers.find(email) != AllUsers.end()) return User{ email, AllUsers[email] };
    }

    bool userExists(string email)
    {
        Helper::ToLower(email);
        return AllUsers.find(email)!=AllUsers.end();
    }

    bool isValidEmail(string& email)
    {
        Helper::ToLower(email);
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
            Helper::ToLower(email);
            newUser.email=email;
            AllUsers[email]=vector<int>{};
            cout<<"New user "<<email<<" has been added to user list\n";
        }
    }

    void deleteUser(string& email)
    {
        auto it=AllUsers.find(email);
        if (it!=AllUsers.end())
        {
            AllUsers.erase(it);
            cout<<"User with email '"<<email<<"' has been deleted successfully.\n";
        }
        else cout<<"User with email '"<<email<<"' is not found.\n";
    }

    void addFavoriteMovie(string email, int movieId)
    {
        MovieList ml;
        dbg(movieId);
        if(!ml.MovieExists(movieId))
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