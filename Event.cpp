//
// Created by Lenovo on 4/24/2022.
//

#include "Event.h"

bool Event::operator==(const Event& e) const {
    return e.name == name && e.evType == evType;
}
