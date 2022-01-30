#pragma once

#include "Shelf.h"
#include "Item.h"

#include <numeric>
#include <map>

const std::string DUMMY_DATE = "01-01-1970";

class Fridge
{
    Date currentDate;
    int actionCounter = 0; // every 3 actions move to the next day
    //Every UI method does this - some that are "internal" don't
    std::vector<Shelf> shelves; // Shelves are initialized with some space
    //#of chars in Item names that can fit there
    std::multimap<std::string, Item> onOrder; //things that are on order will arrive in "future"
    Shelf overflow; // Shelf outside the fridge
    // Any items in it expire twice as fast
    int space = 0;
    int seed = 0; // Seed for random generators in Orders_Generators

public:
    Fridge();

    Fridge(std::vector<int> shelfSpace, Date curDate, int seed = 0);

    Fridge(std::vector<int> shelfSpace, std::string curDate, int seed = 0);

    //* Returns Item with the closest expiration date to current Date and matching name
    Item get(std::string name);

    //* Inserts Item into the first shelf(from bottom)  that has space for it. Returns shelf number  or -1 if item couldn't be inserted
    int put(Item &&item);

    //* Insert Item into the shelf with specified index else return -1
    int put(Item &&item, int shelfNum);

    //* Create item with name and expiration date and insert it to the first shelf(from bottom) with enough space else return -1
    int put(std::string name, std::string date);

    //* Create item with name and expiration date and try inserting it to the #shelf with enough space else return -1
    int put(std::string name, std::string date, int shelfNum);

    int put(std::string name, std::string date, int outside, int shelfNum);

    //* Returns vector of references to items whose expiration dated is within a constant from current day
    std::vector<Item *> closeToExpiration(int threshold = 5, bool internal = false);

    //* Vector of expired references to expired items in the fridge
    std::vector<Item *> expired(bool internal = false);

    //* Number of expired things in the fridge
    int numOfExpired();

    //* All thy things from all thy fridge
    std::vector<Item *> inventory();

    //* All things on the # shelf
    std::vector<Item *> inventory(int shelf);

    int itemsInOverflow();

    //* number of free "slots" in the fridge
    int free();

    //* number of free "slots" on a given shelf
    int free(int shelf);

    //*Used for FileOps
    void insertToOverflow(Item &&it);

    [[nodiscard]] Date getCurrentDate() const;

    //*Returns vector of pointers to Items which are on the shelves
    std::vector<Shelf *> getShelves();

    //*Returns vector of pointers to Items which are in the overflow
    std::vector<Item *> getOverFlow();

    //Returns vector of pairs as they are in the orders ArrivalDate:Pointer to Item;
    [[nodiscard]] std::vector<std::pair<std::string, const Item *>> getOrders() const;

    [[nodiscard]] int getCounter() const;

    void setCurrentDate(std::string date);

    void insertToOrder(std::pair<std::string, Item> &&pair);

    void setActionCounter(int counter);
    //*End of Usage for FileOps

    //Orders
    //* Increase day by one - Part of the orders, call arrivalChecker
    void advanceDay();

    //* Check if the action counter isn't above 3 - if it is, move to the next day
    void dayUpdater();

    //* Working method for all orders.
    void itemToOrder(std::string item, int count);

    //* Returns size of the overflow.
    int orderPutVector(std::vector<Item *> itemVector, bool fromShelf);

    //* Working method for inserting order to the fridge, - True = in fridge , false = in overflow
    bool orderPut(Item *item, bool fromShelf = false);

    //*First checks the overflow shelf - if there is space in the fridge - puts items into the fridge from quickest to spoil
    //* Checks if there are any items with arrival today; Returns number of new items in the fridge;
    int arrivalChecker();

    //*Orders single Item with this name
    void itemToOrder(std::string item);

    //* Put vector of pairs on order - pair consist of name of the item and #of said item,
    void vectorToOrder(std::vector<std::pair<std::string, int>> pairVector);


};