#pragma once

#include "Shelf.h"
#include "Item.h"
#include "FileOps.h"
#include "Orders.h"


class Fridge
{
    std::vector<Shelf> shelves;
    std::vector<Item> onOrder; //things that are on order will arrive in "future"
    int space;
private:

public:
    explicit Fridge(std::vector<int> shelfSpace);

    //* Returns Item with the closest expiration date to current Date and matching name
    Item *get(std::string name);

    //* Inserts Item into the first shelf(from bottom)  that has space for it. Returns shelf number  or -1 if item couldn't be inserted
    int put(Item &&item);

    //* Insert Item into the shelf with specified index else return -1
    int put(Item &&item, int shelfNum);

    //* Create item with name and expiration date and insert it to the first shelf(from bottom) with enough space else return -1
    int put(std::string name, std::string date);

    //* Create item with name and expiration date and try inserting it to the #shelf with enough space else return -1
    int put(std::string name, std::string date, int shelfNum);

    //* Returns vector of references to items whose expiration dated is within a constant from current day
    std::vector<Item *> closeToExpiration(int treshold = 5);

    //* Vector of expired references to expired items in the fridge
    std::vector<Item *> expired();

    //* Number of expired things in the fridge
    int numOfExpired();

    //* All thy things from all thy fridge
    std::vector<Item*> inventory();

    //* All things on the # shelf
    std::vector<Item*> inventory(int shelf);

    //* number of free "slots" in the fridge
    int free();

    //* number of free "slots" on a given shelf
    int free(int shelf);


    //TODO Later
    void InvFromFile(std::string filename);

    //* Put item on order TODO probably make them arrive in some number of days and be automatically put into the fridge
    bool order(Item);

    //* Put vector of items on order ^^^^
    std::string order(std::vector<Item>);

};