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

using namespace std;

class DataManipulation {
private:
    vector<shared_ptr<Competitor>> competitors;
    set<Sport> sports;
    set<Game> games;
    set<Country> countries;
    People athletes = People::getInstance();
public:

    void setC(set<Country>&c){}
    //TODO constructor
    /*DataManipulation(vector<shared_ptr<Competitor>>& competitors, set<Sport> sports, set<Game> games,
                     set<Country> countries){
        this->competitors.insert(this->competitors.begin(), competitors.begin(), competitors.end());
        this->sports.insert(sports.begin(), sports.end());
        this->games.insert(games.begin(), games.end());
        this->countries.insert(games.begin(), games.end());
    }*/

    int numberOfPlayers(const Filter& f);
    int numOfDisciplines(const Filter& f);
    double averageAthletesHeight(const Filter& f);
    double averageAthletesWeight(const Filter& f);
};


#endif //POOP_DATAMANIPULATION_H
