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

    struct EventPrtComp{ //for comparing pointers in set of Event*
        bool operator()(shared_ptr<Event>e, shared_ptr<Event>e1) const{
            return e->getName() < e1->getName() && e->getType() < e1->getType();
        }
    };

    mutable set<shared_ptr<Event>, EventPrtComp> events;

public:
    Sport(const string& n):name(n){}
    Sport(){}
    shared_ptr<Event> addEvent(const Event& e) const;
    string getName()const{return name;}
    bool operator==(const Sport& s) const;
    bool operator<(const Sport& s) const;

};


#endif //POOP_SPORT_H
