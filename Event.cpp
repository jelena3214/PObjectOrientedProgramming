//
// Created by Lenovo on 4/24/2022.
//

#include "Event.h"
#include "Sport.h"

bool Event::operator==(const Event &e) const {
    return e.name == name && e.evType == evType;
}

Sport *Event::getSport() const {
    return sport;
}

