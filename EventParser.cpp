//
// Created by Lenovo on 4/25/2022.
//

#include "EventParser.h"
#include "EventTypeClass.h"
#include "Exceptions.h"
#include<regex>

using namespace std;

void EventParser::eventParsing(const char *fileName, int findForYear) {
    fstream eventFile;
    eventFile.open(fileName, ios::in);

    if (!eventFile)throw FileNotFound();

    string tmp;

    regex reLine("([^!]+)!([^!]+)!([^!]+)!([^!]+)!([^!]+)!([^!]+)!([^!]+)!([^\\n]*)", regex::optimize);
    regex reYearSeason("(\\d+) ([^\\n]+)", regex::optimize);
    regex reIdParse("\\, ", regex::optimize);

    smatch matchLine;
    smatch matchYearSeason; //Year & season

    bool group = (findForYear == -1); //Group regime

    while (getline(eventFile, tmp)) {
        if (regex_search(tmp, matchLine, reLine)) {
            string games = matchLine.str(1);

            regex_search(games, matchYearSeason, reYearSeason);
            int year = stoi(matchYearSeason.str(1));
            string season = matchYearSeason.str(2);

            if (!group) {
                if (year != findForYear)continue;
            }

            string city = matchLine.str(2);
            string sport = matchLine.str(3);
            string event = matchLine.str(4);
            string type = matchLine.str(5);
            string country = matchLine.str(6);
            string ids = matchLine.str(7);
            string medal = matchLine.str(8);

            //Insert game
            auto tmpGamePair = gamesSet.insert(Game(season, year, city));
            auto& currentGame = *tmpGamePair.first;

            //Insert country
            auto tmpPair = countrySet.find(Country(country));
            shared_ptr<Country> currentCountry;
            if(tmpPair == countrySet.end()){ //Doesn't exist
                auto insertRes = countrySet.insert(make_shared<Country>(Country(country)));
                currentCountry = *insertRes.first;
            }else{
                currentCountry = *tmpPair;
            }

            //Insert sport
            auto tmpSportPair = sports.find(Sport(sport));
            shared_ptr<Sport> currentSport;
            if(tmpSportPair == sports.end()){ //Doesn't exist
                auto insertRes = sports.insert(make_shared<Sport>(Sport(sport)));
                currentSport = *insertRes.first;
            }else{
                currentSport = *tmpSportPair;
            }

            //Insert Event to sport
            auto currentEvent = currentSport->addEvent(event, type);
            currentEvent->setSport(currentSport);

            //Make new Competitor
            shared_ptr<Competitor> newCompetitor;
            if (ids[0] == '[') { //Team
                shared_ptr<Team> newTeam = make_shared<Team>();
                ids = ids.substr(1, ids.size() - 2);

                //Parsing string
                vector<string> out(
                        sregex_token_iterator(ids.begin(), ids.end(), reIdParse, -1),
                        sregex_token_iterator()
                );

                for (auto IdPart: out) {
                    IdPart = IdPart.substr(1, IdPart.size() - 2); //Removing quotes
                    newTeam->addAthlete(stoi(IdPart));
                    athletesId.insert(stoi(IdPart));
                }
                newCompetitor = newTeam;
            } else { //Athlete
                shared_ptr<Athlete> newAthlete = make_shared<Athlete>(stoi(ids));
                athletesId.insert(stoi(ids));
                newCompetitor = newAthlete;

            }

            //Set Medal for Competitor
            MedalType m = MedalTypeClass::getMedalTypeFromString(medal);
            newCompetitor->setEvent(currentEvent);
            newCompetitor->setMedal(m);

            //Set Country pointer for Competitor
            newCompetitor->setCountry(currentCountry);
            currentCountry->addCompetitor(newCompetitor); //Adding competitor to the country

            //Adding competitor to the game
            currentGame.addCompetitor(newCompetitor);
            competitors.push_back(newCompetitor);

        } else {
            cout << "Not found" << " :: ";
            throw RegexError();
        }

    }

    if (gamesSet.empty()) {
        cout << "The needed year doesn't exist in the file" << " :: ";
        throw LoadingError();
    }

    eventFile.close();
}


