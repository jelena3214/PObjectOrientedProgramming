//
// Created by Lenovo on 4/25/2022.
//

#ifndef POOP_EVENTPARSER_H
#define POOP_EVENTPARSER_H

#include<fstream>
#include<iostream>
#include<string>
#include "Competitor.h"
#include "Sport.h"
#include "Game.h"
#include "Country.h"
#include "Athlete.h"
#include "Team.h"
#include <set>

using namespace std;

class EventParser {
public:
    struct CountryPrtComp { //for comparing pointers in set of countries
        using is_transparent = void;
        bool operator()(const shared_ptr<Country>& e, const shared_ptr<Country>& e1) const {
            return *e < *e1;
        }
        bool operator()(const shared_ptr<Country>& e, const Country& e1) const {
            return *e < e1;
        }
        bool operator()(const Country& e, const shared_ptr<Country>& e1) const {
            return e < *e1;
        }
    };


    struct SportPrtComp { //for comparing pointers in set of countries
        using is_transparent = void;
        bool operator()(const shared_ptr<Sport>& e, const shared_ptr<Sport>& e1) const {
            return *e < *e1;
        }
        bool operator()(const shared_ptr<Sport>& e, const Sport& e1) const {
            return *e < e1;
        }
        bool operator()(const Sport& e, const shared_ptr<Sport>& e1) const {
            return e < *e1;
        }
    };

private:
    vector<shared_ptr<Competitor>> competitors;
    set<shared_ptr<Sport>, SportPrtComp> sports;
    set<Game> gamesSet;
    set<shared_ptr<Country>, CountryPrtComp> countrySet;
    set<int> athletesId;

    //shared_ptr<Event> insertEventToSport(const string &event, const string &type, const string &sport);

public:
    void eventParsing(const char *fileName, int year = -1);

    vector<shared_ptr<Competitor>> &getCompetitors() { return competitors; }

    set<shared_ptr<Sport>, SportPrtComp>& getSports() { return sports; }

    set<Game>& getGames() { return gamesSet; }

    set<shared_ptr<Country>, CountryPrtComp>& getCountries() { return countrySet; }

    set<int>& getAthleteIds() { return athletesId; }

};


#endif //POOP_EVENTPARSER_H
