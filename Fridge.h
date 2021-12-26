#pragma once

#include "Shelf.h"
#include "Item.h"
#include "FileOps.h"
#include "Orders.h"

class Fridge
{
    std::vector<Shelf> shelves;
    std::vector<Item> onOrder; //things that are on order an will arrive in "future"
private:
    void updateFullness();

public:
    //* Returns Item with the closest expiration date to current Date and matching name
    Item *get(std::string name);

    //* Inserts Item into the first shelf that has space for it. Returns number of the shelf or -1 if item couldn't be inserted
    int put(Item &&item);

    //* Insert Item into the shelf with correct index else return -1
    int put(Item &&item, int shelfNum);

    //* Create item with name and expiration date and insert it to the first shelf with enough space else return -1
    int put(std::string name, std::string date);

    //* Create item with name and expiration date and try inserting it to the #shelf with enough space else return -1
    int put(std::string name, std::string date);

    //* Returns vector of items whose expiration dated is within a constant from current day
    std::vector<Item> closeToExpiration();

    //* Number of expired things in the fridge
    int expired();

    //* All thy things from all thy fridge
    std::vector<Item> inventory();

    //* All things on the # shelf
    std::vector<Item> inventory(int shelf);

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