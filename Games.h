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
    string season;
    int year;
    string city;
    vector<Competitor*> competitors;

public:
    Games(string s, int y, string c): season(s), year(y), city(c){}
    void addCompetitor(Competitor* c);
    string getName() const{return season;}
    string getCity()const {return city;}
    int getYear()const {return year;}
};


#endif //POOP_GAMES_H
