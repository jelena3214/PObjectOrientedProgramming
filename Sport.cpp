//
// Created by Lenovo on 4/24/2022.
//

#include "Sport.h"

void Sport::addEvent(shared_ptr<Event> e) const {
    events.insert(e);
}

bool Sport::operator==(const Sport &s) const {
    return name == s.name;
}

bool Sport::operator<(const Sport &s) const {
    return name < s.name;
}
