//
// Created by Lenovo on 4/26/2022.
//

#include "AthletesParsing.h"

void athletesParse(const char* fileName, vector<Athlete*>& athletes){
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
            string name = match.str(2);
            string gender = match.str(3);
            string yearsOld = match.str(4);
            if(yearsOld == "NA")yearsOld = "0";
            string height = match.str(5);
            if(height == "NA")height = "0";
            string weight = match.str(6);
            if(weight == "NA")weight = "0";
            athletes.push_back(new Athlete(stoi(id), name, gender, stoi(yearsOld), stoi(height), stoi(weight)));
            cout << i++ << endl;
        }else{
            cout<< "Not found"<< endl;
        }

    }

    eventFile.close();

}