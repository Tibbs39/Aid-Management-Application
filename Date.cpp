/*
OOP244 Final Project: Milestone 1
Student Name:   Kenneth Yue
Student Number: 127932176
Professor:      Tamanna Chhabra
Course:         OOP244
Section:        HH
Date:           Mar 14, 2018
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include "Date.h"

namespace AMA {
  Date::Date() {
    year = 0;
    month = 0;
    day = 0;
    errorState = 0;
    comparator = 0;
  }

  Date::Date(int nYear, int nMonth, int nDay) {
    *this = Date();
    if (nYear >= min_year && nYear <= max_year) {
      if (nMonth >= 1 && nMonth <= 12) {
        if (nDay >= 1 && nDay <= mdays(nMonth, nYear)) {
          year = nYear;
          month = nMonth;
          day = nDay;
          comparator = year * 372 + month * 13 + day;
          errCode(NO_ERROR);
        } else {
          errCode(DAY_ERROR);
        }
      } else { 
        errCode(MON_ERROR);
      }
    } else {
      errCode(YEAR_ERROR);
    }
  }

  void Date::errCode(int errorCode) {
    errorState = errorCode;
  }
  // number of days in month mon_ and year year_
  //
  int Date::mdays(int mon, int year)const {
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
    int month = mon >= 1 && mon <= 12 ? mon : 13;
    month--;
    return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
  }

  int Date::errCode() const {
    return errorState;
  }

  bool Date::bad() const {
    return !(errorState == 0);
  }

  bool Date::operator==(const Date& rhs) const {
    return (!bad() && !rhs.bad() && comparator == rhs.comparator);
  }

  bool Date::operator!=(const Date& rhs) const {
    return (!bad() && !rhs.bad() && comparator != rhs.comparator);
  }

  bool Date::operator<(const Date& rhs) const {
    return (!bad() && !rhs.bad() && comparator < rhs.comparator);
  }

  bool Date::operator>(const Date& rhs) const {
    return (!bad() && !rhs.bad() && comparator > rhs.comparator);
  }

  bool Date::operator<=(const Date& rhs) const {
    return (!bad() && !rhs.bad() && comparator <= rhs.comparator);
  }

  bool Date::operator>=(const Date& rhs) const {
    return (!bad() && !rhs.bad() && comparator >= rhs.comparator);
  }

  std::istream& Date::read(std::istream& istr) {
    int yr, mn, dy;

    // extract year
    istr >> yr;
    if (!istr.fail()) {
      istr.ignore();
      istr >> mn;
    }

    if (!istr.fail()) {
      istr.ignore();
      istr >> dy;
    }

    if (!istr.fail()) {
      *this = Date(yr, mn, dy);
    } else {
      *this = Date();
      errCode(CIN_FAILED);
    }

    return istr;
  }

  std::ostream& Date::write(std::ostream& str) const {
    str << year << "/" 
              << std::setw(2) << std::setfill('0') << month << "/" 
              << std::setw(2) << std::setfill('0') << day;
    return str;
  }

  std::istream& operator>>(std::istream& is, Date& rhs) {
    rhs.read(is);
    return is;
  }

  std::ostream& operator<<(std::ostream& os, const Date& rhs) {
    rhs.write(os);

    return os;
  }
  
} // end of namespace AMA
