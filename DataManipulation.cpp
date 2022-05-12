//
// Created by Lenovo on 5/9/2022.
//

#include "DataManipulation.h"

//TODO ucesnici kao br competitora ili kao svi ljudi sportisti?
int DataManipulation::numberOfPlayers(Filter f) {
    auto res = getFilteredCompetitors(f);
    set<int> ids;

    for (shared_ptr<Competitor> cmp: res) {
        auto tmp = cmp->getId();
        if (tmp->size() == 1) {
            ids.insert(*tmp->begin());
        } else {
            for (int p: *tmp) {
                ids.insert(p);
            }
        }
    }

    return ids.size();
}

int DataManipulation::numOfDisciplines(Filter f) {
    auto res = getFilteredCompetitors(f);
    set<shared_ptr<Event>, Event::EventPrtComp> events;
    for (shared_ptr<Competitor> c: res) {
        events.insert(c->getEvent());
    }

    return events.size();
}

vector<shared_ptr<Competitor>> DataManipulation::getFilteredCompetitors(Filter f) {
    auto res = evParser->getCompetitors();
    if (f.isSetYear()) {
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
    for (shared_ptr<Competitor> cmp: res) {
        if (cmp->getId()->size() == 1) {
            int tmpId = *cmp->getId()->begin();
            int height = athletes->getPerson(tmpId)->getHeight();
            if (height) {
                averageHeight += height;
                numOfAthletes++;
            }
            delete cmp->getId();
        } else {
            for (int i: *cmp->getId()) {
                int height = athletes->getPerson(i)->getHeight();
                if (height) {
                    averageHeight += height;
                    numOfAthletes++;
                }
            }
        }
    }
    if (!averageHeight)return 0;
    return averageHeight / numOfAthletes;

}

double DataManipulation::averageAthletesWeight(Filter f) {
    auto res = getFilteredCompetitors(f);
    double averageWeight = 0;
    int numOfAthletes = 0;
    for (shared_ptr<Competitor> cmp: res) {
        if (cmp->getId()->size() == 1) {
            int tmpId = *cmp->getId()->begin();
            int weight = athletes->getPerson(tmpId)->getWeight();
            if (weight) {
                averageWeight += weight;
                numOfAthletes++;
            }
            delete cmp->getId();
        } else {
            for (int i: *cmp->getId()) {
                int weight = athletes->getPerson(i)->getWeight();
                if (weight) {
                    averageWeight += weight;
                    numOfAthletes++;
                }
            }
        }
    }
    if (!averageWeight)return 0;
    return averageWeight / numOfAthletes;
}

int DataManipulation::numberOfDifferentSportsWithMedal(const string &country) {
    auto countries = evParser->getCountries();
    auto countryData = countries->find(Country(country));

    if (countryData == countries->end()) {
        std::cout << "Can't find country";
        return -1;
    }

    set<Sport> sportsWithMedal;

    for (shared_ptr<Competitor> comp: countryData->getCompetitors()) {
        if (comp->getMedal() != MedalType::NA) {
            sportsWithMedal.insert(*comp->getEvent()->getSport());
        }
    }
    return sportsWithMedal.size();
}

//Todo see if you will need to return country object or string is just fine?
set<string> DataManipulation::bestCountriesAtGame(int year, const string &season) {

    struct medalCounter {
        mutable int gold, silver, bronze;

        medalCounter() : gold(0), silver(0), bronze(0) {}

        void incGold() const { gold++; }

        void incSilver() const { silver++; }

        void incBronze() const { bronze++; }
    };
    typedef pair<Country, medalCounter> MyPair;

    struct Comp { //for comparing pairs
        bool operator()(MyPair e, MyPair e1) const {
            if (e.first.getName() < e1.first.getName())return true;
            if (e.first.getName() > e1.first.getName())return false;
            return false;
        }
    };

    set<MyPair, Comp> countryMedalCount;
    vector<MyPair> sortedVect;
    auto games = evParser->getGames();
    auto gameTmp = games->find(Game(season, year, ""));

    if (gameTmp == games->end()) {
        exit(-1);
    }
    auto game = const_cast<Game &>(*gameTmp);

    for (shared_ptr<Competitor> cmp: *game.getCompetitors()) { //inserting into set first because of duplicates
        MyPair p;
        p.first = *cmp->getCountry();
        auto a = countryMedalCount.insert(p);
        if (cmp->getMedal() == MedalType::GOLD)a.first->second.incGold();
        if (cmp->getMedal() == MedalType::SILVER)a.first->second.incSilver();
        if (cmp->getMedal() == MedalType::BRONZE)a.first->second.incBronze();
    }

    for (MyPair p: countryMedalCount) { //inserting in vector because of sorting
        sortedVect.push_back(p);
    }

    sort(sortedVect.begin(), sortedVect.end(), [](MyPair e, MyPair e1) {
        if (e.second.gold != e1.second.gold) { return e.second.gold > e1.second.gold; }
        if (e.second.silver != e1.second.silver) { return e.second.silver > e1.second.silver; }
        if (e.second.bronze != e1.second.bronze)return e.second.bronze > e1.second.bronze;
        return false;
    });

    set<string> threeBestCountries;
    for (int i = 0; i < 3; i++)threeBestCountries.insert((sortedVect.begin() + i)->first.getName());
    return threeBestCountries;
}


//todo za obe ove funkcije sta ako su neke drzave jednake u droju medalja

//todo vidi da li misle na to da li je ikada bila u top 3 drzave na nekim igrama
//todo na grupi kazu najbolja u smislu prva od ove 3 i isto vidi za vracanje stringa ili countryja
set<string> DataManipulation::bestCountries() {
    set<string> countries;
    auto games = *evParser->getGames();

    for (Game g: games) {
        auto ret = bestCountriesAtGame(g.getYear(), g.getName());
        auto s = const_cast<string &>(*ret.begin());
        countries.insert(s);
    }

    return countries;
}

set<string> DataManipulation::olympicCities() {
    set<string> cities;

    auto games = *evParser->getGames();

    for (Game tmpGame: games) {
        cities.insert(tmpGame.getCity());
    }

    return cities;
}

set<shared_ptr<Person>> DataManipulation::participatedAtGames(pair<Game, Game> gamePair) {
    auto games = *evParser->getGames();
    auto gameCompetitors1 = *const_cast<Game &>(*games.find(gamePair.first)).getCompetitors();
    auto gameCompetitors2 = *const_cast<Game &>(*games.find(gamePair.second)).getCompetitors();

    vector<int> game1Ids, game2Ids;
    set<int> intersection;

    //Todo separate function
    for (shared_ptr<Competitor> comp: gameCompetitors1) {
        if (comp->getId()->size() == 1) { game1Ids.push_back(*comp->getId()->begin()); }
        else {
            for (int p: *comp->getId()) {
                game1Ids.push_back(p);
            }
        }
    }

    for (shared_ptr<Competitor> comp: gameCompetitors2) {
        if (comp->getId()->size() == 1) { game2Ids.push_back(*comp->getId()->begin()); }
        else {
            for (int p: *comp->getId()) {
                game2Ids.push_back(p);
            }
        }
    }

    sort(game1Ids.begin(), game1Ids.end());
    sort(game2Ids.begin(), game2Ids.end());

    set_intersection(game1Ids.begin(), game1Ids.end(), game2Ids.begin(), game2Ids.end(),
                     inserter(intersection, intersection.begin()));

    return athletes->getPeople(intersection);

}
