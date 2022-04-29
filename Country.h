//
// Created by Lenovo on 4/24/2022.
//

#ifndef POOP_COUNTRY_H
#define POOP_COUNTRY_H
#include "Competitor.h"
#include<string>
#include<iostream>
#include<vector>
using namespace std;

class Country {
    string name;
    vector<Competitor*> competitors;
public:
    Country(const string& n): name(n){}
    Country(const Country& c);
    void addCompetitor(Competitor* c);
    string getName(){return name;}
    bool operator==(const Country& c);
    bool operator<(const Country& c)const;
    friend ostream & operator << (ostream &, const Country &c);
};


#endif //POOP_COUNTRY_H
