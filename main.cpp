#include <iostream>
#include <set>
#include "EventParser.h"
#include "AthletesParsing.h"
#include "Competitor.h"
#include "Sport.h"
#include "Games.h"
#include "Country.h"
#include "Athlete.h"

int main() {
    vector<Competitor*> competitors;
    set<Sport*> sports;
    set<Games*> games;
    set<Country*> countries;
    vector<Athlete*> athletes;

    athletesParse("C:\\Users\\Lenovo\\CLionProjects\\POOP\\ath.txt", athletes);

    eventParsing("C:\\Users\\Lenovo\\CLionProjects\\POOP\\test.txt", competitors, sports, games, countries, athletes);

    cout << "----" << endl;
    for (auto it = countries.begin(); it != countries.end(); ++it){
        cout << *(*it) << endl;
    }



    return 0;
}
