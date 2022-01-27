#include "../gtest/gtest.h"

#include "../Headers/Fridge.h"

using namespace ::testing;

TEST(Fridge_Base, Empty)
{
    std::vector<int> space{1, 2, 3, 4, 5, 6};
    auto fridge = Fridge(space, DUMMY_DATE);
    ASSERT_EQ(21, fridge.free());
    std::vector<Item *> Dummy;
    ASSERT_EQ(Dummy, fridge.inventory());
    ASSERT_EQ(Dummy, fridge.inventory(2));
    ASSERT_EQ(6, fridge.free(5));
    ASSERT_EQ(0, fridge.numOfExpired());
    ASSERT_EQ(Dummy, fridge.closeToExpiration());
    std::string empty = "We've looked twice and rechecked it but such item is not in the fridge";
    ASSERT_THROW(fridge.get("fridge"),Item_Exc);

}

TEST(Fridge_Base, PutGet_One_Correct_Item)
{
    std::vector<int> space{1, 2, 3, 4, 5, 6};
    auto fridge = Fridge(space, DUMMY_DATE);
    fridge.put("apple", "05-01-1970");
    ASSERT_EQ(16, fridge.free());
    ASSERT_EQ("apple", fridge.inventory()[0]->getName());
    ASSERT_EQ("05-01-1970", fridge.inventory()[0]->getExpirationDate());
    ASSERT_EQ(0, fridge.numOfExpired());
    ASSERT_EQ(6, fridge.free(5));
    ASSERT_EQ(0, fridge.free(4));

    auto apple = fridge.get("apple");
    ASSERT_EQ("apple", apple.getName());
    ASSERT_EQ("05-01-1970", apple.getExpirationDate());
    ASSERT_FALSE(apple.isBad());

    std::vector<Item *> Dummy;
    ASSERT_EQ(21, fridge.free());
    ASSERT_EQ(Dummy, fridge.inventory());
}

TEST(Fridge_Base,Put_Two_Same_Correct_Items)
{
    std::vector<int> space{1, 2, 3, 4, 5, 6};
    auto fridge = Fridge(space, DUMMY_DATE);
    fridge.put("apple", "05-02-1970");
    fridge.put("apple", "05-01-1970");
    ASSERT_EQ(11, fridge.free());
    ASSERT_EQ(fridge.inventory().size(),2);
    ASSERT_EQ("apple", fridge.inventory()[1]->getName());
    ASSERT_EQ(0, fridge.numOfExpired());
    ASSERT_EQ(1, fridge.free(5));
    ASSERT_EQ(0, fridge.free(4));

    auto apple2 = fridge.get("apple");
    ASSERT_EQ("apple", apple2.getName());
    ASSERT_EQ("05-01-1970", apple2.getExpirationDate());

    std::vector<Item *> Dummy;
    ASSERT_FALSE(Dummy == fridge.inventory());
    ASSERT_EQ(6, fridge.free(5));
    ASSERT_EQ(0, fridge.free(4));
    ASSERT_EQ(fridge.inventory().size(),1);

    auto apple1 = fridge.get("apple");
    ASSERT_EQ("apple", apple1.getName());
    ASSERT_EQ("05-02-1970", apple1.getExpirationDate());

    ASSERT_EQ(21, fridge.free());
    ASSERT_EQ(Dummy, fridge.inventory());
}

TEST(Fridge_Advanced,Date_Cycle)
{
    std::vector<int> space{1, 2, 3, 4, 5, 6};
    auto fridge = Fridge(space,"27-12-2021");
    fridge.advanceDay();
    ASSERT_EQ("28-12-2021",fridge.getCurrentDate().getDate());
    fridge.free();
    fridge.numOfExpired();
    fridge.inventory();
    ASSERT_EQ("29-12-2021",fridge.getCurrentDate().getDate());
    fridge.advanceDay();
    ASSERT_EQ("30-12-2021",fridge.getCurrentDate().getDate());
    fridge.advanceDay();
    ASSERT_EQ("31-12-2021",fridge.getCurrentDate().getDate());
    fridge.advanceDay();
    ASSERT_EQ("01-01-2022",fridge.getCurrentDate().getDate());
    fridge.advanceDay();
    ASSERT_EQ("02-01-2022",fridge.getCurrentDate().getDate());
}

TEST(Fridge_Advanced,Date_Cycle_Ferbruary_Leap)
{
    std::vector<int> space{1, 2, 3, 4, 5, 6};
    auto fridge = Fridge(space,"26-02-2020");
    fridge.advanceDay();
    ASSERT_EQ("27-02-2020",fridge.getCurrentDate().getDate());
    fridge.free();
    fridge.numOfExpired();
    fridge.inventory();
    ASSERT_EQ("28-02-2020",fridge.getCurrentDate().getDate());
    fridge.advanceDay();
    ASSERT_EQ("29-02-2020",fridge.getCurrentDate().getDate());
    fridge.advanceDay();
    ASSERT_EQ("01-03-2020",fridge.getCurrentDate().getDate());
    fridge.advanceDay();
    ASSERT_EQ("02-03-2020",fridge.getCurrentDate().getDate());
    fridge.advanceDay();
    ASSERT_EQ("03-03-2020",fridge.getCurrentDate().getDate());
}

TEST(Fridge_Advanced,Put_With_Date_Cycle)
{
    std::vector<int> space{1, 2, 3, 4, 5, 6,7, 8, 9};
    auto fridge = Fridge(space, "28-12-2019");
    ASSERT_EQ(fridge.getCurrentDate().getDate(),"28-12-2019");
    fridge.advanceDay();
    ASSERT_EQ(fridge.getCurrentDate().getDate(),"29-12-2019");
    fridge.put("foo","01-01-2020");
    ASSERT_EQ(fridge.closeToExpiration().size(), 1);
    ASSERT_EQ(fridge.numOfExpired(),0);
    ASSERT_EQ(fridge.getCurrentDate().getDate(),"30-12-2019");
    fridge.put("bar","01-01-2019");
    ASSERT_EQ(fridge.closeToExpiration().size(), 1);
    ASSERT_EQ(fridge.numOfExpired(),1);
    ASSERT_EQ(fridge.getCurrentDate().getDate(),"31-12-2019");

    auto item2got = fridge.get("bar");
    ASSERT_EQ("bar", item2got.getName());
    ASSERT_EQ("01-01-2019", item2got.getExpirationDate());
    ASSERT_TRUE(item2got.isBad(fridge.getCurrentDate()));

    ASSERT_EQ(42, fridge.free());
    ASSERT_EQ(fridge.numOfExpired(),0);
    fridge.advanceDay();
    ASSERT_EQ(fridge.numOfExpired(),1);

    auto item1got = fridge.get("foo");
    ASSERT_EQ("foo", item1got.getName());
    ASSERT_EQ("01-01-2020", item1got.getExpirationDate());
    ASSERT_TRUE(item1got.isBad(fridge.getCurrentDate()));

    ASSERT_EQ(45, fridge.free());
    fridge.inventory();
    ASSERT_EQ(fridge.getCurrentDate().getDate(),"03-01-2020");

}


