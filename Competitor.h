//
// Created by Lenovo on 4/24/2022.
//

#ifndef POOP_COMPETITOR_H
#define POOP_COMPETITOR_H
#include "Event.h"
#include "MedalType.h"
//#include "Medal.h"


class Competitor {
protected:
    MedalType medal;
    Event* event;
public:
    Competitor(){}

    void setMedal(MedalType m){medal = m;}
    void setEvent(Event* e){event = e;}
    Event* getEvent()const {return event;}
    virtual string type(){
        return "c";
    }


};


#endif //POOP_COMPETITOR_H
