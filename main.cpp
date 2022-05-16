#include "EventParser.h"
#include "AthletesParser.h"
#include "People.h"
#include "DataManipulation.h"
#include "MenuFunctions.h"

//TODO finish filter methods, resolve todo isues in those files and finish filters
//TODO consult

int main() {
    People athletes = People::getInstance();
    EventParser evParser;
    int chosenRegime;

    const char* eventFileName = "C:\\\\Users\\\\Lenovo\\\\CLionProjects\\\\POOP\\\\test.txt";
    const char* athletesFileName = "C:\\Users\\Lenovo\\CLionProjects\\POOP\\athletesFile.txt";

    cout << "Izaberite rezim ucitavanja: " << endl;
    cout << "1. Grupni rezim\n"
            "2. Pojedinacni rezim\n" << endl;

    cin >> chosenRegime;
    if(chosenRegime == 1){
        try {
            evParser.eventParsing(eventFileName);
        } catch (const exception &e) {
            cout << e.what() << endl;
        }
    }else{
        int chosenYear;
        cout << "Unesite godinu Olimpijskih igara: "<< endl;
        cin >> chosenYear;
        try {
            evParser.eventParsing(eventFileName, chosenYear);
        } catch (const exception &e) {
            cout << e.what() << endl;
        }

    }

    AthetesParser athParser(evParser.getAthleteIds());
    athParser.athletesParse(athletesFileName, athletes);

    DataManipulation dm(&evParser, &athletes);

    Filter* filter = nullptr;
    string space;
    int chosenOption;

    while(true){
        printOptions();
        cin >> chosenOption;
        try {
            if (chosenOption < 5) { //make filter
                cout << "Unesite ime sporta (/ nista): " << endl;
                string sport;
                getline(cin, space);
                getline(cin, sport);
                cout << "Unesite ime drzave (/ nista): " << endl;
                string country;
                getline(cin, space);
                getline(cin, country);
                int year;
                cout << "Unesite godinu (0 nista): " << endl;
                cin >> year;
                cout << "Unesite tip dogadjaja 1(Individualni), 2(Timski), (0 nista):  " << endl;
                int type;
                cin >> type;
                string typeName;
                if (type == 1) {
                    typeName = "Individual";
                } else if (type == 2) {
                    typeName = "Team";
                } else typeName = "";
                cout << "Unesite tip medalje 1(Zlatna), 2(Srebrna), 3(Bronzana), (0 nista):  " << endl;
                int medal;
                cin >> medal;
                string medalName;
                if (medal == 1) {
                    medalName = "Gold";
                } else if (medal == 2) {
                    medalName = "Silver";
                } else if (medal == 3) {
                    medalName = "Bronze";
                } else medalName = "";

                filter = new Filter((sport != "/"?sport:""), (country != "/"?country:""), year, typeName, medalName);
            }

            if (chosenOption == 1) {
                cout << dm.numberOfPlayers(*filter) << endl;
            } else if (chosenOption == 2) {
                cout << dm.numOfDisciplines(*filter) << endl;
            } else if (chosenOption == 3) {
                cout << dm.averageAthletesHeight(*filter) << endl;
            } else if (chosenOption == 4) {
                cout << dm.averageAthletesWeight(*filter) << endl;
            } else if (chosenOption == 5) {
                string country;
                cout << "Unesite ime drzave: " << endl;
                getline(cin, space);
                getline(cin, country);
                cout << dm.numberOfDifferentSportsWithMedal(country) << endl;
            } else if (chosenOption == 6) {
                string season;
                int year;
                cout << "Unesi tip Olimpijskih igara: ";
                getline(cin, space);
                getline(cin, season);
                cout << endl << "Unesi godinu: ";
                cin >> year;
                auto res = dm.bestCountriesAtGame(year, season);
                for (auto country: res) {
                    cout << *country << endl;
                }
            } else if (chosenOption == 7) {
                auto res = dm.bestCountries();
                for (auto country: res) {
                    cout << *country << endl;
                }
            }else if(chosenOption  == 8){
                auto res = dm.bestYoungestAthletes();
                for(auto person: res){
                    cout << *person << endl;
                }
            }else if(chosenOption == 9){
                auto sportpairs = dm.wonIndividualAndTeamMedal();
                for(auto sportP: sportpairs){
                    cout << sportP.first << " : " << sportP.second << endl;
                }
            }else if(chosenOption == 10){
                string season, city;
                int year;
                Game* first, *second;
                for(int i = 0; i < 2; i++) {
                    cout << "Unesite vrstu igara: ";
                    if(i == 0)getline(cin, space);
                    getline(cin, season);
                    cout << "\nUnesite godinu odrzavanja: ";
                    cin >> year;
                    cout << "\nUnesite grad: ";
                    getline(cin, space);
                    getline(cin, city);
                    if(i == 0) first = new Game(season, year, city);
                    else second = new Game(season, year, city);
                }
                std::pair<Game, Game> gamess;
                gamess.first = *first;
                gamess.second = *second;
                auto res = dm.participatedAtGames(gamess);
                for(auto athlete: res){
                    cout << athlete << endl;
                }
                delete first;
                delete second;
            }else if(chosenOption == 11){
                string season, country;
                int year;
                cout << "Unesite vrstu igara: ";
                getline(cin, space);
                getline(cin, season);
                cout << "\nUnesite godinu odrzavanja: ";
                cin >> year;
                cout << "\nUnesite drzavu: ";
                getline(cin, space);
                getline(cin, country);
                auto teams = dm.countryTeamsAtGame(year, season, country);
                int i = 1;
                for(const auto& t: teams){
                    auto ids = t->getId();
                    cout << i << ". [";
                    int k = 0;
                    for(int id: *ids){
                        cout << id;
                        if(k < ids->size() - 1)cout << ", ";
                        k++;
                    }
                    cout << "]" << endl;
                    i++;
                }
            }else if(chosenOption == 12){
                auto cities = dm.olympicCities();
                for(auto city: cities){
                    cout << city << endl;
                }
            }else if(chosenOption == 13){
                break;
            }

        }catch(const exception& e){
            cout << e.what() << endl;
        }
        delete filter;
    }

    People::deleteInstance();

    return 0;
}
