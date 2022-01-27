#include "../Headers/Date.h"


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

Date Date::operator+(int d)
{
    auto dy = this->getDay() + d;
    if (Date::isLeap(year) && dy <= 366)
        this->day = dy;
    else if (!Date::isLeap(year) && dy <= 365)
        this->day = dy;
    else
    {
        auto tempYear = this->getYear();
        while (true)
        {
            if (Date::isLeap(tempYear) && dy <= 366)
            {
                this->day = dy;
                break;
            }
            else if (!Date::isLeap(tempYear) && dy <= 365)
            {
                this->day = dy;
                break;
            }
            Date::isLeap(tempYear) ? dy -= 366 : dy -= 365;
            tempYear += 1;
        }
        this->year = tempYear;
    }
    return *this;
}

Date Date::operator-(const int d)
{
    auto dy = this->getDay() - d;
    if (Date::isLeap(year-1) && dy > 0)
        this->day = dy;
    else if (!Date::isLeap(year-1) && dy > 0)
        this->day = dy;
    else
    {
        auto tempYear = this->getYear();
        while (true)
        {
            if (Date::isLeap(tempYear-1) && dy > 0)
            {
                this->day = dy;
                break;
            }
            else if (!Date::isLeap(tempYear-1) && dy > 0)
            {
                this->day = dy;
                break;
            }
            Date::isLeap(tempYear-1) ? dy += 366 : dy += 365;
            tempYear -= 1;
        }
        this->year = tempYear;
    }
    return *this;
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
