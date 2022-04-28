//
// Created by Lenovo on 4/26/2022.
//

#include "AthletesParsing.h"

void athletesParse(const char* fileName, set<int>& athletes, People& people){
    fstream eventFile;
    eventFile.open(fileName, ios::in);
    // TODO if(!eventFile) throw Greska;
    if(!eventFile)cout << "No";
    string tmp;
    regex re("([^!]+)!([^!]+)!([^!]+)!([^!]+)!([^!]+)!([^!]+)");
    smatch match;
    int i = 0;

    while(getline(eventFile, tmp)){
        if (regex_search(tmp, match, re) == true) {
            string id = match.str(1);
            if(athletes.find(stoi(id)) == athletes.end()) continue;
            string name = match.str(2);
            string gender = match.str(3);
            string yearsOld = match.str(4);
            if(yearsOld == "NA")yearsOld = "0";
            string height = match.str(5);
            if(height == "NA")height = "0";
            string weight = match.str(6);
            if(weight == "NA")weight = "0";
            people.addPerson(new Person(stoi(id), stoi(yearsOld), stoi(height), stoi(weight), name, gender));
            cout << i++ << endl;
        }else{
            cout<< "Not found"<< endl;
        }

    }

    eventFile.close();

}