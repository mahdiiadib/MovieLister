#pragma once

#include"all_headers.h"
#include"json.hpp"
#include"Helper.hpp"
#include"Movie.hpp"
using namespace std;


class MovieList
{
    string moviesJsonFileName="db/movies.json";
    map<int, Movie> AllMovies;

public:    
    MovieList()
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
            // file>>jsonData;
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

    bool MovieExists(int movieId)
    {
        return AllMovies.find(movieId) != AllMovies.end();
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

            Helper::ToLower(titleQuery), Helper::ToLower(castQuery), Helper::ToLower(categoryQuery);
            Helper::ToLower(m.title);
            for(auto& s : m.category) Helper::ToLower(s);
            for(auto& s : m.cast) Helper::ToLower(s);

            vector<string> titleTokens=Helper::tokenize(m.title);
            vector<string> castTokens=Helper::tokenize(castQuery);
            vector<string> categoryTokens=Helper::tokenize(categoryQuery);

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