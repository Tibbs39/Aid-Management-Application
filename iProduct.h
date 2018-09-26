/*
OOP244 Final Project: Milestone 3
Student Name:   Kenneth Yue
Student Number: 127932176
Professor:      Tamanna Chhabra
Course:         OOP244
Section:        HH
Date:           Mar 28, 2018
*/

#ifndef AMA_IPRODUCT_H
#define AMA_IPRODUCT_H

#include <iostream>
#include <fstream>

namespace AMA {
    class iProduct {
        public:
            // returns the name of the product
            virtual const char* name() const = 0;
            // returns the sku
            virtual const char* sku() const = 0;
            // returns the unit
            virtual const char* unit() const = 0;

            // store / load 
            virtual std::fstream& store(std::fstream& file, bool newLine = true) const = 0;
            virtual std::fstream& load(std::fstream& file) = 0;
            
            // read / write
            virtual std::ostream& write(std::ostream& os, bool linear) const = 0;
            virtual std::istream& read(std::istream& is) = 0;
            
            // check if sku match
            virtual bool operator==(const char*) const = 0;
            // returns the total cost
            virtual double total_cost() const = 0;
            // update the quantity
            virtual void quantity(int) = 0;
            // check if the object is empty
            virtual bool isEmpty() const = 0;
            // returns the amount needed
            virtual int qtyNeeded() const = 0;
            // returns the amount on hand
            virtual int quantity() const = 0;
            // compares sku
            virtual bool operator>(const iProduct&) const = 0;
            // add to the quantity
            virtual int operator+=(int) = 0;
    };

    std::ostream& operator<<(std::ostream&, const iProduct&);
    std::istream& operator>>(std::istream&, iProduct&);
    double operator+=(double&, const iProduct&);

    iProduct* CreateProduct();
    iProduct* CreatePerishable();

}

#endif