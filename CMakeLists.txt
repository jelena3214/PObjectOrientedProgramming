cmake_minimum_required(VERSION 3.22)
project(POOP)

set(CMAKE_CXX_STANDARD 17)

add_executable(POOP main.cpp Competitor.cpp Competitor.h Games.cpp Games.h Athlete.cpp Athlete.h Team.cpp Team.h Event.cpp Event.h Country.cpp Country.h Sport.cpp Sport.h EventType.h MedalType.h EventParser.cpp EventParser.h AthletesParsing.cpp AthletesParsing.h)
