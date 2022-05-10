//
// Created by Lenovo on 5/9/2022.
//

#include "Filter.h"
#include "Country.h"

vector<shared_ptr<Competitor>> Filter::sportFiltering(vector<shared_ptr<Competitor>> competitors) {
    if(sport == "")return competitors;
    competitors.erase(remove_if(competitors.begin(), competitors.end(),
                                [this](shared_ptr<Competitor> comp){return comp->getEvent()->getSport()->getName() != sport; }),
                      competitors.end());
    return competitors;
}

vector<shared_ptr<Competitor>> Filter::countryFiltering(vector<shared_ptr<Competitor>> competitors) {
    if(country == "")return competitors;
    competitors.erase(remove_if(competitors.begin(), competitors.end(),
                                [this](shared_ptr<Competitor> comp){return comp->getCountry()->getName() != country; }),
                      competitors.end());
    return competitors;

    //TODO another way by using country set
    /*auto t = find_if(countries.begin(), countries.end(), [this](Country c){return c.getName() == country;});
    auto tmp = const_cast<Country&>(*t);
    return *tmp.getCompetitors();*/
}

vector<shared_ptr<Competitor>> Filter::yearFiltering(set<Game> games) {
    //if(year == 0)return nullptr; TODO VIDI OVO
    auto t = find_if(games.begin(), games.end(), [this](Game g){return g.getYear() == year;});
    auto tmp =  const_cast<Game&>(*t);
    return *tmp.getCompetitors();
}

vector<shared_ptr<Competitor>> Filter::eventTypeFiltering(vector<shared_ptr<Competitor>> competitors) {
    if(!eventFlag)return competitors;
    competitors.erase(remove_if(competitors.begin(), competitors.end(),
                                [this](shared_ptr<Competitor> comp){return comp->getEvent()->getType() != eventType; }),
                      competitors.end());
    return competitors;
}

vector<shared_ptr<Competitor>> Filter::medalTypeFiltering(vector<shared_ptr<Competitor>> competitors) {
    if(!medalFlag) return competitors;
    competitors.erase(remove_if(competitors.begin(), competitors.end(),
                                [this](shared_ptr<Competitor> comp){return comp->getMedal() != medalType;}),
                      competitors.end());
    return competitors;
}
