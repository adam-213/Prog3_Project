#pragma once

#include "Date.h"
const Date DATE(1,1,1970);
const Date dummyExpiration(0,0,0);

class Item
{
    std::string name;
    Date expiration = Date(0,0,0000);

public:
    Item();
    //* Constructor without expiration date(usable but useless)
    explicit Item(std::string name0); // when you put things in that don't care
    //* Constructor with string as expiration date DD-MM-YYYY
    Item(std::string name0, const std::string& expirationDate);
    //* Constructor with previously declared date object
    Item(std::string name0, const Date &expirationDate);
    //* Returns *this object - Used for taking things out of the fridge
    Item get();
    //* Usable but only used as internal method - setter for class variables (Could be made private)
    bool put(std::string name0, const std::string& expirationDate0);

    //* for taking inventory etc.
    std::string getName() const;
    //* Obvious ?
    std::string getExpirationDate() const;

    //* return Expiration date - global variable date in days
    int goodDays();

    //* if global variable DATE > expiration date return true
    bool isBad();

};