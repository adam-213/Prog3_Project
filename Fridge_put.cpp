#include "Fridge.h"

int Fridge::put(Item &&item)
{
    for(auto &shelf:shelves)
    {
        if(shelf.getFreeSpace() >= item.getName().size())
        {
            shelf.store(std::move(item));
            return shelf.getNumber();
        }
    }
    return -1;
}

int Fridge::put(Item &&item, int shelfNum)
{
    if(shelves[shelfNum].store(std::move(item)))
        return shelfNum;
    return -1;
}


int Fridge::put(std::string name, std::string date)
{
    auto item = Item(std::move(name),Date(date));
    return this->put(std::move(item));
}

int Fridge::put(std::string name, std::string date, int shelfNum)
{
    auto item = Item(std::move(name),Date(date));
    return this->put(std::move(item),shelfNum);
}