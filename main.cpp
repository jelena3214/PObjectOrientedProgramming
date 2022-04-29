#include <iostream>
#include "EventParser.h"
#include "AthletesParser.h"
#include "Competitor.h"
#include "Sport.h"
#include "Game.h"
#include "Country.h"
#include "People.h"

int main() {
    People athletes = People::getInstance();
    // TODO sredi kod + destruktori???, SHARED POINTER
    EventParser evParser;
    evParser.eventParsing("C:\\Users\\Lenovo\\CLionProjects\\POOP\\test.txt", 2012);
    auto competitors = evParser.getCompetitors();
    auto sports = evParser.getSports();
    auto games = evParser.getGames();
    auto countries = evParser.getCountries();
    auto athletesId = evParser.getAthleteIds();

    AthetesParser athParser(athletesId);
    athParser.athletesParse("C:\\Users\\Lenovo\\CLionProjects\\POOP\\athletesFile.txt", athletes);
    return 0;
}
