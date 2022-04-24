//
// Created by Lenovo on 4/24/2022.
//

#ifndef POOP_GAMES_H
#define POOP_GAMES_H
#include<string>
#include<vector>
#include "Competitor.h"
using namespace std;

class Games {
    string name;
    int year;
    string city;
    vector<Competitor*> competitors;

public:
    Games(string n, int y, string c): name(n), year(y), city(c){}
    void addCompetitor(Competitor* c);
};


#endif //POOP_GAMES_H
