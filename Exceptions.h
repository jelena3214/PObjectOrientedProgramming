//
// Created by Lenovo on 5/16/2022.
//

#ifndef POOP_EXCEPTIONS_H
#define POOP_EXCEPTIONS_H

#include <iostream>

using namespace std;


class FileNotFound : public exception {
    const char *what() const throw() {
        return "File not found";
    }
};

class RegexError : public exception {
    const char *what() const throw() {
        return "Regex error";
    }
};

class LoadingError : public exception {
    const char *what() const throw() {
        return "Loading regime error";
    }
};

class ErrorGetingDataFromEventParser : public exception {
    const char *what() const throw() {
        return "Error geting data from EventParser";
    }
};

class BasicFilteringError : public exception {
    const char *what() const throw() {
        return "Basic filtering error";
    }
};

class AdvancedFilteringError : public exception {
    const char *what() const throw() {
        return "Advanced filtering error";
    }
};

class ReturnError : public exception {
};


#endif //POOP_EXCEPTIONS_H
