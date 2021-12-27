#include "Item.h"

#include <algorithm>
#include <vector>

class Shelf
{
    int shelfNumber;
    int shelfSpace;
    int shelfFree;
    std::vector<Item> stores;
    /* I've had this written with map and with set,
     * but with map there was a problem when there were multiple things named the same
     * and same with set */
public:
    //* Constructor with shelfSpace - in characters of the name of the item, and shelfNum position in the fridge from bottom up
    Shelf(int space, int num);

    //* Store the item with std::move because items can only be moved and not copied
    bool store(Item &&item);

    //* Returns the item with desired name that is closest to the expiration date. Also updates the freeSpace on the shelf
    Item *get(const std::string itemName);

    //* Same as the one above but doesn't update the free space(Used in bigger fridge getter)
    Item *getSmallest(const std::string &itemName);

    //* Updates the free space on the shelf with .size() input
    bool updateFreeSpace(int changeInSpace);

    int getFreeSpace() const
    { return shelfFree; };

    int getNumber() const
    { return shelfNumber; };

    //* returns the full reference to the stores vector. Used for taking inventory.
    std::vector<Item> &getShelf()
    { return stores; };

};