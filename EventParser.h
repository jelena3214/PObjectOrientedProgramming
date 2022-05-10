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

class EventParser{
private:
    vector<shared_ptr<Competitor>> competitors;
    set<Sport> sports;
    set<Game> gamesSet;
    set<Country> countrySet;
    set<int> athletesId;

    shared_ptr<Event> insertEventToSport(const string& event, const string& type,const string& sport);
public:
    void eventParsing(const char* fileName, int year = -1);
    vector<shared_ptr<Competitor>>& getCompetitors() {return competitors;}
    set<Sport>& getSports(){return sports;}
    set<Game>& getGames(){return gamesSet;}
    set<Country>* getCountries(){return &countrySet;}
    set<int>& getAthleteIds(){return athletesId;}
};




#endif //POOP_EVENTPARSER_H
