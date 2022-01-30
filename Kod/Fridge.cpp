
#include "../Headers/Fridge.h"

bool pairDateComp(const std::pair<int, Item *> lhs, const std::pair<int, Item *> rhs)
{
    if (lhs.second->getExpirationDate() <= rhs.second->getExpirationDate())
        return true;
    return false;
}


Item Fridge::get(std::string name)
{
    actionCounter += 1;
    std::vector<std::pair<int, Item *>> all_items;
    for (int i = 0; i < shelves.size(); i++)
    {
        auto item = shelves[i].getSmallest(name);
        if (item)
        {
            std::pair<int, Item *> pair(i, item);
            all_items.push_back(pair);
        }

    }
    if (!all_items.empty())
    {
        //sorts tuple(shelfNum,Item) by item date and then updates the correct shelf by the correct ammount, returns pointer to the Item
        std::sort(all_items.begin(), all_items.end(), pairDateComp);
        shelves[all_items[0].first].updateFreeSpace(all_items[0].second->getName().size());
        auto item = std::move(*all_items[0].second);
        shelves[all_items[0].first].removeItem(item);
        dayUpdater();
        return std::move(item);
    }
    throw Item_Exc();
}

std::vector<Item *> Fridge::closeToExpiration(int threshold, bool internal)
{
    if (!internal)
    {
        actionCounter += 1;
        dayUpdater();
    }
    std::vector<Item *> expiresSoon;

    for (auto &shelf: shelves)
    {
        for (auto &item: shelf.getContents())
        {
            auto x = item.goodDays(currentDate);
            if (x <= threshold && ((x >= 0) || threshold == -1))
                expiresSoon.push_back(&item);
        }
    }
    return expiresSoon;
}

std::vector<Item *> Fridge::expired(bool internal)
{
    if (!internal)
    {
        actionCounter += 1;
        dayUpdater();
    }
    //if set to 0 it would return everything that's expired and that expires today
    return this->closeToExpiration(-1, true);
}

int Fridge::numOfExpired()
{
    actionCounter += 1;
    dayUpdater();
    return this->expired(true).size();
}

std::vector<Item *> Fridge::inventory()
{
    actionCounter += 1;
    std::vector<Item *> fullInv;
    for (auto &shelf: shelves)
    {
        for (auto &item: shelf.getContents())
        {
            fullInv.push_back(&item);
        }
    }
    dayUpdater();
    return fullInv;
}

std::vector<Item *> Fridge::inventory(int shelf)
{
    actionCounter += 1;
    //Cant just return the getContents because it returns actual vector of things, We just want references to them
    std::vector<Item *> inv;
    for (auto &item: shelves[shelf].getContents())
    {
        inv.push_back(&item);
    }
    dayUpdater();
    return inv;
}

int Fridge::free()
{
    actionCounter += 1;
    int freeSpace = 0;
    for (auto &shelf: shelves)
    {
        freeSpace += shelf.getFreeSpace();
    }
    dayUpdater();
    return freeSpace;
}

int Fridge::free(int shelf)
{
    actionCounter += 1;
    dayUpdater();
    return shelves[shelf].getFreeSpace();
}

Fridge::Fridge(std::vector<int> shelfSpace, Date curDate, int seed) : overflow(999999, 999)
{
    auto c = 0;
    this->seed = seed;
    this->currentDate = curDate;
    for (auto &size: shelfSpace)
    {
        //this is some cool stuff specifically the emplace back, which takes the params and calls the constructor in place.
        this->shelves.emplace_back(size, c);
        c++;
    }
    std::accumulate(shelfSpace.begin(), shelfSpace.end(), this->space);
}

Fridge::Fridge(std::vector<int> shelfSpace, std::string curDate, int seed) : overflow(999999, 999)
{
    auto c = 0;
    this->seed = seed;
    this->currentDate = Date(curDate);
    for (auto &size: shelfSpace)
    {
        //this is some cool stuff specifically the emplace back, which takes the params and calls the constructor in place.
        this->shelves.emplace_back(size, c);
        c++;
    }
    std::accumulate(shelfSpace.begin(), shelfSpace.end(), this->space);
}

Fridge::Fridge() = default;