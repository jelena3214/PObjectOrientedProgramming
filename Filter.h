//
// Created by Lenovo on 5/9/2022.
//

#ifndef POOP_FILTER_H
#define POOP_FILTER_H
#include <string>
#include <vector>
#include "EventTypeClass.h"
#include "MedalTypeClass.h"
#include "Competitor.h"
#include "Sport.h"
#include "Game.h"

using namespace std;

class Filter {
private:
    string sport, country;
    int year;
    EventType eventType;
    MedalType medalType;

public:
    explicit Filter(const string ss = "", const string cc = "", const int yy = 0, const string ev = "", const string mt = ""):
            sport(ss), country(cc), year(yy){
        if(ev != "") eventType = EventTypeClass::getEventTypeFromString(ev);
        if(mt != "") medalType = MedalTypeClass::getMedalTypeFromString(mt);
    }

    auto sportFiltering(vector<shared_ptr<Competitor>> competitors);
    auto countryFiltering(vector<shared_ptr<Competitor>> competitors);
    auto yearFiltering(set<Game> games);

};


#endif //POOP_FILTER_H
