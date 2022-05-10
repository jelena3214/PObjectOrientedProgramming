//
// Created by Lenovo on 5/9/2022.
//

#include "DataManipulation.h"

int DataManipulation::numberOfPlayers(Filter f) {
    auto res = getFilteredCompetitors(f);
    return res.size();
}

int DataManipulation::numOfDisciplines(Filter f) {
    auto res = getFilteredCompetitors(f);
    set<shared_ptr<Event>, Event::EventPrtComp> events;
    for(shared_ptr<Competitor> c: res){
        events.insert(c->getEvent());
    }

    return events.size();
}

vector<shared_ptr<Competitor>> DataManipulation::getFilteredCompetitors(Filter f) {
    auto res = competitors;
    if(f.isSetYear()){
        res = f.yearFiltering(games);
    }
    res = f.sportFiltering(res);
    res = f.countryFiltering(res);
    res = f.eventTypeFiltering(res);
    res = f.medalTypeFiltering(res);
    return res;
}

double DataManipulation::averageAthletesHeight(Filter f) {
    auto res = getFilteredCompetitors(f);
    double averageHeight = 0;
    int numOfAthletes = 0;
    for(shared_ptr<Competitor> cmp: res){
        if(cmp->getId()->size() == 1){
            int tmpId = *cmp->getId()->begin();
            averageHeight += athletes->getPerson(tmpId)->getHeight();
            numOfAthletes++;
            delete cmp->getId();
        }else{
            for(int i : *cmp->getId()){
                averageHeight += athletes->getPerson(i)->getHeight();
                numOfAthletes++;
            }
        }
    }

    return averageHeight/numOfAthletes;

}

double DataManipulation::averageAthletesWeight(Filter f) {
    auto res = getFilteredCompetitors(f);
    double averageWeight = 0;
    int numOfAthletes = 0;
    for(shared_ptr<Competitor> cmp: res){
        if(cmp->getId()->size() == 1){
            int tmpId = *cmp->getId()->begin();
            averageWeight += athletes->getPerson(tmpId)->getWeight();
            numOfAthletes++;
            delete cmp->getId();
        }else{
            for(int i : *cmp->getId()){
                averageWeight += athletes->getPerson(i)->getWeight();
                numOfAthletes++;
            }
        }
    }

    return averageWeight/numOfAthletes;
}
