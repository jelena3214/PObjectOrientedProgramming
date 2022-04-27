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
            Event* competitorEvent = insertEventToSport(event, type, sport, sports); //returns event pointer for competitor

            Competitor* newCompetitor = nullptr;
            if(ids[0] == '['){ //Team
                Team* newTeam = new Team();
                ids = ids.substr(1, ids.size() - 2);
                int n = ids.length();
                char* char_array = new char[n + 1];
                strcpy(char_array, ids.c_str());
                char* res = strtok(char_array, " ,");
                while(res != nullptr){
                    string tmp = res;
                    tmp = tmp.substr(1, tmp.size() - 2);
                    int playerId = stoi(tmp);
                    //find player
                    Athlete* foundAthlete = findAthlete(athletes, playerId);
                    if(foundAthlete) newTeam->addAthlete(foundAthlete);
                    res = strtok (NULL, " ,");
                }
                newCompetitor = newTeam;
            }else{ //Athlete
                for (auto it = athletes.begin(); it != athletes.end(); ++it){
                    if((*it)->getId() == stoi(ids)){
                        newCompetitor = (*it);
                    }
                }

            }
            MedalType m;
            if(medal == "Gold"){
                m = GOLD;
            }else if(medal == "Silver"){
                m = SILVER;
            }else if(medal == "Bronze"){
                m = BRONZE;
            }else{
                m = NA;
            }

            newCompetitor->setEvent(competitorEvent);
            newCompetitor->setMedal(m);
            competitors.push_back(newCompetitor);

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
    if(type == "Individual") e = INDIVIDUAL;
    else e = TEAM;
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

Athlete* findAthlete(vector<Athlete*> athletes, int id) {
    for (auto it = athletes.begin(); it != athletes.end(); ++it){
        if((*it)->getId() == id) {
            return (*it);
        }
    }
    return nullptr;
}