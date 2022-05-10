#include <iostream>
#include "EventParser.h"
#include "AthletesParser.h"
#include "Competitor.h"
#include "Sport.h"
#include "Game.h"
#include "Country.h"
#include "People.h"
#include "DataManipulation.h"

//TODO finish filter methods, resolve todo isues in those files and finish filters
//TODO consult

int main() {
    People athletes = People::getInstance();
    // TODO sredi kod + destruktori???, SHARED POINTER
    EventParser evParser;
    evParser.eventParsing("C:\\Users\\Lenovo\\CLionProjects\\POOP\\test.txt", 2004);
    auto competitors = evParser.getCompetitors();
    auto sports = evParser.getSports();
    auto games = evParser.getGames();
    auto countries = evParser.getCountries();
    auto athletesId = evParser.getAthleteIds();

    AthetesParser athParser(athletesId);
    athParser.athletesParse("C:\\Users\\Lenovo\\CLionProjects\\POOP\\athletesFile.txt", athletes);

    DataManipulation dm(competitors, sports, *games, *countries, &athletes);
    int p = dm.numberOfPlayers(Filter("Sailing", "Italy", 2004, "Team", "Gold"));
    int k = dm.numOfDisciplines(Filter("Sailing"));
    double h = dm.averageAthletesHeight(Filter("Sailing", "New Zealand", 2004));
    double w = dm.averageAthletesWeight(Filter("Sailing", "New Zealand", 2004));
    return 0;
}
