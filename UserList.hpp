#pragma once

#include"all_headers.h"
#include"json.hpp"
#include"MovieList.hpp"
#include"User.hpp"
#include"Helper.hpp"
using namespace std;


class UserList
{
    string usersJsonFileName="db/users.json"; // File name for JSON data storing user information
    map<string, vector<int>> AllUsers; // Map to store all users by their email and favorites as key-value pair

public:
    UserList()
    {
        readUsersFromJsonFile(); // Reading users from JSON file and initialize the AllUsers map
    }

    void readUsersFromJsonFile()
    {
        // Open JSON file
        ifstream file(usersJsonFileName);
        if (!file.is_open()) cerr<<"Error opening file!\n";

        // Parse JSON data
        nlohmann::json jsonData;
        try {
            jsonData=nlohmann::json::parse(file);
        }
        catch (nlohmann::json::parse_error& e) {
            cerr<<"Parse error: "<<e.what()<<'\n';
        }
        file.close();

        // Extract user data from JSON and fill User objects
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
        // Open JSON file for writing
        ofstream file(usersJsonFileName);
        if(!file.is_open())
        {
            cerr<<"Error opening file for writing: "<<usersJsonFileName<<"\n";
            return;
        }

        // Convert User objects to JSON format
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

        // Write JSON data to file
        file<<jsonData.dump(4)<<"\n";
        file.close();
    }

    void ShowUserDetails(MovieList& ml, string email="")
    {
        // Display details of all users if no specific email provided
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

        // Display details of user with specified email
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
        // Check if user with given email exists and return that user object
        if(userExists(email)) return User{ email, AllUsers[email] };
        return User {"", vector<int>{}};
    }

    bool userExists(string email)
    {
        // Check if user with given email exists in the user list
        Helper::ToLower(email);
        return AllUsers.find(email)!=AllUsers.end();
    }

    bool isValidEmail(string& email)
    {
        // Validate email using regular expression pattern
        Helper::ToLower(email);
        regex emailPattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
        return regex_match(email, emailPattern);
    }

    void addUser(string email)
    {
        if(!isValidEmail(email)) cout<<email<<" is an invalid email address.\n"; // Check if email is valid
        else if(userExists(email)) cout<<"User "<<email<<" already exists\n"; // Check if user already exists
        else // Create and add new user to the user list
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
        // Check if user exists and delete user from user list
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
        if(!ml.MovieExists(movieId)) // Check if movie exists
        {
            cout<<"Movie ID: "<<movieId<<" is not present in the movie list\n";
            return;
        }

        if(AllUsers.find(email)!=AllUsers.end()) // Check if user exists
        {
            for(int& i : AllUsers[email])
            {
                if(i==movieId) // Check if movie already exists in user's favorites
                {
                    cout<<"Movie ID: "<<movieId<<" is already present in the favorites of "<<email<<"\n";
                    return;
                }
            }
            AllUsers[email].push_back(movieId); // Add movie to user's favorites list
            cout<<"Movie ID: "<<movieId<<" has been added to favorites of "<<email<<"\n";
        }
        else cout<<"User not found: "<<email<<'\n';
    }

    void removeFavoriteMovie(string email, int movieId)
    {
        if(AllUsers.find(email)!=AllUsers.end()) // Check if user exists
        {
            for(auto it=AllUsers[email].begin(); it!=AllUsers[email].end(); it++) // Search movieID in user's favorites
            {
                if(*it==movieId)
                {
                    AllUsers[email].erase(it); // Remove movie from user's favorites
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