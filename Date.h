/*
OOP244 Final Project: Milestone 1
Student Name:   Kenneth Yue
Student Number: 127932176
Professor:      Tamanna Chhabra
Course:         OOP244
Section:        HH
Date:           Mar 14, 2018
*/

#ifndef AMA_DATE_H
#define AMA_DATE_H
#include <iostream>

#define NO_ERROR 0
#define CIN_FAILED 1
#define YEAR_ERROR 2
#define MON_ERROR 3
#define DAY_ERROR 4

namespace AMA {
  const int min_year = 2000;
  const int max_year = 2030;

  class Date {

    int year;
    int month;
    int day;
    int comparator;
    int errorState;

    int mdays(int, int) const;
    void errCode(int errorCode);

  public:
    Date();
    Date(int newYear, int newMonth, int newDay);

    bool operator==(const Date& rhs) const;
    bool operator!=(const Date& rhs) const;
    bool operator<(const Date& rhs) const;
    bool operator>(const Date& rhs) const;
    bool operator<=(const Date& rhs) const;
    bool operator>=(const Date& rhs) const;

    int errCode() const;
    bool bad() const;
    std::istream& read(std::istream& istr);
    std::ostream& write(std::ostream& ostr) const;
  };

  std::istream& operator>>(std::istream& is, Date& rhs);
  std::ostream& operator<<(std::ostream& os, const Date& rhs);
  
}

#endif //AMA_DATE_H