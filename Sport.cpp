//
// Created by Lenovo on 4/24/2022.
//

#include "Sport.h"

shared_ptr<Event> Sport::addEvent(const Event& e) const{
    auto it = events.insert(make_shared<Event>(e));
    return *it.first;
}
bool Sport::operator==(const Sport& s) const {
    return name == s.name;
}

bool Sport::operator<(const Sport& s) const{
    return name < s.name;
}
