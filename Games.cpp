//
// Created by Lenovo on 4/24/2022.
//

#include "Games.h"

void Games::addCompetitor(Competitor* c) {
    if(c != nullptr){
        competitors.push_back(c);
    }
}
