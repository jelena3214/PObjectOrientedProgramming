//
// Created by Lenovo on 4/24/2022.
//

#include "Sport.h"

bool Sport::operator==(const Sport &s) const {
    return name == s.name;
}

bool Sport::operator<(const Sport &s) const {
    return name < s.name;
}

shared_ptr<Event> Sport::addEvent(const string &name, const string &type) const {
    EventType e = EventTypeClass::getEventTypeFromString(type);
    auto eventPair = events.insert(make_shared<Event>(Event(name, e)));
    return *eventPair.first;
}
