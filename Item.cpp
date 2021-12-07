#include "Item.h"

#include <utility>


bool Item::put(std::string name0, const std::string& expirationDate0)
{
    name = std::move(name0);
    expiration.putDate(expirationDate0);
    return true;
}

Item Item::get()
{
    return *this;
}

std::string Item::getName()
{
    return name;
}

std::string Item::getExpirationDate()
{
    return expiration.getDate();
}

int Item::goodDays()
{
    if(expiration == dummyExpiration)
    {
        return -1;
    }
    int yearDelta = 0;
    int tempYear = DATE.getYear();
    while(true)
    {
        if(tempYear == expiration.getYear())
            break;

        Date::isLeap(tempYear) ? yearDelta += 366 : yearDelta += 365;
        tempYear < expiration.getYear() ? tempYear += 1 : tempYear -= 1;
    }

    int dayDelta = expiration.getDay() - DATE.getDay();

    if (expiration >= DATE)
    {
        return (yearDelta + dayDelta);
    }
    else
    {
        return -(yearDelta+ dayDelta);
    }
}

bool Item::isBad()
{
    if(expiration != dummyExpiration)
    {
        if(this->expiration >= DATE)
            return false;
        return true;
    }
    return false;
}

Item::Item(std::string name0)
{
    name = std::move(name0);
}

Item::Item(std::string name0, const std::string& expirationDate)
{
    this->put(std::move(name0),expirationDate);
}

Item::Item(std::string name0, const Date &expirationDate)
{
    name = std::move(name0);
    expiration = expirationDate;
}

Item::Item()
= default;




