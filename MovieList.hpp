#pragma once

#include"all_headers.h"
#include"json.hpp"
#include"Helper.hpp"
#include"Movie.hpp"
using namespace std;


class MovieList
{
    string moviesJsonFileName="db/movies.json"; // File name for JSON data storing movie information
    map<int, Movie> AllMovies; // Map to store all movies by their Id

public:    
    MovieList()
    {
        readMoviesFromJsonFile(); // Reading movies from JSON file and initialize the AllMovies map
    }

    void readMoviesFromJsonFile()
    {
        // Open JSON file
        ifstream file(moviesJsonFileName);
        if (!file.is_open())
        {
            cerr<<"Error opening file!\n";
            return;
        }

        // Parse JSON data
        nlohmann::json jsonData;
        try {
            // file>>jsonData;
            jsonData=nlohmann::json::parse(file);
            // cout<<setw(4)<<jsonData<<'\n';
        }
        catch (nlohmann::json::parse_error& e) {
            cerr<<"Parse error: "<<e.what()<<'\n';
        }
        file.close();

        // Extract movie data from JSON and fill Movie objects
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
        // Open JSON file for writing
        ofstream file(moviesJsonFileName);
        if(!file.is_open())
        {
            cerr<<"Error opening file for writing: "<<moviesJsonFileName<<'\n';
            return;
        }

        // Convert Movie objects to JSON format
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

        // Write JSON data to file
        file<<jsonData.dump(4)<<"\n";
        file.close();
    }

    void DisplayMovies(vector<int> movieIds=vector<int>{-1}, string addi="  ")
    {
        // Display all movies if no specific IDs provided
        if(!movieIds.empty() && movieIds[0]==-1)
        {
            for(auto& p : AllMovies) p.second.PrintMovie(addi);
            return;
        }

        // Display movies with specified IDs
        for(int& i : movieIds) AllMovies[i].PrintMovie(addi);
    }

    bool MovieExists(int movieId)
    {
        // Check if movie with given ID exists in the movie list
        return AllMovies.find(movieId) != AllMovies.end();
    }

    vector<Movie> searchMovies(string& titleQuery, string& castQuery, string& categoryQuery, vector<int> movieIndices=vector<int>{})
    {
        // If no movie indices are provided then use the default movie list, else use the curated list
        map<int, Movie> movieMap;
        if(movieIndices.empty()) movieMap=AllMovies;
        else for(int& i : movieIndices) movieMap[i]=AllMovies[i];

        vector<Movie> result;
        for (auto& p : movieMap)
        {
            // Prepare search queries
            Movie m=p.second;

            Helper::ToLower(titleQuery), Helper::ToLower(castQuery), Helper::ToLower(categoryQuery);
            Helper::ToLower(m.title);
            for(auto& s : m.category) Helper::ToLower(s);
            for(auto& s : m.cast) Helper::ToLower(s);

            vector<string> titleTokens=Helper::tokenize(m.title);
            vector<string> castTokens=Helper::tokenize(castQuery);
            vector<string> categoryTokens=Helper::tokenize(categoryQuery);

            // Check for title match
            bool matchesTitle=false;
            for(string& titleToken : titleTokens)
            {
                for(string& queryToken : Helper::tokenize(titleQuery))
                {
                    if(Helper::containsWord(titleToken, queryToken))
                    {
                        matchesTitle=true;
                        break;
                    }
                }
                if(matchesTitle) break;
            }

            // Check for cast member match
            bool matchesCast=false;
            for(string& castToken : castTokens)
            {
                for(string& castMember : m.cast)
                {
                    for(string& queryToken : Helper::tokenize(castToken))
                    {
                        if(Helper::containsWord(castMember, queryToken))
                        {
                            matchesCast=true;
                            break;
                        }
                    }
                    if(matchesCast) break;
                }
                if(matchesCast) break;
            }

            // Check for category match
            bool matchesCategory=false;
            for(string& categoryToken : categoryTokens)
            {
                for(string& catg : m.category) {
                    for(string& queryToken : Helper::tokenize(categoryToken))
                    {
                        if(Helper::containsWord(catg, queryToken))
                        {
                            matchesCategory=true;
                            break;
                        }
                    }
                    if(matchesCategory) break;
                }
                if(matchesCategory) break;
            }

            // dbg(matchesTitle, matchesCast, matchesCategory);

            // Add matching movies to result vector
            if(titleQuery.empty() && castQuery.empty() && categoryQuery.empty()) result.push_back(p.second);
            else if(titleQuery.empty() && castQuery.empty() && matchesCategory) result.push_back(p.second);
            else if(titleQuery.empty() && matchesCast && categoryQuery.empty()) result.push_back(p.second);
            else if(matchesTitle && castQuery.empty() && categoryQuery.empty()) result.push_back(p.second);
            else if(matchesTitle || (matchesCast && matchesCategory)) result.push_back(p.second);
        }
        
        sort(result.begin(), result.end(), Movie::cmp()); // Sort search results
        return result;
    }
};