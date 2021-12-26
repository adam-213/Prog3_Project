#include "Shelf.h"


bool Shelf::store(Item &&item)
{
    if (this->shelfFree >= item.getName().size())
    {
        if(this->update(item.getName().size()));
            this->stores[item.getName()] = item;

        return true;
    }
    return false;
}

Item *Shelf::get(std::string itemName)
{
    if (this->stores.find(itemName) == this->stores.end())
        return nullptr;
    else
    {
        this->update(itemName.size());
        return &this->stores[itemName];
    }

}

bool Shelf::update(int change)
{
    if(shelfFree+change < 0 || shelfFree+change > shelfSpace)
        return false;
    this->shelfFree += change;
    return true;
}

Shelf::Shelf(int space, int num)
{
    if (space > 0)
    {
        shelfSpace = space;
        if (num >= 0)
        {
            shelfNumber = num;
            shelfFree = space;
        }

    }
}



