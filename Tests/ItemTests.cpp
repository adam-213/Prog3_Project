#include <iostream>
#include "../gtest/gtest.h"

#include "../Headers/Item.h"

using namespace ::testing;

TEST(Item,Constructor1)
{
    Item item1;
    ASSERT_EQ("",item1.getName());
    ASSERT_EQ("",item1.getExpirationDate());
    ASSERT_FALSE(item1.isBad());
    ASSERT_EQ(-1,item1.goodDays());

    item1.put("foo","01-01-1970");
    ASSERT_EQ("foo",item1.getName());
    ASSERT_EQ("01-01-1970",item1.getExpirationDate());
    ASSERT_FALSE(item1.isBad());
    ASSERT_EQ(0,item1.goodDays());
}

TEST(Item,Constructor2)
{
    Item item2("toy truck");
    ASSERT_EQ("toy truck", item2.getName());
    ASSERT_EQ("",item2.getExpirationDate());
    ASSERT_FALSE(item2.isBad());
    ASSERT_EQ(-1,item2.goodDays());
}

TEST(Item,Constructor3)
{
    std::string dateItem3 = "17-12-2000";
    Item item3("apple",dateItem3);
    ASSERT_EQ("apple",item3.getName());
    ASSERT_EQ("17-12-2000",item3.getExpirationDate());
    ASSERT_FALSE(item3.isBad());
    ASSERT_EQ(11308,item3.goodDays());

    item3.put("foo","01-01-1969");
    ASSERT_EQ("foo",item3.getName());
    ASSERT_EQ("01-01-1969",item3.getExpirationDate());
    ASSERT_TRUE(item3.isBad());
    ASSERT_EQ(-365,item3.goodDays());
}

TEST(Item,Constructor4)
{
    Date dateItem4(12,12,2021);
    Item item4("eggs",dateItem4);
    ASSERT_EQ("eggs",item4.getName());
    ASSERT_EQ("12-12-2021",item4.getExpirationDate());
    ASSERT_FALSE(item4.isBad());
    ASSERT_EQ(18973,item4.goodDays());
}
 //I'm not sure how to change global variables inside the tests - methods isBad, goodDays etc grab global variable current_date which has to be const