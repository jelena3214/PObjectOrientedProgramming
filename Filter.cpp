//
// Created by Lenovo on 5/9/2022.
//

#include "Filter.h"
#include "Country.h"

auto Filter::sportFiltering(vector<shared_ptr<Competitor>> competitors) {
    if(sport == "")return competitors;
    remove_if(competitors.begin(), competitors.end(),
              [this](shared_ptr<Competitor> comp){return comp->getEvent()->getSport()->getName() != sport; });
    return competitors;
}

auto Filter::countryFiltering(vector<shared_ptr<Competitor>> competitors) {
    if(country == "")return competitors;
    remove_if(competitors.begin(), competitors.end(),
              [this](shared_ptr<Competitor> comp){return comp->getCountry()->getName() != country; });
    return competitors;
}

auto Filter::yearFiltering(set<Game> games) {
    if(year == 0)return games;
    //TODO REMOVEIF FOR SET
    //(games.begin(), games.end(), [this](const Game& g){return  g.getYear() != year;});
    return games;
}
