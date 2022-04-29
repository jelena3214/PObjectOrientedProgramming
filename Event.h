//
// Created by Lenovo on 4/24/2022.
//

#ifndef POOP_EVENT_H
#define POOP_EVENT_H
#include "EventTypeClass.h"
#include<string>
using namespace std;


class Event {
    string name;
    EventType evType;

public:
    Event(const string& n, EventType evt): name(n), evType(evt){}
    string getName()const{return name;}
    EventType getType()const{return evType;}
    bool operator==(const Event& e)const;

};


#endif //POOP_EVENT_H
