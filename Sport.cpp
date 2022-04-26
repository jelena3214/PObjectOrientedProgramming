//
// Created by Lenovo on 4/24/2022.
//

#include "Sport.h"

void Sport::addEvent(Event *e) {
    if(e)events.push_back(e);
}

bool Sport::containsEvent(Event& e) {
    for (auto it = events.begin(); it != events.end(); ++it){
        if(*(*it) == e){
            return true;
        }
    }
    return false;
}

Event *Sport::getEvent(const string& name, EventType ev) {
    Event e = Event(name, ev);
    for (auto it = events.begin(); it != events.end(); ++it){
        if(*(*it) == e){
            return (*it);
        }
    }
    return nullptr;
}
