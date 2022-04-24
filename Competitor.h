//
// Created by Lenovo on 4/24/2022.
//

#ifndef POOP_COMPETITOR_H
#define POOP_COMPETITOR_H
#include "Event.h"
#include "Medal.h"

class Competitor {
    Medal medal;
    Event* event;
int l;
public:
    Competitor(Medal m, Event ev){
        medal = m;
        event = &ev;
    }

    virtual ~Competitor() = 0;

};


#endif //POOP_COMPETITOR_H
