//
// Created by Lenovo on 4/26/2022.
//

#ifndef POOP_ATHLETESPARSING_H
#define POOP_ATHLETESPARSING_H

#include <set>
#include "Athlete.h"
#include "People.h"
#include<fstream>
#include <regex>

void athletesParse(const char* fileName, set<int>& athletes, People& ppl);


#endif //POOP_ATHLETESPARSING_H
