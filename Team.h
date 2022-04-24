//
// Created by Lenovo on 4/24/2022.
//

#ifndef POOP_TEAM_H
#define POOP_TEAM_H
#include<iostream>
#include<set>
#include "Athlete.h"
#include "Competitor.h"

class Team: public Competitor {
private:
    set<Athlete> athlets;

public:
    Team(Medal m, Event ev): Competitor(m, ev){}
};


#endif //POOP_TEAM_H
