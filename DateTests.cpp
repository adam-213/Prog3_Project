#include "gtest/gtest.h"

#include "Date.h"

using namespace ::testing;



TEST(Date, PutDate1)
{
    Date date{};
    ASSERT_TRUE(date.putDate(1,1,1970));
    ASSERT_EQ("01-01-1970",date.getDate());
    Date date2{};
    std::string d2 = "01-01-1970";
    ASSERT_TRUE(date2.putDate(d2));
    ASSERT_TRUE(date2 == date);
}

TEST(Date,PutDate2_Incorrect_dates)
{
    Date date{};
    std::string d1 = "21-13-2021";
    std::string d2 = "30-2-1994";
    ASSERT_FALSE(date.putDate(d1));
    ASSERT_FALSE(date.putDate(29,2,2001));
    ASSERT_FALSE(date.putDate(0,12,2000));
    ASSERT_FALSE(date.putDate(12,-2,1111));
    ASSERT_FALSE(date.putDate(d2));
}

TEST(Date,PutDate3_Operators)
{
    Date date{};
    Date date2{};
    auto d2 = "13-11-2004";
    ASSERT_TRUE(date.putDate(13,11,2000));
    ASSERT_TRUE(date2.putDate(d2));
    ASSERT_TRUE(date.getDay() == date2.getDay());
    ASSERT_FALSE(date > date2);
    ASSERT_TRUE(date < date2);
    ASSERT_TRUE(date != date2);
}

TEST(Date,Constructors)
{
    Date date(1,1,1970);
    std::string dt2 = "1-1-1970";
    Date date2(dt2);
    Date date3;
    date3.putDate(1,1,1970);
    ASSERT_TRUE(date == date2);
    ASSERT_TRUE(date2 == date3);
}
