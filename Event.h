//
// Created by Lenovo on 4/24/2022.
//

#ifndef POOP_EVENT_H
#define POOP_EVENT_H
#include "EventTypeClass.h"
#include<string>
using namespace std;
class Sport;

class Event {
    string name;
    EventType evType;
    Sport* sport;

public:
    Event(const string& n, EventType evt): name(n), evType(evt){}
    void setSport(Sport& s){
        sport = &s;
    }
    string getName()const{return name;}
    EventType getType()const{return evType;}
    Sport* getSport()const;
    bool operator==(const Event& e)const;

};


#endif //POOP_EVENT_H
