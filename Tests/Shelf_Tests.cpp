#include "../gtest/gtest.h"

#include "../Headers/Shelf.h"

using namespace ::testing;


TEST(Shelf,Constructor)
{
    auto shelf = Shelf(25,0);
    auto tempItem = shelf.get("foo");
    ASSERT_EQ(tempItem.getName(),"");
    ASSERT_EQ(tempItem.getExpirationDate(),"");
    ASSERT_EQ(shelf.sortedByExpiry(),std::vector<Item *>());
    auto tempItem2 = "foo";
    ASSERT_EQ(shelf.getSmallest(tempItem2),nullptr);
    ASSERT_EQ(shelf.getFreeSpace(),25);
    ASSERT_EQ(shelf.getNumber(),0);
    ASSERT_EQ(shelf.getContents().size(), 0);
}
TEST(Shelf,Store_Item)
{
    auto shelf = Shelf(25,42);
    auto item1 = Item("foobar","01-01-2000");
    auto ref = &item1;
    shelf.store(std::move(item1));
    ASSERT_EQ(shelf.getFreeSpace(),19);
    ASSERT_EQ(shelf.sortedByExpiry().size(),1);

}
TEST(Shelf,Store_Multiple_Items)
{
    auto shelf = Shelf(25,42);
    auto item1 = Item("foobar","01-01-2000");
    ASSERT_TRUE(shelf.store(std::move(item1)));
    ASSERT_EQ(shelf.getFreeSpace(),19);
    ASSERT_EQ(shelf.sortedByExpiry().size(),1);
    auto item2 = Item("foo","01-02-2000");
    ASSERT_TRUE(shelf.store(std::move(item2)));
    auto item3 = Item("bar","01-02-2000");
    ASSERT_TRUE(shelf.store(std::move(item3)));
    ASSERT_EQ(shelf.getFreeSpace(),13);
    ASSERT_EQ(shelf.sortedByExpiry().size(),3);
    auto item4 = Item("This is a very big item","01-02-2000");
    ASSERT_FALSE(shelf.store(std::move(item4)));
    ASSERT_EQ(shelf.getFreeSpace(),13);
    ASSERT_EQ(shelf.sortedByExpiry().size(),3);
}
TEST(Shelf,Store_Get_Item)
{
    auto shelf = Shelf(12,9001);
    auto item1 = Item("foobar","01-01-2000");
    ASSERT_TRUE(shelf.store(std::move(item1)));
    ASSERT_EQ(shelf.getFreeSpace(),6);
    ASSERT_EQ(shelf.sortedByExpiry().size(),1);
    auto gotItem = shelf.get("foobar");
    ASSERT_EQ(gotItem.getExpirationDate(), "01-01-2000");
    ASSERT_EQ(gotItem.getName(),"foobar");

    ASSERT_EQ(shelf.getFreeSpace(),12);
    ASSERT_EQ(shelf.sortedByExpiry().size(),0);
}
TEST(Shelf,Store_Get_Multiple_Items)
{
    auto shelf = Shelf(21,3);
    auto item1 = Item("foobar","01-02-2003");
    auto item2 = Item("foobar","01-01-2003");
    auto item3 = Item("apple","02-01-2003");
    ASSERT_TRUE(shelf.store(std::move(item1)));
    ASSERT_TRUE(shelf.store(std::move(item2)));
    ASSERT_TRUE(shelf.store(std::move(item3)));
    ASSERT_EQ(shelf.getFreeSpace(),4);
    ASSERT_EQ(shelf.sortedByExpiry().size(),3);

    auto item1got = shelf.get("foobar");
    ASSERT_EQ(item1got.getName(), "foobar");
    ASSERT_EQ(item1got.getExpirationDate(),"01-01-2003");

    ASSERT_EQ(shelf.getFreeSpace(),10);
    ASSERT_EQ(shelf.sortedByExpiry().size(),2);

    auto item2got = shelf.get("foobar");
    ASSERT_EQ(item2got.getName(), "foobar");
    ASSERT_EQ(item2got.getExpirationDate(),"01-02-2003");

    ASSERT_EQ(shelf.getFreeSpace(),16);
    ASSERT_EQ(shelf.sortedByExpiry().size(),1);

    auto itemgot = shelf.get("foobar");
    ASSERT_EQ(itemgot.getName(), "");
    ASSERT_EQ(itemgot.getExpirationDate(),"");

    ASSERT_EQ(shelf.getFreeSpace(),16);
    ASSERT_EQ(shelf.sortedByExpiry().size(),1);

    auto item3got = shelf.get("apple");
    ASSERT_EQ(item3got.getName(), "apple");
    ASSERT_EQ(item3got.getExpirationDate(),"02-01-2003");

    ASSERT_EQ(shelf.getFreeSpace(),21);
    ASSERT_EQ(shelf.sortedByExpiry().size(),0);

}

