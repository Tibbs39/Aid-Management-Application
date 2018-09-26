/*
OOP244 Final Project: Milestone 2
Student Name:   Kenneth Yue
Student Number: 127932176
Professor:      Tamanna Chhabra
Course:         OOP244
Section:        HH
Date:           Mar 23, 2018
*/

#ifndef AMA_ERRORSTATE_H
#define AMA_ERRORSTATE_H

#include <iostream>

namespace AMA {
    class ErrorState {
        char* errMsg;
        
        public:
            // constructor
            explicit ErrorState(const char* errorMessage = nullptr);
            
            // prevent copy constructor and copy assignment
            ErrorState(const ErrorState& em) = delete;
            ErrorState& operator=(const ErrorState& em) = delete;
            
            // deconstructor
            virtual ~ErrorState();
            
            // clear error message
            void clear();

            // check if pointer is null
            bool isClear() const;

            // change message
            void message(const char* str);

            // return message
            const char* message() const;
    };

    // helper function
    // output msg to ostream with << operator
    std::ostream& operator<<(std::ostream& os, const ErrorState& em);
}


#endif // AMA_ERRORSTATE_H