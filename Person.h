//
// Created by Lenovo on 4/28/2022.
//

#ifndef POOP_PERSON_H
#define POOP_PERSON_H

#include<string>

using namespace std;

//Samo sadrzi informacije o ljudima koji su nam potrebni
class Person {
    string name, gender;
    int id, yearsOld, height, weight;

public:
    Person(int idd, int year, int h, int w, const string &n, const string &g) : id(idd), yearsOld(year), gender(g),
                                                                                name(n), height(h), weight(w) {}

    int getId() const { return id; }

    double getHeight() const { return height; }

    double getWeight() const { return weight; }

    int getYears() const { return yearsOld; }
};


#endif //POOP_PERSON_H
