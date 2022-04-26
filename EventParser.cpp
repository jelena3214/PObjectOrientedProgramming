//
// Created by Lenovo on 4/25/2022.
//

#include "EventParser.h"
#include<regex>

void eventParsing(const char* fileName, vector<Competitor*>& competitors, set<Sport*>& sports,
                  set<Games*>& gamesSet, set<Country*>& countrySet, vector<Athlete*>& athletes){
    fstream eventFile;
    eventFile.open(fileName, ios::in);
    // TODO if(!eventFile) throw Greska;
    if(!eventFile)cout << "No";
    string tmp;
    regex re("([^!]+)!([^!]+)!([^!]+)!([^!]+)!([^!]+)!([^!]+)!([^!]+)!([^\\n]*)");
    smatch match;
    //Events, Games, Athlets, Teams, Country, Sport
    //1: igre, 2: grad, 3: sport, 4: event, 5: t/i, 6: drzava, 7: id indi/tim, 8: medalja
    while(getline(eventFile, tmp)){
        if (regex_search(tmp, match, re) == true) {
            string games = match.str(1);
            string city = match.str(2);
            string sport = match.str(3);
            string event = match.str(4);
            string type = match.str(5);
            string country = match.str(6);
            string ids = match.str(7);
            string medal = match.str(8);

            games = games + " " + city;
            insertGame(games, gamesSet);
            insertT<Country>(country, countrySet);
            insertT<Sport>(sport, sports);
            Event* competitorEvent = insertEventToSport(event, type, sport, sports);

            Competitor* newCompetitor = nullptr;
            if(ids[0] == '['){ //Team
                //team
            }else{ //Athlete
                for (auto it = athletes.begin(); it != athletes.end(); ++it){
                    if((*it)->getId() == stoi(ids)){
                        newCompetitor = (*it);
                    }
                }

            }
            MedalType m;
            if(medal == "GOLD"){
                m = GOLD;
            }else if(medal == "SILVER"){
                m = SILVER;
            }else if(medal == "BRONZE"){
                m = BRONZE;
            }else{
                m = NA;
            }


            newCompetitor->setEvent(competitorEvent);
            newCompetitor->setMedal(m);
            competitors.push_back(newCompetitor);
            //List of athlets, and if competitor is a athlete we just add that single athlete to the vector
            //if competitor is a Team we find all athlets and add them to the team
            //then we add Medal, pointer to the event
            //then we add competitors to the country and games collection
            //game country can return pointer to them so we can add competitors

        }else{
            cout<< "Not found"<< endl;
        }

    }

    eventFile.close();
}

Games* insertGame(const string& game, set<Games*>& games){
    regex re("(\\d+) (\\S+) (\\S+)");
    smatch match;
    regex_search(game, match, re);

    for (auto it = games.begin(); it != games.end(); ++it){
        if((*it)->getYear() == stoi(match.str(1)) && (*it)->getCity() == match.str(3) && (*it)->getName() == match.str(2)){
            return (*it);
        }
    }

    Games* nG = new Games(match.str(2), stoi(match.str(1)), match.str(3));
    games.insert(nG);
    return nG;
}

template<typename T>
T* insertT(const string& name, set<T*>& insertSet){

    for (auto it = insertSet.begin(); it != insertSet.end(); ++it){
        if((*it)->getName() == name){
            return (*it);
        }
    }

    T* nT = new T(name);
    insertSet.insert(nT);
    return nT;
}

Event* insertEventToSport(const string& event, const string& type,const string& sport, set<Sport*> sports){
    //RETURNS EVENT FOR CONTESTANTS
    bool insert = true;
    EventType e;
    if(type == "Individual") e = Individual;
    else e = Team;
    Event tmpEvent = Event(event, e);

    Sport* tmpSport = nullptr;
    for (auto it = sports.begin(); it != sports.end(); ++it){
        if((*it)->getName() == sport) {
            tmpSport = (*it);
        }
    }

    if(tmpSport->containsEvent(tmpEvent)){
        return tmpSport->getEvent(event, e);
    }else{
        Event* insert = new Event(event, e);
        tmpSport->addEvent(insert);
        return insert;
    }

}