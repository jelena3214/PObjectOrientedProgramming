//
// Created by Lenovo on 4/25/2022.
//

#include "EventParser.h"
#include<regex>

void eventParsing(const char* fileName){
    fstream eventFile;
    eventFile.open(fileName, ios::in);
    // TODO if(!eventFile) throw Greska;
    if(!eventFile)cout << "No";
    string tmp;
    regex re("([^!]+)!([^!]+)!([^!]+)!([^!]+)!([^!]+)!([^!]+)!([^!]+)!([^\\n]*)");
    smatch match;

    while(getline(eventFile, tmp)){
        if (regex_search(tmp, match, re) == true) {
            string s = match.str(8);
            if(s.size() == 0)cout << "Zero" << endl;
            else cout << s << endl;
        }else{
            cout<< "Not found"<< endl;
        }
    }
    eventFile.close();
}