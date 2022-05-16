//
// Created by Lenovo on 5/9/2022.
//

#include "DataManipulation.h"
#include "Exceptions.h"

int DataManipulation::numberOfPlayers(Filter f) {
    vector<shared_ptr<Competitor>> res;
    try {
        res = getFilteredCompetitors(f);
    } catch (const exception &e) {
        cout << e.what() << endl;
        throw BasicFilteringError();
    }

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
    vector<shared_ptr<Competitor>> res;
    try {
        res = getFilteredCompetitors(f);
    } catch (const exception &e) {
        cout << e.what() << endl;
        throw BasicFilteringError();
    }
    set<shared_ptr<Event>, Event::EventPrtComp> events;
    for (shared_ptr<Competitor> c: res) {
        events.insert(c->getEvent());
    }

    return events.size();
}

vector<shared_ptr<Competitor>> DataManipulation::getFilteredCompetitors(Filter f) {
    auto res = evParser->getCompetitors();

    if (res.empty()) {
        cout << "getFilteredCompetitors function :: ";
        throw ErrorGetingDataFromEventParser();
    }

    if (f.isYearSet()) {
        res = f.yearFiltering(*evParser->getGames());
    }
    res = f.sportFiltering(res);
    res = f.countryFiltering(res);
    res = f.eventTypeFiltering(res);
    res = f.medalTypeFiltering(res);
    return res;
}

double DataManipulation::averageAthletesHeight(Filter f) {
    vector<shared_ptr<Competitor>> res;
    try {
        res = getFilteredCompetitors(f);
    } catch (const exception &e) {
        cout << e.what() << endl;
        throw BasicFilteringError();
    }

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
    vector<shared_ptr<Competitor>> res;
    try {
        res = getFilteredCompetitors(f);
    } catch (const exception &e) {
        cout << e.what() << endl;
        throw BasicFilteringError();
    }

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
        cout << "numberOfDifferentSportsWithMedal function :: Can't find country :: ";
        throw AdvancedFilteringError();
    }

    set<Sport> sportsWithMedal;

    for (shared_ptr<Competitor> comp: countryData->getCompetitors()) {
        if (comp->getMedal() != MedalType::NA) {
            sportsWithMedal.insert(*comp->getEvent()->getSport());
        }
    }
    return sportsWithMedal.size();
}

deque<Country *> DataManipulation::bestCountriesAtGame(int year, const string &season) {

    struct medalCounter {
        mutable int gold, silver, bronze;

        medalCounter() : gold(0), silver(0), bronze(0) {}

        void incGold() const { gold++; }

        void incSilver() const { silver++; }

        void incBronze() const { bronze++; }
    };
    typedef pair<Country *, medalCounter> MyPair;

    struct Comp { //for comparing pairs
        bool operator()(MyPair e, MyPair e1) const {
            if (e.first->getName() < e1.first->getName())return true;
            if (e.first->getName() > e1.first->getName())return false;
            return false;
        }
    };

    set<MyPair, Comp> countryMedalCount;
    vector<MyPair> sortedVect;
    auto games = evParser->getGames();
    auto gameTmp = games->find(Game(season, year, ""));

    if (gameTmp == games->end()) {
        cout << "bestCountriesAtGame error : game not found :: ";
        throw AdvancedFilteringError();
    }

    auto game = const_cast<Game &>(*gameTmp);

    for (auto &cmp: *game.getCompetitors()) { //inserting into set first because of duplicates
        MyPair p;
        p.first = cmp->getCountry();
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

    deque<Country *> threeBestCountries; //because we need to keep insertion order, set can't do that
    int lenght = 3;
    if (sortedVect.size() < 3)lenght = sortedVect.size();
    for (int i = 0; i < lenght; i++)threeBestCountries.push_back((sortedVect.begin() + i)->first);
    return threeBestCountries;
}

//todo za obe ove funkcije sta ako su neke drzave jednake u broju medalja, pretpostavka i da su jednake nek ih leksikografski rasporedi pa nek uzme prvi 3

set<Country *> DataManipulation::bestCountries() {
    set<Country *> countries;
    auto games = *evParser->getGames();

    for (Game g: games) {
        auto ret = bestCountriesAtGame(g.getYear(), g.getName());
        auto s = const_cast<Country *>(ret.front());
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
    auto gameTmp1 = games.find(gamePair.first);
    auto gameTmp2 = games.find(gamePair.second);

    if (gameTmp1 == games.end() || gameTmp2 == games.end()) {
        cout << "participatedAtGames error : game not found :: ";
        throw AdvancedFilteringError();
    }

    auto gameCompetitors1 = *gameTmp1->getCompetitors();
    auto gameCompetitors2 = *gameTmp2->getCompetitors();

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

    if (intersection.empty()) {
        cout << "No athletes that match the search\n";
        return set<shared_ptr<Person>>();
    }

    return athletes->getPeople(intersection);
}

vector<shared_ptr<Competitor>>
DataManipulation::countryTeamsAtGame(int year, const string &season, const string &country) {
    auto gameTmp = evParser->getGames()->find(Game(season, year, ""));

    if (gameTmp == evParser->getGames()->end()) {
        cout << "countryTeamsAtGame error : game not found :: ";
        throw AdvancedFilteringError();
    }

    auto game = const_cast<Game &>(*gameTmp);

    vector<shared_ptr<Competitor>> countryTeam;

    for (shared_ptr<Competitor> comp: *game.getCompetitors()) {
        if (comp->getCountry()->getName() == country && comp->getId()->size() > 1) {
            countryTeam.push_back(comp);
        }
    }

    sort(countryTeam.begin(), countryTeam.end(), [](const shared_ptr<Competitor>& c, const shared_ptr<Competitor>& c1) {
        return c->getId()->size() > c1->getId()->size();
    });

    sort(countryTeam.begin(), countryTeam.end(), [](const shared_ptr<Competitor>& c, const shared_ptr<Competitor>& c1) {
        if (c->getEvent()->getName() != c1->getEvent()->getName())
            return c->getEvent()->getName() < c1->getEvent()->getName();
        return false;
    });

    return countryTeam;
}

set<pair<Country, shared_ptr<Person>>> DataManipulation::wonIndividualAndTeamMedal() {
    auto &countries = *evParser->getCountries();

    set<pair<Country, shared_ptr<Person>>> returnSet;

    //mora referenca za count jer bez nje ce se kopirati vrednost
    for (auto &count: countries) {
        set<int> wonIndividualMedal;
        set<int> wonTeamMedal;
        for (shared_ptr<Competitor> cmp: count.getCompetitors()) {
            if (cmp->getMedal() == MedalType::NA)continue;
            if (cmp->getId()->size() == 1) { //individual
                wonIndividualMedal.insert(*cmp->getId()->begin());
            } else {
                wonTeamMedal.insert(cmp->getId()->begin(), cmp->getId()->end());
            }
        }

        set<int> intersect;
        set_intersection(wonTeamMedal.begin(), wonTeamMedal.end(), wonIndividualMedal.begin(), wonIndividualMedal.end(),
                         std::inserter(intersect, intersect.begin()));
        if (intersect.size() == 0)continue;
        for (int id: intersect) {
            pair<Country, shared_ptr<Person>> tmp;
            tmp.first = count;
            tmp.second = athletes->getPerson(id);
            returnSet.insert(tmp);
        }
    }
    return returnSet;
}

vector<shared_ptr<Person>> DataManipulation::bestYoungestAthletes() {
    auto athletesIds = evParser->getAthleteIds();
    auto games = evParser->getGames();

    vector<int> youngestWithMedal;

    for (int id: athletesIds) {
        const Game *firstParticipation = nullptr;
        MedalType medalWon;
        int firstParticipationYear = INT_MAX;

        for (auto &game: *games) {
            auto competitors = *game.getCompetitors();
            for (auto competitor: competitors) {
                auto idSet = competitor->getId();
                if (idSet->find(id) != idSet->end()) {
                    if ((game.getYear() < firstParticipationYear) ||
                        (game.getYear() == firstParticipationYear && competitor->getMedal() != MedalType::NA)) {
                        firstParticipation = &game;
                        firstParticipationYear = game.getYear();
                        medalWon = competitor->getMedal();
                    }
                }
            }
        }

        if (medalWon != MedalType::NA) youngestWithMedal.push_back(id);

    }

    vector<shared_ptr<Person>> youngAthletes;

    for (int id: youngestWithMedal) {
        youngAthletes.push_back(athletes->getPerson(id));
    }

    sort(youngAthletes.begin(), youngAthletes.end(), [](const shared_ptr<Person> &p1, const shared_ptr<Person> &p2) {
        return p1->getYears() < p2->getYears();
    });

    if (youngAthletes.size() > 10) {
        youngAthletes.resize(10);
    }
    return youngAthletes;
}
