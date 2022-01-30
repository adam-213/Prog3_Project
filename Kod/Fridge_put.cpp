#include <cmath>
#include "../Headers/Fridge.h"

int Fridge::put(Item &&item)
{
    actionCounter += 1;
    for (auto &shelf: shelves)
    {
        if (shelf.getFreeSpace() >= item.getName().size())
        {
            shelf.store(std::move(item));
            dayUpdater();
            return shelf.getNumber();
        }
    }

    dayUpdater();
    return -1;
}

int Fridge::put(Item &&item, int shelfNum)
{
    actionCounter += 1;
    if (shelves[shelfNum].store(std::move(item)))
    {
        dayUpdater();
        return shelfNum;
    }
    dayUpdater();
    return -1;
}


int Fridge::put(std::string name, std::string date)
{
    auto item = Item(std::move(name), Date(std::move(date)));
    return this->put(std::move(item));
}

int Fridge::put(std::string name, std::string date, int shelfNum)
{
    auto item = Item(std::move(name), Date(std::move(date)));
    return this->put(std::move(item), shelfNum);
}


int Fridge::put(std::string name, std::string date, int outside, int shelfNum)
{
    auto item = Item(std::move(name), date, outside);
    return this->put(std::move(item), shelfNum);

}
