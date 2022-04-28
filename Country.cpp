//
// Created by Lenovo on 4/24/2022.
//

#include "Country.h"

void Country::addCompetitor(Competitor* c) {
    if(c)competitors.push_back(c);
}

bool Country::operator==(Country c) {
    return name == c.name;
}

Country::Country(const Country &c) {
    name = c.name;
}

ostream &operator<<(ostream &os, const Country &c) {
    return os << c.name;
}