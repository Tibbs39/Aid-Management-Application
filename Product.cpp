/*
OOP244 Final Project: Milestone 3
Student Name:   Kenneth Yue
Student Number: 127932176
Professor:      Tamanna Chhabra
Course:         OOP244
Section:        HH
Date:           Mar 28, 2018
*/

#include "Product.h"
#include <string.h>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

namespace AMA {
    // protected functions
    // change the name of the object
    void Product::name(const char* name_) {
        if (name_) {
            int length = strlen(name_);
            if (length > max_name_length) {
                length = max_name_length;
            }

            pName = new char[length + 1];
            strncpy(pName, name_, length);
            pName[length] = '\0';
        } else {
            pName = nullptr;
        }
    }
    // return the name
    const char* Product::name() const {
        return pName;
    }
    // return the sku
    const char* Product::sku() const {
        return pSku;
    }
    // return the unit
    const char* Product::unit() const {
        return desc;
    }
    // return true if the product is taxable
    bool Product::taxed() const {
        return taxable;
    }
    // return the price of the product
    double Product::price() const {
        return pPrice;
    }
    // return the total cost of the product
    double Product::cost() const {
        double totalCost = pPrice;
        if (taxed()) {
            totalCost *= (1 + tax_rate);
        }
        
        return totalCost;
    }
    // set error message
    void Product::message(const char* msg) {
        error.message(msg);
    }

    const char* Product::message() const {
        return error.message();
    }

    // check if error state is clear
    bool Product::isClear() const {
        return error.isClear();
    }

    // public functions
    // constructor
    Product::Product(char type_) {
        type = type_;
        strcpy(pSku,"\0");
        strcpy(desc,"\0");
        pName = nullptr;
        qty = -1;
        qtyNeed = -1;
        pPrice = -1;
        taxable = false;
        error.clear();
    }

    Product::Product(const char* pSku_, const char* name_, const char* desc_, 
            int qty_, bool taxable_, double pPrice_, int qtyNeed_) {
        pName = nullptr;
        //*this = Product(); // initalize everything as default
        
        // set name
        name(name_);

        // check string lengths
        if (pSku_) {
            int length = strlen(pSku_);
            if (length > max_sku_length) {
                length = max_sku_length;
            }
            strncpy(pSku, pSku_, length);
            pSku[length] = '\0';
        }

        if (desc_) {
            int length = strlen(desc_);
            if (length > max_unit_length) {
                length = max_unit_length;
            }
            strncpy(desc, desc_, length);
            desc[length] = '\0';
        }

        // set variables
        if (qty_ >= 0)
            qty = qty_;
        
        taxable = taxable_;

        if (pPrice_ >= 0)
            pPrice = pPrice_;
        
        if (qtyNeed_ >= 0)
            qtyNeed = qtyNeed_;
    }

    // destructor
    Product::~Product() {
        delete [] pName;
    }

    // copy constructor
    Product::Product(const Product& rhs) {
        pName = nullptr;
        *this = rhs;
    }

    // copy assignment operator
    Product& Product::operator=(const Product& rhs) {
        if (this != &rhs) {
            // shallow copy
            strcpy(pSku,rhs.pSku);
            strcpy(desc,rhs.desc);
            qty = rhs.qty;
            taxable = rhs.taxable;
            pPrice = rhs.pPrice;
            qtyNeed = rhs.qtyNeed;

            // deep copy
            delete [] pName;
            // incase you're copying an empty object
            if (rhs.pName) {
                name(rhs.name());
            } else {
                pName = nullptr;
            }
        }
        return *this;
    }

    // write of file
    fstream& Product::store(fstream& file, bool newLine) const {
        file << type << "," 
            << sku() << ","
            << name() << ","
            << unit() << ","
            << taxed() << ","
            << price() << ","
            << quantity() << ","
            << qtyNeeded();
        
        if (newLine) {
            file << endl;
        }

        return file;
    }

    // read from file
    fstream& Product::load(fstream& file) {
		char pSku_[max_sku_length + 1];
		char desc_[max_unit_length + 1];
		char pName_[max_name_length + 1];
		int qty_;
		int qtyNeed_;
		double pPrice_;
		bool taxable_;
        
        file.getline(pSku_, max_sku_length, ',');
        file.getline(pName_,max_name_length, ',');
        file.getline(desc_, max_sku_length, ',');
        file >> taxable_;
        file.ignore();
        file >> pPrice_;
        file.ignore();
        file >> qty_;
        file.ignore();
        file >> qtyNeed_;

        Product temp(pSku_, pName_, desc_, qty_, taxable_, pPrice_, qtyNeed_);
        *this = temp;

        return file;
    }

    // print object
    ostream& Product::write(ostream& os, bool linear) const {
     // print linearly
        if (!isEmpty() && isClear()) {
            if (linear) {
                os << setfill(' ') << setw(7) << left << sku() << "|"
                << setw(20) << name() << "|" 
                << setw(7) << setprecision(2) << fixed << right << cost()
                << "|" << setw(4) << quantity() << "|" 
                << setw(10) << left << unit() << "|" 
                << setw(4) << right << qtyNeeded() << "|";
            } else {
            // print fancily
                os << " Sku: " << sku() << endl
                << " Name (no spaces): " << name() << endl
                << " Price: " << price() << endl 
                << " Price after tax: ";  
                if (taxed()) {
                    os << cost();
                } else {
                    os << " N/A";
                }
                os << endl << " Quantity on Hand: " << quantity() 
                << " " << unit() << endl
                << " Quantity needed: " << qtyNeeded();
            }
        } else if (!isClear()) {
            os << message();
        }
        
        return os;
    }

    // input
    istream& Product::read(istream& is) {
        error.clear(); // clear any previous errors

        //char type_;
		char pSku_[max_sku_length + 1];
		char desc_[max_unit_length + 1];
		char pName_[max_name_length + 1];
		int qty_;
		int qtyNeed_;
		double pPrice_;
		bool taxable_;
        char taxed;
        bool ok = true;

        // reset stream before proceeding
        cin.clear();

        // prompt for input
        cout << " Sku: ";
        cin >> pSku_;

        cout << " Name (no spaces): ";
        cin >> pName_;

        cout << " Unit: ";
        cin >> desc_;

        cout << " Taxed? (y/n): ";
        cin >> taxed;
        // check for input errors after input
        switch (taxed) {
            case 'Y':
            case 'y':
                taxable_ = true;
                break;
            case 'N':
            case 'n':
                taxable_ = false;
                break;
            default:
                is.setstate(std::ios::failbit);
                message("Only (Y)es or (N)o are acceptable");
                ok = false;
        }

        if (ok) {
            cout << " Price: ";
            cin >> pPrice_;
            if (is.fail()) {
                message("Invalid Price Entry");
                ok = false;
            }
        }

        if (ok) {
            cout << " Quantity on hand: ";
            cin >> qty_;
            if (is.fail()) {
                message("Invalid Quantity Entry");
                ok = false;
            }
        }

        if (ok) {
            cout << " Quantity needed: ";
            cin >> qtyNeed_;
            if (is.fail()) {
                message("Invalid Quantity Needed Entry");
                ok = false;
            }
        }

        if (ok) {
            Product temp(pSku_, pName_, desc_, qty_, taxable_, pPrice_, qtyNeed_);
            *this = temp;
        }

        cin.ignore();

        return is;
    }

    // check if sku matches
    bool Product::operator==(const char* pSku_) const {
        return (strcmp(sku(),pSku_) == 0);
    }

    // return total cost
    double Product::total_cost() const {
        double cost = pPrice;
        if (taxed()) {
            cost *= (1 + tax_rate);
        }
        return (cost * qty);
    }

    // update quantity on hand
    void Product::quantity(int qty_) {
        if (qty_ >= 0) {
            qty = qty_;
        }
    }

    // check if object is empty
    bool Product::isEmpty() const {
        return (!pName);
    }

    // return quantity needed
    int Product::qtyNeeded() const {
        return qtyNeed;
    }

    // return quantity on hand
    int Product::quantity() const {
        return qty;
    }

    // compare sku #
    bool Product::operator>(const char* pSku_) const {
        if (pSku_) {
            return (strcmp(pSku_, sku()) > 0);
        } else {
            return false;
        }
    }

    // compare sku #
    bool Product::operator>(const iProduct& rhs) const {
        return (*this > rhs.sku());
    }
    
    // add to quantity on hand
    int Product::operator+=(int qty_) {
        if (!isEmpty())
            qty += qty_;

        return qty;
    }

    //helper functions
    // output
    ostream& operator<<(ostream& os, const iProduct& rhs) {
        rhs.write(os, true);
        return os;
    }

    // input
    istream& operator>>(istream& is, iProduct& rhs) {
        rhs.read(is);
        return is;
    }

    // add total cost of product to double
    double operator+=(double& lhs, const iProduct& rhs) {
        if (!rhs.isEmpty()) {
            lhs += rhs.total_cost();
        }
        
        return lhs;
    }
}