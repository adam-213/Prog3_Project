#include "../Headers/Orders_Generators.h"
#include "../Headers/Fridge.h"


void Fridge::advanceDay()
{
    this->currentDate + 1;
    this->actionCounter = 0;
    this->arrivalChecker();
}

void Fridge::dayUpdater()
{
    if(actionCounter >= 3)
        this->advanceDay();
}

void Fridge::itemToOrder(std::string item, int count)
{
    actionCounter++;
    for (int i = 0; i < count; i++)
    {
        auto rand = basicExpiryGen();
        auto tempItem = Item(item, Date::fromDay(rand.first, rand.second));
        std::string arrivalDate = (currentDate + arrivalTimeGen()).getDate();
        this->onOrder.insert(std::make_pair(arrivalDate, std::move(tempItem)));
    }
}

void Fridge::itemToOrder(std::string item)
{
    this->itemToOrder(std::move(item), 1);
}

int Fridge::orderPutVector(std::vector<Item*> itemVector,bool fromShelf = false)
{
    int c = 0;

    for (auto *it: itemVector)
    {
        if(!orderPut(it,fromShelf))
            c++;
    }
    return c;
}

bool Fridge::orderPut(Item* item,bool fromShelf)
{
    bool willFit = false;
    for (auto &shelf: shelves)
    {
        if (shelf.getFreeSpace() >= item->getName().size())
        {
            willFit = true;
            break;
        }
    }
    if (willFit)
    {
        if(fromShelf)
        {
            item->setExpiration((item->getExpiration() + std::floor(item->goodDays() * 2)) - 2 * item->outsideDays());
        }
        this->put(std::move(*item));
        return true;
    }
    else if (!fromShelf)
    {
        item->setExpiration(item->getExpiration() - std::floor(item->goodDays() / 2));
        this->overflow.store(std::move(*item));
        return false;
    }
    else
    {
        item->anotherDayOutside();
        return false;
    }
}

int Fridge::arrivalChecker()
{
    typedef std::multimap<std::string, Item>::iterator MMAPIterator;

    this->orderPutVector(overflow.sortedByExpiry(),true);

    if(onOrder.find(currentDate.getDate()) != onOrder.end())
    {
        std::pair<MMAPIterator, MMAPIterator> result = onOrder.equal_range(currentDate.getDate());
        for (auto it = result.first; it != result.second; it++)
        {
            this->orderPut(&it->second);
        }
    }
    return overflow.getContents().size();
}

void Fridge::orderVector(std::vector<std::pair<std::string, int>> pairVector)
{
    for(auto &pair: pairVector)
    {
        this->itemToOrder(pair.first,pair.second);
    }
}