
#include "../Headers/Shelf.h"


bool Shelf::store(Item &&item)
{
    if (this->shelfFree >= item.getName().size())
    {
        if (this->updateFreeSpace(-item.getName().size()))
            this->stores.push_back(std::move(item));

        return true;
    }
    return false;
}

bool dateComp(const Item *lhs, const Item *rhs)
{
    if (lhs->getExpirationDate() <= rhs->getExpirationDate())
        return true;
    return false;
}

Item Shelf::get(const std::string itemName)
{
    std::vector<Item *> temp;
    for (auto &item: stores)
    {
        if (item.getName() == itemName)
        {
            temp.push_back(&item);
        }
    }
    if (!temp.empty())
    {
        std::sort(temp.begin(), temp.end(), dateComp);
        this->updateFreeSpace(itemName.size());
        auto itemRT = std::move(*temp[0]);
        this->deleter();
        return itemRT;
    }
    return {};
}

void Shelf::deleter()
{
    for (auto i = 0; i < stores.size(); i++)
    {
        if (stores[i].getName().empty() && stores[i].getExpirationDate().empty())
        {
            stores.erase(stores.begin()+i);
        }
    }
}


bool Shelf::updateFreeSpace(int changeInSpace)
{
    if (shelfFree + changeInSpace < 0 || shelfFree + changeInSpace > shelfSpace)
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
    std::vector<Item *> temp;
    for (auto &item: stores)
    {
        if (item.getName() == itemName)
        {
            temp.push_back(&item);
        }
    }
    if (!temp.empty())
    {
        std::sort(temp.begin(), temp.end(), dateComp);
        return temp[0];
    }
    return nullptr;
}


void Shelf::removeItem(const Item &original)
{
    //I just can't explain this one
    //Looks throught the vector stores and finds the Item which matches the parameter then deletes it.
    auto ref = &original;
    stores.erase(
            std::remove_if(stores.begin(), stores.end(),
                           [&ref](const Item &it) -> bool
                           {
                               return ref == &it;
                           }
            )
    );
}

std::vector<Item *> Shelf::sortedByExpiry()
{
    std::vector<Item *> temp;
    for (auto &item: stores)
    {
        temp.push_back(&item);
    }
    if (!temp.empty())
    {
        std::sort(temp.begin(), temp.end(), dateComp);
        return temp;
    }
    return temp;
}



