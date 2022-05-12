#include "EventParser.h"
#include "AthletesParser.h"
#include "People.h"
#include "DataManipulation.h"

//TODO finish filter methods, resolve todo isues in those files and finish filters
//TODO consult

int main() {
    People athletes = People::getInstance();
    // TODO sredi kod + destruktori???
    EventParser evParser;
    evParser.eventParsing("C:\\Users\\Lenovo\\CLionProjects\\POOP\\test.txt");

    AthetesParser athParser(evParser.getAthleteIds());
    athParser.athletesParse("C:\\Users\\Lenovo\\CLionProjects\\POOP\\athletesFile.txt", athletes);

    DataManipulation dm(&evParser, &athletes);
    int p = dm.numberOfPlayers(Filter());
    int k = dm.numOfDisciplines(Filter());
    double h = dm.averageAthletesHeight(Filter("", "Netherlands"));
    double w = dm.averageAthletesWeight(Filter("", "Netherlands"));
    int medals = dm.numberOfDifferentSportsWithMedal("Ukraine");
    //auto pk = dm.bestCountriesAtGame(2004, "Summer");
    auto pb = dm.bestCountries();
    auto cp = dm.olympicCities();
    Game ga("Summer", 2012, "London");
    Game gb("Summer", 1976, "Montreal");
    std::pair<Game, Game> gamess;
    gamess.first = ga;
    gamess.second = gb;
    auto s = dm.participatedAtGames(gamess);
    return 0;
}
