#include "../gtest/gtest.h"

#include "../Headers/Fridge.h"
#include "../Headers/FileOps.h"

using namespace ::testing;

TEST(Full_Scale, the_Big_T)
{
    std::vector<int> space1{4, 5, 6, 7,};
    std::vector<int> space2{3, 4, 6};
    std::string currentDateString = "30-01-2022";
    Date currentDate(currentDateString);
    int seed = 42;
    auto fridge1 = Fridge(space1, currentDateString, seed);
    auto fridge2 = Fridge(space2, currentDateString, seed);

    ASSERT_EQ(fridge1.getCurrentDate(), currentDate);
    ASSERT_EQ(fridge2.getCurrentDate(), currentDate);

    fridge1.itemToOrder("apple"); // 68
    fridge2.itemToOrder("apple");
    ASSERT_EQ(fridge1.getOrders()[0].first, fridge2.getOrders()[0].first);
    auto temp = fridge1.getOrders()[0].first;
    while (currentDate.getDate() != temp)
    {
        fridge1.advanceDay();
        fridge2.advanceDay();
        currentDate + 1;
    }
    ASSERT_TRUE(fridge1.free() == 17 && fridge2.free() == 8);

    fridge1.itemToOrder("banana");
    fridge2.itemToOrder("banana"); //73
    ASSERT_EQ(fridge1.getOrders()[0].first, fridge2.getOrders()[0].first);
    temp = fridge1.getOrders()[0].first;
    while (currentDate.getDate() != temp)
    {
        fridge1.advanceDay();
        fridge2.advanceDay();
        currentDate + 1;
    }
    ASSERT_EQ(fridge1.getCurrentDate(), currentDate); //40
    ASSERT_EQ(fridge1.inventory().size(), 2);
    ASSERT_EQ(fridge2.inventory().size(), 1);
    ASSERT_EQ(fridge2.itemsInOverflow(), 1);

    auto apple2 = fridge2.get("apple");
    ASSERT_EQ(apple2.getName(), "apple");
    ASSERT_EQ(apple2.getExpiration().getDate(), "09-03-2022");
    ASSERT_FALSE(apple2.isBad());
    ASSERT_EQ(fridge1.put(std::move(apple2)), 3);
    ASSERT_EQ(fridge1.inventory().size(), 3);
    ASSERT_EQ(fridge1.free(), 6);
    fridge2.advanceDay();
    ASSERT_EQ(fridge2.free(), 7);
    ASSERT_EQ(fridge2.itemsInOverflow(), 0);

    std::vector<std::pair<std::string, int>> toOrder{{"foo", 1},
                                                     {"bar", 1},
                                                     {"boo", 2}};
    fridge2.vectorToOrder(toOrder);

    FileOps::FridgeToFile("fridge2.txt", fridge2);
    auto fileFridge = FileOps::FridgeFromFile("fridge2.txt");

    ASSERT_EQ(fileFridge.getOrders().size(), 4);
    ASSERT_EQ(fileFridge.numOfExpired(), 0);
    ASSERT_EQ(fileFridge.free(), 7);

    while (currentDate.getDate() != "09-03-2022")
    {
        fridge1.advanceDay();
        currentDate + 1;
    }
    ASSERT_EQ(fridge1.expired().size(), 2);
    ASSERT_EQ(fridge1.expired()[0]->getName(), "apple");
    fridge1.get("apple");
    fridge1.get("apple");
    auto banana = fridge1.get("banana");
    ASSERT_EQ(banana.getName(), "banana");
    ASSERT_EQ(banana.getExpiration().getDate(), "14-03-2022");
    ASSERT_FALSE(banana.isBad());
    ASSERT_EQ(fridge1.free(), 22);

    ASSERT_EQ(fileFridge.itemsInOverflow(), 0);
    for (int i = 0; i < 4; ++i)
    {
        fileFridge.advanceDay();
    }
    ASSERT_EQ(fileFridge.itemsInOverflow(), 2);
    for (int i = 0; i < 10; ++i)
    {
        fileFridge.advanceDay();
    }
    ASSERT_EQ(fileFridge.getOverFlow()[0]->goodDays(fileFridge.getCurrentDate()), 6);
    ASSERT_EQ(fileFridge.getShelves()[0]->getContents()[0].getName(), "foo");
    ASSERT_EQ(fileFridge.closeToExpiration(5, true).size(), 0);
    ASSERT_ANY_THROW(fileFridge.get("boo"));
    ASSERT_EQ(fileFridge.free(2), 0);
    fileFridge.itemToOrder("throw", -1);
    ASSERT_EQ(fileFridge.getOrders().size(), 0);
}
