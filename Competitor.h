//
// Created by Lenovo on 4/24/2022.
//

#ifndef POOP_COMPETITOR_H
#define POOP_COMPETITOR_H
#include "Event.h"
#include "MedalTypeClass.h"
#include <memory>
#include <set>

using namespace std;

class Country;

class Competitor {
protected:
    MedalType medal;
    shared_ptr<Event> event;
    Country* country;
public:
    void setMedal(MedalType m){medal = m;}
    void setEvent(shared_ptr<Event> e){event = e;}
    shared_ptr<Event> getEvent()const {return event;}
    MedalType getMedal()const{return medal;}
    void setCountry(Country& c){country = &c;}
    Country* getCountry()const{return country;}
    virtual set<int>* getId(){
        return nullptr;
    }


};


#endif //POOP_COMPETITOR_H
