#include "../gtest/gtest.h"

#include "../Headers/Fridge.h"

using namespace ::testing;

TEST(Orders_Simple, One_Thing)
{
    std::vector<int> space{1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto fridge = Fridge(space, "28-12-2019");
    fridge.itemToOrder("apple");
    auto timer = 0;
    for (timer; fridge.free() == 45; timer++)
    {
        fridge.advanceDay();
    }
    ASSERT_EQ(fridge.free(), 40);
    ASSERT_EQ(fridge.numOfExpired(), 0);
    ASSERT_EQ(fridge.inventory().size(), 1);
}

TEST(Orders_Simple, Multiple_One_Thing)
{
    std::vector<int> space{1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto fridge = Fridge(space, "28-12-2019");
    fridge.itemToOrder("apple", 2);
    auto timer = 0;
    for (timer; fridge.free() != 35; timer++)
    {
        fridge.advanceDay();
    }
    ASSERT_EQ(fridge.free(), 35);
    ASSERT_EQ(fridge.numOfExpired(), 0);
    ASSERT_EQ(fridge.inventory().size(), 2);
}

TEST(Orders_Simple, Vector_Of_Things)
{
    std::vector<int> space{1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto fridge = Fridge(space, "28-12-2019", 1337);
    std::vector<std::pair<std::string, int>> toOrder;
    toOrder.emplace_back("apple", 2);
    toOrder.emplace_back("banana", 2);
    fridge.vectorToOrder(toOrder);
    auto timer = 0;
    for (timer; fridge.free() != 23; timer++)
    {
        fridge.advanceDay();
    }
    ASSERT_EQ(fridge.free(), 23);
    ASSERT_EQ(fridge.inventory().size(), 4);
    ASSERT_EQ(fridge.numOfExpired(), 0);

}

TEST(Orders_Simple, Overflow)
{
    std::vector<int> space{1, 2, 3};
    auto fridge = Fridge(space, "28-12-2019");
    fridge.put("foo", "01-01-2020");
    fridge.itemToOrder("bar");
    ASSERT_EQ(fridge.free(), 3);
    ASSERT_EQ(fridge.getCurrentDate().getDate(), "29-12-2019");
    auto timer = 0;
    for (timer; timer <= 20; timer++)
    {
        fridge.advanceDay();
    }
    ASSERT_EQ(fridge.free(), 3);
    ASSERT_EQ(fridge.inventory().size(), 1);
    ASSERT_EQ(fridge.itemsInOverflow(), 1);
}