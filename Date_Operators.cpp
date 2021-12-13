#include "Date.h"


bool Date::operator==(const Date &otherDate) const
{
    if (year == otherDate.year)
        if (day == otherDate.day)
            return true;

    return false;
}

bool Date::operator<(const Date &otherDate) const
{
    if (this->year < otherDate.year)
        return true;
    if (this->year == otherDate.year)
        if (this->day < otherDate.day)
            return true;

    return false;
}

bool Date::operator<=(const Date &otherDate) const
{
    if (*this == otherDate)
        return true;
    if (*this < otherDate)
        return true;
    return false;
}

bool Date::operator>=(const Date &otherDate) const
{
    if (*this == otherDate)
        return true;
    if (!(*this < otherDate))
        return true;
    return false;

}

bool Date::operator>(const Date &otherDate) const
{
    if (!(*this <= otherDate))
        return true;
    return false;
}

bool Date::operator!=(const Date &otherDate) const
{
    if (!(*this == otherDate))
        return true;
    return false;
}

bool operator>>(std::istringstream &is, Date &inputDate)
{
    char dash;
    int d = 0, m = 0, y = 0;
    if (is >> d >> dash)
    {
        if (dash != '-') is.setstate(std::ios::failbit);
        if (is >> m >> dash)
        {
            if (dash != '-') is.setstate(std::ios::failbit);
            if (is >> y)
            {
                return inputDate.putDate(d, m, y);
            }
        }
    }
    return false;
}
