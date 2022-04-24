//
// Created by Lenovo on 4/24/2022.
//

#ifndef POOP_SPORT_H
#define POOP_SPORT_H
#include<string>
#include<vector>
#include "Event.h"
using namespace std;

class Sport {
    string name;
    vector<Event*> events;

public:
    Sport(const string& n):name(n){}
    void addEvent(Event* e);
};


#endif //POOP_SPORT_H
