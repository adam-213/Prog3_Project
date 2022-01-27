#pragma once

#include "Shelf.h"
#include "Item.h"
#include "FileOps.h"

#include <numeric>
#include <map>

const std::string DUMMY_DATE = "01-01-1970";

class Fridge
{
    Date currentDate;
    int actionCounter = 0;
    std::vector<Shelf> shelves; //Last shelf is an overflow shelf that isn't actually in the fridge
    std::multimap<std::string, Item> onOrder; //things that are on order will arrive in "future"
    Shelf overflow; //* Shelf outside the fridge - Any items in it have halved Expiration Date
    int space = 0;


private:

public:
    Fridge(std::vector<int> shelfSpace, Date curDate);

    Fridge(std::vector<int> shelfSpace, std::string curDate);

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

    //* Returns vector of references to items whose expiration dated is within a constant from current day
    std::vector<Item *> closeToExpiration(int threshold=5 ,bool internal=false);

    //* Vector of expired references to expired items in the fridge
    std::vector<Item *> expired(bool internal=false);

    //* Number of expired things in the fridge
    int numOfExpired();

    //* All thy things from all thy fridge
    std::vector<Item *> inventory();

    //* All things on the # shelf
    std::vector<Item *> inventory(int shelf);

    //TODO 5 above for overflow

    //* number of free "slots" in the fridge
    int free();

    //* number of free "slots" on a given shelf
    int free(int shelf);

    Date getCurrentDate() const
    {return currentDate;};

    //* README
    // i wawnted to write something but i forgot
    //
    //
    //
    //
    // *//


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
    void orderVector(std::vector<std::pair<std::string, int>> pairVector);


    //TODO Later




    void InvFromFile(std::string filename);
};