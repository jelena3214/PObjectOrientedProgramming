//
// Created by Lenovo on 5/9/2022.
//

#ifndef POOP_DATAMANIPULATION_H
#define POOP_DATAMANIPULATION_H

#include <algorithm>
#include <vector>
#include "Filter.h"
#include "EventParser.h"
#include "AthletesParser.h"
#include <deque>

using namespace std;

class DataManipulation {
private:
    EventParser *evParser;
    People *athletes;
public:

    DataManipulation(EventParser *ev, People *ath) {
        evParser = ev;
        athletes = ath;
    }

    /**
     * Basic filtering options
     */
    int numberOfPlayers(Filter f);

    int numOfDisciplines(Filter f);

    double averageAthletesHeight(Filter f);

    double averageAthletesWeight(Filter f);

    vector<shared_ptr<Competitor>> getFilteredCompetitors(Filter f);

    /**
     * Advanced data operations
     */
    int numberOfDifferentSportsWithMedal(const string &country);

    deque<Country *> bestCountriesAtGame(int year, const string &season);

    set<Country *> bestCountries();

    vector<shared_ptr<Person>> bestYoungestAthletes();

    set<pair<Country, shared_ptr<Person>>> wonIndividualAndTeamMedal();

    set<shared_ptr<Person>> participatedAtGames(pair<Game, Game>);

    vector<shared_ptr<Competitor>> countryTeamsAtGame(int year, const string &season, const string &country);

    set<string> olympicCities();

};


#endif //POOP_DATAMANIPULATION_H
