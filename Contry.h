//
// Created by Lenovo on 4/24/2022.
//

#ifndef POOP_CONTRY_H
#define POOP_CONTRY_H
#include "Competitor.h"
#include<string>
#include<vector>
using namespace std;

class Contry {
    string name;
    vector<Competitor*> competitors;
public:
    Contry(const string& n): name(n){}
    void addCompetitor(Competitor* c);
};


#endif //POOP_CONTRY_H
