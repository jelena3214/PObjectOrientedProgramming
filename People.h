//
// Created by Lenovo on 4/28/2022.
//

#ifndef POOP_PEOPLE_H
#define POOP_PEOPLE_H
#include <map>
#include "Person.h"
using namespace std;

class People {
    map<int, Person*> lines;

    static JGP* instance;
    JGP() {}
public:
    static JGP& getInstance() {
        if (instance == nullptr) {
            instance = new JGP();
        }
        return *instance;
    }
    static void deleteInstance();


};


#endif //POOP_PEOPLE_H
