cmake_minimum_required(VERSION 3.22)
project(POOP)

set(CMAKE_CXX_STANDARD 17)

add_executable(POOP main.cpp Competitor.cpp Competitor.h Game.cpp Game.h Athlete.cpp Athlete.h Team.cpp Team.h Event.cpp Event.h Country.cpp Country.h Sport.cpp Sport.h EventTypeClass.h MedalTypeClass.h EventParser.cpp EventParser.h AthletesParser.cpp AthletesParser.h People.cpp People.h Person.cpp Person.h DataManipulation.cpp DataManipulation.h Filter.cpp Filter.h Exceptions.h MenuFunctions.h)
