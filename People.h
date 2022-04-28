//
// Created by Lenovo on 4/28/2022.
//

#ifndef POOP_PEOPLE_H
#define POOP_PEOPLE_H
#include <map>
#include "Person.h"
//Postoji samo jedna instanca People koja zadrzi sve potrebne ucesnike za taj filter
//Na kraju programa se to dealocira
//A dok u Athlete i Team cuvamo samo id/jeve koji im trebaju
//Ubaci indekciranje i vracanje potrebnog coveka iz mape
using namespace std;

class People {
    map<int, Person*> athletes;

    static People* instance;
    People() {}
public:
    static People& getInstance() {
        if (instance == nullptr) {
            instance = new People();
        }
        return *instance;
    }
    //static void deleteInstance();

    void addPerson(Person * p){
        athletes[p->getId()] = p;
    }

};


#endif //POOP_PEOPLE_H