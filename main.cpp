#include <iostream>
#include <set>
#include "EventParser.h"
#include "AthletesParsing.h"
#include "Competitor.h"
#include "Sport.h"
#include "Games.h"
#include "Country.h"
#include "People.h"

int main() {
    vector<Competitor*> competitors;
    set<Sport*> sports;
    set<Games*> games;
    set<Country*> countries;
    set<int> athletesId;

    People athletes = People::getInstance();
// TO DO: zavrsi i drugi rezim ucitavanja + sredi kod + destruktori???
    eventParsing("C:\\Users\\Lenovo\\CLionProjects\\POOP\\test.txt", competitors, sports, games, countries, athletesId);
    athletesParse("C:\\Users\\Lenovo\\CLionProjects\\POOP\\athletesFile.txt", athletesId, athletes);
    cout << "----" << endl;
    for (auto it = competitors.begin(); it != competitors.end(); ++it){
        if((*it)->type() == "a"){
            cout << "INDIVIDUAL" << endl;
        }
        else{
            cout << "Team" << endl;
            Team* t = dynamic_cast<Team*>(*it);
            cout << " " << endl;
        }
    }

    return 0;
}
