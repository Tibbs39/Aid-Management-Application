/*
OOP244 Final Project: Milestone 5
Student Name:   Kenneth Yue
Student Number: 127932176
Professor:      Tamanna Chhabra
Course:         OOP244
Section:        HH
Date:           April 16, 2018
*/

#ifndef AMA_PERISHABLE_H
#define AMA_PERISHABLE_H
#include "Product.h"
#include "Date.h"

namespace AMA {
    class Perishable : public Product {
        Date expDate;

        public:
            // default constructor
            Perishable();

            // store / load
            std::fstream& store(std::fstream& file, bool newLine = true) const;
            std::fstream& load(std::fstream& file);

            // write / read
            std::ostream& write(std::ostream& os, bool linear) const;
            std::istream& read(std::istream& is);

            // returns expiry date
            const Date& expiry() const;
    };
}

#endif //AMA_PERISHABLE_H