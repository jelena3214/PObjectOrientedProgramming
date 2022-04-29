//
// Created by Lenovo on 4/24/2022.
//

#ifndef POOP_COMPETITOR_H
#define POOP_COMPETITOR_H
#include "Event.h"
#include "MedalTypeClass.h"
#include <memory>
//#include "Medal.h"
using namespace std;

class Country;
class Game;

class Competitor {
protected:
    MedalType medal;
    shared_ptr<Event> event;
    Country* country;
    Game* game;
public:
    void setMedal(MedalType m){medal = m;}
    void setEvent(shared_ptr<Event> e){event = e;}
    shared_ptr<Event> getEvent()const {return event;}
    virtual string type(){
        return "c";
    }


};


#endif //POOP_COMPETITOR_H
