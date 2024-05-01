#pragma once

#include"all_headers.h"
#include"MovieList.hpp"
#include"UserList.hpp"
#include"Movie.hpp"
#include"Helper.hpp"
using namespace std;


class Session
{
    MovieList ml;
    UserList ul;
    string currentUserEmail;

    bool Login(string& email)
    {
        Helper::ToLower(email);
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
        // dbg(title,cast,category);

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

    void RunSession()
    {
        while(true)
        {
            Helper::ClearScreen();
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
                    Helper::Pause();
                    Helper::ClearScreen();
                    while(true)
                    {
                        Helper::ClearScreen();
                        cout<<"User: "<<currentUserEmail<<'\n';
                        cout<<"\n0. Exit Profile\n1. Search Movies\n2. View Personal Details\n3. Search in Favorites\n4. Add to Favorites\n5. Remove from Favorites\n6. Delete Profile\n";
                        cout<<"\nChoose an option: ";
                        string option; cin>>option, cin.ignore();

                        if(option=="0")
                        {
                            Logout();
                            break;
                        }
                        else if(option=="1") SearchMovies();
                        else if(option=="2") ul.ShowUserDetails(ml, currentUserEmail);
                        else if(option=="3")
                        {
                            vector<int> fav=ul.GetUser(currentUserEmail).favorites;
                            if(!fav.empty()) SearchMovies(fav);
                            else cout<<"\nYour Favorites list is empty.\n\n";
                        }
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
                        else if(option=="6")
                        {
                            cout<<"Are you sure you want to delete your profile? All your data will be lost.\n";
                            cout<<"\t0. NO\n\t1. YES\n";
                            cout<<"Confirm your choice: ";
                            string choice; cin>>choice, cin.ignore();
                            if(choice=="0") {}
                            else if(choice=="1")
                            {
                                ul.deleteUser(currentUserEmail);
                                currentUserEmail="";
                                break;
                            }
                            else cout<<"Invalid choice.\n";
                        }
                        else cout<<"Invalid option! Try again.\n";

                        Helper::Pause();
                    }
                }
            }
            else cout<<"Invalid input! Try again.\n";

            Helper::Pause();
        }
    }
};