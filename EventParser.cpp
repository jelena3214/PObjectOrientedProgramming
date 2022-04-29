//
// Created by Lenovo on 4/25/2022.
//

#include "EventParser.h"
#include "EventTypeClass.h"
#include<regex>

using namespace std;

void EventParser::eventParsing(const char* fileName, int findForYear){
    fstream eventFile;
    eventFile.open(fileName, ios::in);
    // TODO if(!eventFile) throw Greska;
    if(!eventFile)cout << "No";
    string tmp;

    regex reLine("([^!]+)!([^!]+)!([^!]+)!([^!]+)!([^!]+)!([^!]+)!([^!]+)!([^\\n]*)");
    regex reYearSeason("(\\d+) ([^\\n]+)");

    smatch matchLine;
    smatch matchYearSeason; //Year & season

    bool group = (findForYear == -1); //Group regime
    //TODO ako nema te godine u faju greska
    while(getline(eventFile, tmp)){
        if (regex_search(tmp, matchLine, reLine) == true) {
            string games = matchLine.str(1);

            regex_search(games, matchYearSeason, reYearSeason);
            int year = stoi(matchYearSeason.str(1));
            string season = matchYearSeason.str(2);

            if(!group){
                if(year != findForYear)continue;
            }

            string city = matchLine.str(2);
            string sport = matchLine.str(3);
            string event = matchLine.str(4);
            string type = matchLine.str(5);
            string country = matchLine.str(6);
            string ids = matchLine.str(7);
            string medal = matchLine.str(8);

            gamesSet.insert(Game(season, year, city));
            countrySet.insert(Country(country));
            sports.insert(Sport(sport));

            shared_ptr<Event> competitorEvent = insertEventToSport(event, type, sport); //returns event pointer for competitor

            shared_ptr<Competitor> newCompetitor = nullptr;
            if(ids[0] == '['){ //Team
                shared_ptr<Team> newTeam = make_shared<Team>();
                ids = ids.substr(1, ids.size() - 2);

                regex reIdParse("\\, ");
                vector<string> out(
                        sregex_token_iterator(ids.begin(), ids.end(), reIdParse, -1),
                        sregex_token_iterator()
                );

                for(auto IdPart: out){
                    IdPart = IdPart.substr(1, IdPart.size() - 2); //Removing quotes
                    newTeam->addAthlete(stoi(IdPart));
                    athletesId.insert(stoi(IdPart));
                }
                newCompetitor = newTeam;
            }else{ //Athlete
                shared_ptr<Athlete> newAthlete = make_shared<Athlete>(stoi(ids));
                athletesId.insert(stoi(ids));
                newCompetitor = newAthlete;

            }

            MedalType m = MedalTypeClass::getMedalTypeFromString(medal);
            newCompetitor->setEvent(competitorEvent);
            newCompetitor->setMedal(m);
            competitors.push_back(newCompetitor);

        }else{
            cout<< "Not found"<< endl;
        }

    }
    eventFile.close();
}

shared_ptr<Event> EventParser::insertEventToSport(const string& event, const string& type, const string& sport){
    //RETURNS EVENT FOR CONTESTANTS
    EventType e = EventTypeClass::getEventTypeFromString(type);
    Event tmpEvent(event, e);
    Sport tmpSport(sport);
    auto it = sports.find(tmpSport);

    //if(it == sports.end())//TODO GRESKA

    return  (*it).addEvent(tmpEvent);
}

