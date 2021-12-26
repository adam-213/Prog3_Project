#include "Item.h"

#include <map>
#include <vector>

class Shelf
{
    int shelfNumber;
    int shelfSpace;
    int shelfFree;
    std::map<std::string,Item> stores;

private:
    bool update(int change);

public:
    Shelf(int space, int num);

    bool store(Item &&item);

    Item* get(std::string itemName);

    int getFreeSpace() const
    {return shelfFree;};

};