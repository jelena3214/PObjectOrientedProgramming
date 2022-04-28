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
#include "Games.h"
#include "Country.h"
#include "Athlete.h"
#include "Team.h"
#include <set>
using namespace std;

void eventParsing(const char* fileName, vector<Competitor*>& competitors, set<Sport*>& sports,
        set<Games*>& games, set<Country*>& countries, set<int>& athletesId);
Games* insertGame(const string& game, set<Games*>& games);
template<typename T>
T* insertT(const string& name, set<T*>& insertSet);
Event* insertEventToSport(const string& event, const string& type,const string& sport,set<Sport*> sports);
Athlete* findAthlete(vector<Athlete*> athletes, int id);

#endif //POOP_EVENTPARSER_H
