#include <numeric>
#include "Fridge.h"

bool pairDateComp(const std::pair<int, Item *> lhs, const std::pair<int, Item *> rhs)
{
    if (lhs.second->getExpirationDate() <= rhs.second->getExpirationDate())
        return true;
    return false;
}


Item *Fridge::get(std::string name)
{
    std::vector<std::pair<int, Item *>> all_items;
    all_items.reserve(shelves.size());
    for (int i = 0; i < shelves.size(); i++)
    {
        all_items.emplace_back(i, shelves[i].getSmallest(name));
    }
    if (!all_items.empty())
    {
        //sorts tuple(shelfNum,Item) by item date and then updates the correct shelf by the correct ammount, returns pointer to the Item
        std::sort(all_items.begin(), all_items.end(), pairDateComp);
        shelves[all_items[0].first].updateFreeSpace(-all_items[0].second->getName().size());
        return all_items[0].second;
    }
    return nullptr;
}

std::vector<Item *> Fridge::closeToExpiration(int threshold)
{
    std::vector<Item *> expiresSoon;

    for (auto &shelf: shelves)
    {
        for (auto &item: shelf.getShelf())
        {
            if (item.goodDays() <= threshold)
                expiresSoon.push_back(&item);
        }
    }
    return expiresSoon;
}

std::vector<Item *> Fridge::expired()
{
    //if set to 0 it would return everything that's expired and that expires today
    return this->closeToExpiration(-1);
}

int Fridge::numOfExpired()
{
    return this->expired().size();
}

std::vector<Item *> Fridge::inventory()
{
    std::vector<Item *> fullInv;
    for (auto &shelf: shelves)
    {
        for(auto &item: shelf.getShelf())
        {
            fullInv.push_back(&item);
        }
    }
    return fullInv;
}

std::vector<Item *> Fridge::inventory(int shelf)
{
    //Cant just return the getShelf because it returns actual vector of things, We just want references to them
    std::vector<Item *> inv;
    for (auto &item: shelves[shelf].getShelf())
    {
        inv.push_back(&item);
    }
    return inv;
}

int Fridge::free()
{
    int freeSpace = 0;
    for (auto &shelf: shelves)
    {
        freeSpace += shelf.getFreeSpace();
    }
    return freeSpace;
}

int Fridge::free(int shelf)
{
    return shelves[shelf].getFreeSpace();
}

Fridge::Fridge(std::vector<int> shelfSpace)
{
    auto c = 0;
    for(auto &size: shelfSpace)
    {
        //this is some cool stuff specifically the emplace back, which takes the params and calls the constructor in place.
        this->shelves.emplace_back(size,c);
    }
    std::accumulate(shelfSpace.begin(),shelfSpace.end(),this->space);
}








