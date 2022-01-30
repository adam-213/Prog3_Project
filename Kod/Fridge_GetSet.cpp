#include "../Headers/Fridge.h"

//GETTERS
Date Fridge::getCurrentDate() const
{
    return currentDate;
}

std::vector<Shelf *> Fridge::getShelves()
{
    std::vector<Shelf *> out;
    for (auto &shelf: shelves)
    {
        out.push_back(&shelf);
    }
    return out;
}

std::vector<Item *> Fridge::getOverFlow()
{
    return overflow.getItems();
}

std::vector<std::pair<std::string, const Item *>> Fridge::getOrders() const
{
    std::vector<std::pair<std::string, const Item *>> out;
    for (auto &i: onOrder)
    {
        auto pair = std::make_pair(i.first, &i.second);
        out.push_back(pair);
    }
    return out;
}

int Fridge::getCounter() const
{
    return actionCounter;
}

//SETTERS

void Fridge::setCurrentDate(std::string date)
{
    currentDate = Date(std::move(date));
}

void Fridge::insertToOverflow(Item &&it)
{
    overflow.store(std::move(it));
}