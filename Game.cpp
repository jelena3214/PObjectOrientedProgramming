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
    return (season == g.season && year == g.year) || (season == g.season && year == g.year && city == g.city);
}

bool Game::operator<(const Game &g2)const {
    if(season < g2.season)return true;
    if(year < g2.year) return true;
    return false;
}

vector<shared_ptr<Competitor>> *Game::getCompetitors() {
    return &competitors;
}

const vector<shared_ptr<Competitor>> *Game::getCompetitors() const {
    return &competitors;
}



