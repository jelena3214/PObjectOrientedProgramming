//
// Created by Lenovo on 4/24/2022.
//

#ifndef POOP_TEAM_H
#define POOP_TEAM_H
#include<iostream>
#include<vector>
#include "Athlete.h"
#include "Competitor.h"

using namespace std;

class Team: public Competitor {
private:
    std::vector<Athlete*> athletes;

public:
    Team(){}
    void addAthlete(Athlete* athlete);
    string type() override{
        return "t";
    }
};


#endif //POOP_TEAM_H
