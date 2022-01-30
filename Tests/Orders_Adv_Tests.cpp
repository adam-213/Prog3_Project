#include "../gtest/gtest.h"

#include "../Headers/Fridge.h"

using namespace ::testing;


TEST(Orders_Advanced, Item_Replacement_From_Overflow)
{
    std::vector<int> space{1, 2, 3};
    auto fridge = Fridge(space, "28-12-2019");
    fridge.put("foo", "01-01-2020");
    fridge.itemToOrder("bar");
    ASSERT_EQ(fridge.free(), 3);
    ASSERT_EQ(fridge.getCurrentDate().getDate(), "29-12-2019");
    auto timer = 0;
    for (timer; timer <= 8; timer++)
    {
        fridge.advanceDay();
    }
    ASSERT_EQ(fridge.free(), 3);
    ASSERT_EQ(fridge.inventory().size(), 1);
    ASSERT_EQ(fridge.itemsInOverflow(), 1);

    auto item1 = fridge.get("foo");
    ASSERT_EQ(item1.getName(), "foo");
    ASSERT_EQ(item1.getExpiration().getDate(), "01-01-2020");
    ASSERT_EQ(item1.outsideDays(), 0);

    ASSERT_EQ(fridge.free(), 6);
    ASSERT_EQ(fridge.inventory().size(), 0);

    ASSERT_EQ(fridge.free(), 3);
    ASSERT_EQ(fridge.inventory().size(), 1);
    ASSERT_EQ(fridge.itemsInOverflow(), 0);

    auto item2 = fridge.get("bar");
    ASSERT_EQ(item2.getName(), "bar");
    ASSERT_TRUE(item2.outsideDays() > 0);


}

TEST(Orders_Advanced, Mutli_Replacement)
{
    std::vector<int> space{1, 3, 3};
    auto fridge = Fridge(space, "28-12-2019");
    fridge.put("foo", "01-01-2020");
    fridge.itemToOrder("bar");
    fridge.itemToOrder("bar");
    ASSERT_EQ(fridge.free(), 4);
    ASSERT_EQ(fridge.getCurrentDate().getDate(), "29-12-2019");
    auto timer = 0;
    for (timer; timer <= 8; timer++)
    {
        fridge.advanceDay();
    }
    ASSERT_EQ(fridge.free(), 1);
    ASSERT_EQ(fridge.itemsInOverflow(), 1);
    auto itemBar1 = fridge.get("bar");
    auto itemBar2 = fridge.get("bar");
    auto itemFoo = fridge.get("foo");
    ASSERT_EQ(fridge.inventory().size(), 0);
    fridge.itemToOrder("bar");
    for (timer = 0; timer <= 8; timer++)
    {
        fridge.advanceDay();
    }
    ASSERT_EQ(fridge.inventory().size(), 1);


}

