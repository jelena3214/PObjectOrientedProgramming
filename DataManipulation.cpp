//
// Created by Lenovo on 5/9/2022.
//

#include "DataManipulation.h"
//TODO ucesnici kao br competitora ili kao svi ljudi sportisti?
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
    auto res = evParser->getCompetitors();
    if(f.isSetYear()){
        res = f.yearFiltering(*evParser->getGames());
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
            int height = athletes->getPerson(tmpId)->getHeight();
            if(height) {
                averageHeight += height;
                numOfAthletes++;
            }
            delete cmp->getId();
        }else{
            for(int i : *cmp->getId()){
                int height = athletes->getPerson(i)->getHeight();
                if(height)
                {
                    averageHeight += height;
                    numOfAthletes++;
                }
            }
        }
    }
    if(!averageHeight)return 0;
    return averageHeight/numOfAthletes;

}

double DataManipulation::averageAthletesWeight(Filter f) {
    auto res = getFilteredCompetitors(f);
    double averageWeight = 0;
    int numOfAthletes = 0;
    for(shared_ptr<Competitor> cmp: res){
        if(cmp->getId()->size() == 1){
            int tmpId = *cmp->getId()->begin();
            int weight = athletes->getPerson(tmpId)->getWeight();
            if(weight) {
                averageWeight += weight;
                numOfAthletes++;
            }
            delete cmp->getId();
        }else{
            for(int i : *cmp->getId()){
                int weight = athletes->getPerson(i)->getWeight();
                if(weight) {
                    averageWeight += weight;
                    numOfAthletes++;
                }
            }
        }
    }
    if(!averageWeight)return 0;
    return averageWeight/numOfAthletes;
}
