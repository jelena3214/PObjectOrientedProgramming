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

public:
    Athlete(int idd):id(idd) {}
    friend bool operator==(const Athlete& a1, const Athlete& a2);
    set<int>* getId() override{
        set<int>* tmp = new set<int>();
        tmp->insert(id);
        return tmp;
    }
};


#endif //POOP_ATHLETE_H
