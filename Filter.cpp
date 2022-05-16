//
// Created by Lenovo on 5/9/2022.
//

#include "Filter.h"
#include "Country.h"

vector<shared_ptr<Competitor>> Filter::sportFiltering(vector<shared_ptr<Competitor>> competitors) {
    if (sport.empty())return competitors;
    competitors.erase(remove_if(competitors.begin(), competitors.end(),
                                [this](shared_ptr<Competitor> comp) {
                                    return comp->getEvent()->getSport()->getName() != sport;
                                }),
                      competitors.end());
    return competitors;
}

vector<shared_ptr<Competitor>> Filter::countryFiltering(vector<shared_ptr<Competitor>> competitors) {
    if (country.empty())return competitors;
    competitors.erase(remove_if(competitors.begin(), competitors.end(),
                                [this](shared_ptr<Competitor> comp) {
                                    return comp->getCountry()->getName() != country;
                                }),
                      competitors.end());
    return competitors;
}

vector<shared_ptr<Competitor>> Filter::yearFiltering(set<Game> games) {
    auto t = find_if(games.begin(), games.end(), [this](Game g) { return g.getYear() == year; });
    auto tmp = const_cast<Game &>(*t);
    return *tmp.getCompetitors();
}

vector<shared_ptr<Competitor>> Filter::eventTypeFiltering(vector<shared_ptr<Competitor>> competitors) {
    if (!eventFlag)return competitors;
    competitors.erase(remove_if(competitors.begin(), competitors.end(),
                                [this](shared_ptr<Competitor> comp) {
                                    return comp->getEvent()->getType() != eventType;
                                }),
                      competitors.end());
    return competitors;
}

vector<shared_ptr<Competitor>> Filter::medalTypeFiltering(vector<shared_ptr<Competitor>> competitors) {
    if (!medalFlag) return competitors;
    competitors.erase(remove_if(competitors.begin(), competitors.end(),
                                [this](shared_ptr<Competitor> comp) { return comp->getMedal() != medalType; }),
                      competitors.end());
    return competitors;
}
