//
// Created by Lenovo on 4/24/2022.
//

#include "Sport.h"

void Sport::addEvent(Event *e) {
    if(e)events.push_back(e);
}
