/*
OOP244 Final Project: Milestone 3
Student Name:   Kenneth Yue
Student Number: 127932176
Professor:      Tamanna Chhabra
Course:         OOP244
Section:        HH
Date:           Mar 28, 2018
*/

#ifndef AMA_PRODUCT_H
#define AMA_PRODUCT_H
#include "ErrorState.h"
#include "iProduct.h"

namespace AMA {
	const int max_sku_length = 7;
	const int max_unit_length = 10;
	const int max_name_length = 75;
	const double tax_rate = 0.13;

	class Product : public iProduct {
		char type;
		char pSku[max_sku_length + 1];
		char desc[max_unit_length + 1];
		char* pName;
		int qty;
		int qtyNeed;
		double pPrice;
		bool taxable;
		ErrorState error;

		protected:
			// change the name of the product
			void name(const char*);
			// return the name
			const char* name() const;
			// return the sku
			const char* sku() const;
			// return the unit
			const char* unit() const;
			// return true if taxable
			bool taxed() const;
			// returns the price
			double price() const;
			// returns the total cost of the object
			double cost() const;
			// sets the error message
			void message(const char*);
			// returns the error message
			const char* message() const;
			// check if the error message is clear
			bool isClear() const;

		public:
			// constructors
			Product(char type_ = 'N');
			Product(const char*, const char*, const char*, 
				int qty_ = 0, bool taxable_ = true, double price_ = 0.0, int qtyNeed_ = 0);
			// copy constructor
			Product(const Product&);
			// copy assignment operator
			Product& operator=(const Product&);
			// deconstructor
			~Product();

			// read / write to/from file
			std::fstream& store(std::fstream&, bool newLine = true) const;
			std::fstream& load(std::fstream&);
			// input / output
			std::ostream& write(std::ostream&, bool linear) const;
			std::istream& read(std::istream&);

			// check if sku match
			bool operator==(const char* sku) const;
			// returns total cost
			double total_cost() const;
			// update quantity
			void quantity(int);
			// check if object is empty
			bool isEmpty() const;
			// returns amount needed
			int qtyNeeded() const;
			// returns amount on hand
			int quantity() const;
			// compares SKU #s
			bool operator>(const char*) const;
			bool operator>(const iProduct&) const;
			// add to quantity on hand
			int operator+=(int);
	};

	// helper functions
	// output
	std::ostream& operator<<(std::ostream&, const iProduct&);
	// input
	std::istream& operator>>(std::istream&, iProduct&);

	// add total cost to double
	double operator+=(double&, const iProduct&);
	
}

#endif //AMA_PRODUCT_H