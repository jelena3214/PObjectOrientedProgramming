//
// Created by Lenovo on 4/24/2022.
//

#ifndef POOP_EVENT_H
#define POOP_EVENT_H
#include "EventType.h"
#include<string>
using namespace std;


class Event {
    string name;
    EventType evType;

public:
    Event(const string& n, EventType evt): name(n), evType(evt){}
};


#endif //POOP_EVENT_H
