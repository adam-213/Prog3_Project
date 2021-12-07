#pragma once

#include <iomanip>
#include <string>
#include <sstream>

const int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
class Date
{

    int day{};  //From start of the year
    int year{};
public:
    Date();
    //*Integer Constructor without default values
    Date(int day0, int month0, int year0);
    //* String constructof in format DD-MM-YYYY, Year technically can be anything if it's not negative
    explicit Date(std::string &date);
    //* Year in bool out with info if any positive year is leap.
    static bool isLeap(int year);
    //* converts date (DD-MM-YYYY) to day from 1.January + output from this function so 1.2 would be 32;
    static int toDay(int day0, int month0, int year0);
    //* converts back from 1.January + days from start of the year, year to DD-MM-YYYY
    static std::string fromDay(int day0,int year0);
    //* Set class variables' day,year to Days from start of the year and year.(From 3 ints)
    bool putDate(int day0, int month0, int year0);
    //* Set class variables' day,year to Days from start of the year and year.(From string)
    bool putDate(const std::string &date0);
    //*date getter in format string DD-MM-YYYY
    std::string getDate() const;

    //Hopefully these don't need comments
    bool operator==(const Date &otherDate) const;

    bool operator<(const Date &otherDate) const;

    bool operator<=(const Date &otherDate) const;

    bool operator>=(const Date &otherDate) const;

    bool operator>(const Date &otherDate) const;

    bool operator!=(const Date &otherDate) const;

    int getDay() const
    {return day;};

    int getYear() const
    {return year;};

};
//* Put stringstream in format DD-MM-YYYY to the Date object with help of some class functions
bool operator>>(std::istringstream &is, Date &inputDate);
