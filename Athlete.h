//
// Created by Lenovo on 4/24/2022.
//

#ifndef POOP_ATHLETE_H
#define POOP_ATHLETE_H
#include<string.h>
#include<iostream>
#include "Competitor.h"

using namespace std;

class Athlete: public Competitor {
private:
    int id;
    //DO WE NEED TEAM POINTER? THEY CAN BELONG TO TEAM IN ONE GAME AND THEN NOT
public:
    Athlete(int idd):id(idd) {}
    //TO DO
    //COPY CONSTRUCTOR?
    int getId()const {return id;}
    friend bool operator==(const Athlete& a1, const Athlete& a2);
    string type() override{
        return "a";
    }
};


#endif //POOP_ATHLETE_H
