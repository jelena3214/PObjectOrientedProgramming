//
// Created by Lenovo on 5/9/2022.
//

#ifndef POOP_DATAMANIPULATION_H
#define POOP_DATAMANIPULATION_H

#include <algorithm>
#include <vector>
#include "Filter.h"
#include "Competitor.h"
#include "Sport.h"
#include "People.h"
#include "Game.h"
#include "Country.h"

using namespace std;

class DataManipulation {
private:
    vector<shared_ptr<Competitor>> competitors;
    set<Sport> sports;
    set<Game> games;
    set<Country> countries;
    People* athletes;
public:
    //TODO constructor neki drugi nacin? ower of a parser??
    DataManipulation(vector<shared_ptr<Competitor>>& competitors, set<Sport>& sports, set<Game>& games,
                     set<Country>& countries, People* ath){
        this->competitors.insert(this->competitors.begin(), competitors.begin(), competitors.end());
        this->sports.insert(sports.begin(), sports.end());
        this->games.insert(games.begin(), games.end());
        this->countries.insert(countries.begin(), countries.end());
        athletes = ath;
    }


    int numberOfPlayers(Filter f);
    int numOfDisciplines(Filter f);
    double averageAthletesHeight(Filter f);
    double averageAthletesWeight(Filter f);
    vector<shared_ptr<Competitor>> getFilteredCompetitors(Filter f);
};


#endif //POOP_DATAMANIPULATION_H
