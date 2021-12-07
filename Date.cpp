#include "Date.h"

bool Date::putDate(int day0, int month0, int year0)
{
    if (1 > day0)
    {
        return false;
    }
    switch (month0)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if (day0 <= 31)
                break;
            return false;
        case 4:
        case 6:
        case 9:
        case 11:
            if (day0 <= 30)
                break;
            return false;
        case 2:
            if (isLeap(year0) && day0 <= 29)
            {
                return true;
            }
            if (!isLeap(year0) && day0 <= 28)
            {
                return true;
            }
            return false;
        default:
            return false;

    }
    day = toDay(day0, month0, year0);
    year = year0;
    return true;
}


bool Date::putDate(const std::string &date0)
{
    std::istringstream is(date0);
    if (is >> *this)
        return true;
    return false;
}

std::string Date::getDate() const
{
    return fromDay(this->day, this->year);
}


Date::Date(int day0, int month0, int year0)
{
    this->putDate(day0, month0, year0);
}

Date::Date(std::string &date)
{
    this->putDate(date);
}

Date::Date()
= default;



