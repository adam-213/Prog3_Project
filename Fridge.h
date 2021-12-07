#pragma once
#include "Item.h"
#include "FileOps.h"
#include "Orders.h"

class Fridge
{
    std::vector<Item> fullInventory;
    std::vector<std::vector<Item>> inventoryByShelf;
    std::vector<Item> onOrder;
    int overallFullness;
    std::vector<int> shelfSpace; //TODO this will have to be configured manually maybe as a constructor (Different types of fridges)


public:
    Item get(std::string name); //preferably return the one closest to expiraton date, may make specification later

    bool put(Item); // I don't know how the thing works yet preferably just enter what it needs to initialize Item and it will do it automagicaly
    //* Returns vector of items whose expiration dated is within a constant from current day
    std::vector<Item> closeToExpiration();

    //* Number of expired things in the fridge
    int expired();

    //* All thy things from all thy fridge
    std::string inventory();

    //* All things on the # shelf
    std::string inventory(int shelf);

    //* Put item on order TODO probably make them arrive in some number of days and be automatically put into the fridge
    std::string order(Item);

    //* Put vector of items on order ^^^^
    std::string order(std::vector<Item>);

    void updateFullness();
    //* number of free "slots" in the fridge
    int free();
    //* number of free "slots" on a given shelf
    int free(int shelf);

    void InvFromFile(std::string filename);


};