#pragma once

#include <exception>
#include "Date.h"

const Date DATE(1, 1, 1970);
const Date dummyExpiration(0, 0, 0);

class Item
{
    std::string name;
    Date expiration = Date(0, 0, 0000);
    int daysOutside = 0;

public:
    Item();

    //* Constructor without expiration date(usable but useless)
    explicit Item(std::string name0); // when you put things in that don't care
    //* Constructor with string as expiration date DD-MM-YYYY
    Item(std::string name0, const std::string &expirationDate);

    //* Constructor with previously declared date object
    Item(std::string name0, const Date &expirationDate);

    //* Deleting copy constructor - not needed can't copy Items
    Item(const Item &) = delete;

    //* Move constructor for moving with std::move
    Item(Item &&source) noexcept;

    //* Returns *this object - Used for taking things out of the fridge
    //[[maybe_unused]] Item get();

    //* Usable but only used as internal method - setter for class variables (Could be made private)
    bool put(std::string name0, const std::string &expirationDate0);

    //* for taking inventory etc.
    std::string getName() const;

    //* Obvious ?
    std::string getExpirationDate() const;

    Date getExpiration() const
    {return this->expiration;};

    void setExpiration(Date newExp)
    {this->expiration = newExp;};

    //* return Expiration date - global variable date in days
    int goodDays(const Date &current_date);

    int goodDays();

    int outsideDays() const
    {return daysOutside;};

    void anotherDayOutside()
    {daysOutside += 1;};

    //* if global variable current_date > expiration date return true
    bool isBad(const Date &current_date);

    bool isBad();

    //* Needed for deletion of Items from shelves.
    Item &operator=(const Item &other) = default;


};

//*Exception for when there isn't such item in the fridge.
class Item_Exc : public std::exception
{
    std::string text = "We've looked twice and rechecked it but such item is not in the fridge";
public:
    [[nodiscard]] const char *what() const noexcept override
    { return text.c_str(); };
};