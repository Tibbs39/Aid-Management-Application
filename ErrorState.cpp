/*
OOP244 Final Project: Milestone 2
Student Name:   Kenneth Yue
Student Number: 127932176
Professor:      Tamanna Chhabra
Course:         OOP244
Section:        HH
Date:           Mar 23, 2018
*/

#include "ErrorState.h"
#include <iostream>
#include <string.h>

namespace AMA {
    // constructor
    ErrorState::ErrorState(const char* errorMessage /*= nullptr*/) {
        // set error to nullptr by default
        errMsg = nullptr;
        // check if new message is not null
        if (errorMessage) {
            // set new message
            message(errorMessage);
        }
    }

    // destructor
    ErrorState::~ErrorState() {
        delete [] errMsg;
    }

    // clear error message and set to nullptr
    void ErrorState::clear() {
        // check if there's a message
        if (errMsg) {
            delete [] errMsg;
            errMsg = nullptr;
        }
    }

    // return state
    bool ErrorState::isClear() const {
        return !errMsg;
    }

    // set new message
    void ErrorState::message(const char* str) {
        // check if the message string is not empty
        int length = strlen(str);
        if (length > 0) {
            // delete old string
            clear();
            // allocate new memory to match string length
            errMsg = new char[length+1];
            // copy string over
            strcpy(errMsg, str);
        }
    }

    // return message
    const char* ErrorState::message() const {
        return errMsg;
    }

    // output message to ostream
    std::ostream& operator<<(std::ostream& os, const ErrorState& em) {
        if (!em.isClear()) {
            std::cout << em.message();
        }
        return os;
    }
}