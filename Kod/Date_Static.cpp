#include "../Headers/Date.h"


bool Date::isLeap(const int year)
{
    if (year % 4 == 0)
    {
        if (year % 100 == 0)
        {
            if (year % 400 == 0)
            {
                return true;
            }
            return false;
        }
        return true;
    }
    return false;
}

int Date::toDay(int day0, int month0, int year0)
{
    if(day0 < 0) day0 *= -1;
    if(month0 < 0) month0 *= -1;
    auto tempDay = 0;
    for (auto i = 0; i < month0 - 1; i++)
    {
        tempDay += monthDays[i];
    }
    tempDay += day0;
    isLeap(year0) && month0 > 2 ? tempDay += 1 : tempDay;
    return tempDay;
}


std::string Date::fromDay(int day0, int year0)
{
    if(day0 == 0) return "";
    if(day0 < 0) day0 *= -1;
    if(year0 < 0) year0 *= -1;
    auto i = 0;
    for (i; i < 13; i++)
    {
        if (day0 <= monthDays[i] ||
            (i == 1 && day0 <= (monthDays[i] + 1) && isLeap(year0)))
            break;

        if (i == 1 && isLeap(year0))
        {
            day0 -= monthDays[i] + 1;
        }
        else
        {
            day0 -= monthDays[i];
        }
    }
    std::ostringstream output;
    output << std::setw(2) << std::setfill('0') << day0 << '-'
           << std::setw(2) << std::setfill('0') << i + 1 << '-'
           << std::setw(4) << std::setfill('0') << year0;
    if(output.str() == "00-01-0000")
        return "";
    return output.str();
}
