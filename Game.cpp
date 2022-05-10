//
// Created by Lenovo on 4/24/2022.
//

#include "Game.h"

void Game::addCompetitor(shared_ptr<Competitor> c) {
    if(c != nullptr){
        competitors.push_back(c);
    }
}

bool Game::operator==(const Game &g) {
    return season == g.season && year == g.year && city == g.city;
}

bool Game::operator<(const Game &g)const {
    return season < g.season && city < g.city && year < g.year;
}

vector<shared_ptr<Competitor>> *Game::getCompetitors() {
    return &competitors;
}



