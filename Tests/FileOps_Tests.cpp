#include "../gtest/gtest.h"

#include "../Headers/Fridge.h"
#include "../Headers/FileOps.h"

using namespace ::testing;

TEST(FileOps, Write)
{
    std::vector<int> space{3, 3, 3};
    auto fridge = Fridge(space, "28-12-2019", 1337);
    fridge.put("foo", "01-01-2020");
    fridge.put("bar", "02-01-2020");
    fridge.put("boo", "03-01-2020");
    fridge.itemToOrder("bar");
    fridge.itemToOrder("far", 4);
    for (auto timer = 0; timer < 10; timer++)
    {
        fridge.advanceDay();
    }
    fridge.itemToOrder("for", 4);
    FileOps::FridgeToFile("test1.txt", fridge);
}

TEST(FileOps, Read)
{
    Fridge fridge = FileOps::FridgeFromFile("test1.txt");
    ASSERT_EQ(fridge.getCounter(), 1);
    ASSERT_EQ(fridge.getCurrentDate().getDate(), "08-01-2020");
    ASSERT_EQ(fridge.inventory().size(), 3);
    ASSERT_TRUE(fridge.itemsInOverflow() == 5);
    ASSERT_EQ(fridge.free(), 0);
    ASSERT_TRUE(fridge.numOfExpired() >= 3);
}

TEST(FileOps, Wrong_Read)
{
    ASSERT_ANY_THROW(FileOps::FridgeFromFile("test2.txt"));
}
