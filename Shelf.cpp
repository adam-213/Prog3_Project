
#include "Shelf.h"


bool Shelf::store(Item &&item)
{
    if (this->shelfFree >= item.getName().size())
    {
        if(this->updateFreeSpace(item.getName().size()))
            this->stores.push_back(item);

        return true;
    }
    return false;
}

bool dateComp(const Item* lhs, const Item* rhs)
{
    if(lhs->getExpirationDate() <= rhs->getExpirationDate())
        return true;
    return false;
}

Item *Shelf::get(const std::string itemName)
{
    std::vector<Item*> temp;
    for(auto &item: stores)
    {
        if(item.getName() == itemName)
        {
            temp.push_back(&item);
        }
    }
    if(!temp.empty())
    {
        std::sort(temp.begin(), temp.end(), dateComp);
        this->updateFreeSpace(-itemName.size());
        return temp[0];
    }
    return nullptr;
}



bool Shelf::updateFreeSpace(int changeInSpace)
{
    if(shelfFree + changeInSpace < 0 || shelfFree + changeInSpace > shelfSpace)
        return false;
    this->shelfFree += changeInSpace;
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

Item *Shelf::getSmallest(const std::string &itemName)
{
    std::vector<Item*> temp;
    for(auto &item: stores)
    {
        if(item.getName() == itemName)
        {
            temp.push_back(&item);
        }
    }
    if(!temp.empty())
    {
        std::sort(temp.begin(), temp.end(), dateComp);
        return temp[0];
    }
    return nullptr;
}



