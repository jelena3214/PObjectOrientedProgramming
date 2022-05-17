//
// Created by Lenovo on 4/26/2022.
//

#include "AthletesParser.h"
#include "Exceptions.h"

void AthetesParser::athletesParse(const char *fileName, People &people) {
    fstream eventFile;
    eventFile.open(fileName, ios::in);

    if (!eventFile)throw FileNotFound();

    string tmp;
    regex re("([^!]+)!([^!]+)!([^!]+)!([^!]+)!([^!]+)!([^!]+)", regex::optimize);
    smatch match;
    int i = 0;

    if (athletes.empty()) {
        cout << "No athletes to be loaded" << " :: ";
        throw LoadingError();
    }

    while (getline(eventFile, tmp)) {
        if (regex_search(tmp, match, re) == true) {
            string id = match.str(1);
            if (athletes.find(stoi(id)) == athletes.end()) continue;
            string name = match.str(2);
            string gender = match.str(3);
            string yearsOld = match.str(4);
            if (yearsOld == "NA")yearsOld = "0";
            string height = match.str(5);
            if (height == "NA")height = "0";
            string weight = match.str(6);
            if (weight == "NA")weight = "0";
            people.addPerson(make_shared<Person>(stoi(id), stoi(yearsOld), stoi(height), stoi(weight), name, gender));
            cout << i++ << endl;
        } else {
            cout << "Not found" << " :: ";
            throw RegexError();
        }

    }

    eventFile.close();

}