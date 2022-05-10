//
// Created by Lenovo on 4/24/2022.
//

#ifndef POOP_SPORT_H
#define POOP_SPORT_H
#include<string>
#include<set>
#include<memory>
#include "Event.h"

using namespace std;

class Sport {
    string name;
    mutable set<shared_ptr<Event>, Event::EventPrtComp> events;

public:
    Sport(const string& n):name(n){}
    Sport(){}
    void addEvent(shared_ptr<Event> e) const;
    string getName()const{return name;}
    bool operator==(const Sport& s) const;
    bool operator<(const Sport& s) const;

};


#endif //POOP_SPORT_H
