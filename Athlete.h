//
// Created by Lenovo on 4/24/2022.
//

#ifndef POOP_ATHLETE_H
#define POOP_ATHLETE_H
#include<string.h>
#include<iostream>
#include "Team.h"
#include "Competitor.h"

using namespace std;

class Athlete: public Competitor {
private:
    int id, height, weight, years;
    string name;
    char gender;
    //DO WE NEED TEAM POINTER? THEY CAN BELONG TO TEAM IN ONE GAME AND THEN NOT
public:
    Athlete(int idd, const string &n, char g, int y, int h, int w, Medal m, Event ev):Competitor(m, ev), id(idd), name(n), gender(g), years(y),
    height(h), weight(w){}
    //TO DO
    //COPY CONSTRUCTOR?
};


#endif //POOP_ATHLETE_H
