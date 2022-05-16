//
// Created by Lenovo on 4/24/2022.
//

#ifndef POOP_GAME_H
#define POOP_GAME_H

#include<string>
#include<vector>
#include "Competitor.h"

using namespace std;

class Game {
    string season;
    int year;
    string city;
    vector<shared_ptr<Competitor>> competitors;

public:
    Game(string s, int y, string c) : season(s), year(y), city(c) {}

    Game() {}

    void addCompetitor(shared_ptr<Competitor> c);

    vector<shared_ptr<Competitor>> *getCompetitors();

    const vector<shared_ptr<Competitor>> *getCompetitors() const;

    int numberOfCompetitors() const { return competitors.size(); }

    string getName() const { return season; }

    string getCity() const { return city; }

    bool operator<(const Game &g) const;

    bool operator==(const Game &g);

    int getYear() const { return year; }
};


#endif //POOP_GAME_H
