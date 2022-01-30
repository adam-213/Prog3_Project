#include "../Headers/Item.h"

#include <utility>


bool Item::put(std::string name0, const std::string &expirationDate0)
{
    name = std::move(name0);
    expiration.putDate(expirationDate0);
    return true;
}

std::string Item::getName() const
{
    return name;
}

std::string Item::getExpirationDate() const
{
    return expiration.getDate();
}

int Item::goodDays(const Date &current_date)
{
    if (expiration == dummyExpiration)
    {
        return -1;
    }
    int yearDelta = 0;
    int tempYear = current_date.getYear();
    while (true)
    {
        if (tempYear == expiration.getYear())
            break;

        Date::isLeap(tempYear) ? yearDelta += 366 : yearDelta += 365;
        tempYear < expiration.getYear() ? tempYear += 1 : tempYear -= 1;
    }

    int dayDelta = expiration.getDay() - current_date.getDay();

    if (expiration >= current_date)
    {
        return (yearDelta + dayDelta);
    }
    else
    {
        return (-yearDelta + dayDelta);
    }
}

bool Item::isBad(const Date &current_date)
{
    if (expiration != dummyExpiration)
    {
        if (this->expiration >= current_date)
            return false;
        return true;
    }
    return false;
}

Item::Item(std::string name0)
{
    name = std::move(name0);
}

Item::Item(std::string name0, const std::string &expirationDate)
{
    this->put(std::move(name0), expirationDate);
}

Item::Item(std::string name0, const Date &expirationDate)
{
    name = std::move(name0);
    expiration = expirationDate;
}

Item::Item(Item &&source) noexcept
{
    this->name = source.name;
    this->expiration = std::move(source.expiration);
    this->daysOutside = source.daysOutside;
    source.name = "";
    source.expiration = Date();
    source.daysOutside = -999;

}

int Item::goodDays()
{
    return this->goodDays(DATE);
}

bool Item::isBad()
{
    return this->isBad(DATE);
}

Item::Item(std::string name0, const std::string &expirationDate, int outside)
{
    if (this->put(std::move(name0), expirationDate))
    {
        daysOutside = outside;
    }
}


Item::Item()
= default;




