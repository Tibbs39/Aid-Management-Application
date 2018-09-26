/*
OOP244 Final Project: Milestone 5
Student Name:   Kenneth Yue
Student Number: 127932176
Professor:      Tamanna Chhabra
Course:         OOP244
Section:        HH
Date:           April 16, 2018
*/

#include "Perishable.h"
#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;

namespace AMA {
    // constructor
    Perishable::Perishable() : Product('P') {
        expDate = Date();
    }

    // store / load
    fstream& Perishable::store(fstream& file, bool newLine) const {
        Product::store(file, false);
        file << "," << expiry(); // store date
        
        if (newLine) {
            file << endl;
        }

        return file;
    }

    fstream& Perishable::load(fstream& file) {
        Product::load(file);

        file.ignore();
        file >> expDate;

        return file;
    }


    // write / read
    ostream& Perishable::write(ostream& os, bool linear) const {
        Product::write(os, linear);

        if (!isEmpty() && isClear()) {
            // print linearly
            if (linear) {
                os << expiry();
            } else {
            // print fancily
                os << endl << " Expiry date: " << expiry();
            }
        }
        
        return os;
    }

    istream& Perishable::read(istream& is) {
        Product::read(is);
        
        if (!isEmpty()) {
            cout << " Expiry date (YYYY/MM/DD): ";
            Date tempDate;
            cin >> tempDate;
            if (tempDate.bad()) {
                is.setstate(std::ios::failbit);
                switch (tempDate.errCode()) {
                    case 1:
                        message("Invalid Date Entry");
                        break;
                    case 2:
                        message("Invalid Year in Date Entry");
                        break;
                    case 3:
                        message("Invalid Month in Date Entry");
                        break;
                    case 4:
                        message("Invalid Day in Date Entry");
                        break;
                }
            } else {
                expDate = tempDate;
            }
        }
                
        return is;
    }

    const Date& Perishable::expiry() const {
        return expDate;
    }
}