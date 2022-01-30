#include "../gtest/gtest.h"

#include "../Headers/Date.h"

using namespace ::testing;


TEST(Date, PutDate1)
{
    Date date{};
    ASSERT_TRUE(date.putDate(1, 1, 1970));
    ASSERT_EQ("01-01-1970", date.getDate());
    Date date2{};
    std::string d2 = "01-01-1970";
    ASSERT_TRUE(date2.putDate(d2));
    ASSERT_TRUE(date2 == date);
}

TEST(Date, PutDate2_Incorrect_dates)
{
    Date date{};
    std::string d1 = "21-13-2021";
    std::string d2 = "30-2-1994";
    ASSERT_FALSE(date.putDate(d1));
    ASSERT_FALSE(date.putDate(29, 2, 2001));
    ASSERT_FALSE(date.putDate(0, 12, 2000));
    ASSERT_FALSE(date.putDate(12, 0, 28));
    ASSERT_FALSE(date.putDate(d2));
}

TEST(Date, Operators)
{
    Date date{};
    Date date2{};
    auto d2 = "13-11-2004";
    ASSERT_TRUE(date.putDate(13, 11, 2000));
    ASSERT_TRUE(date2.putDate(d2));
    ASSERT_TRUE(date.getDay() == date2.getDay());
    ASSERT_FALSE(date > date2);
    ASSERT_TRUE(date < date2);
    ASSERT_TRUE(date != date2);
}

TEST(Date, Operators2)
{
    Date date(29, 1, 2000);
    Date date2;
    date2.putDate("1-3-2000");
    Date date3;
    date3.putDate(date2.getDate());
    ASSERT_TRUE(date < date2);
    ASSERT_TRUE(date2 == date3);
    ASSERT_TRUE(date3 != date);
    ASSERT_FALSE(date == date3);
    ASSERT_FALSE(date >= date2);
    ASSERT_FALSE(date3 <= date);
    ASSERT_TRUE(date2 <= date3);
}

TEST(Date, Odd_Dates_Operators)
{
    Date date1(1, 1, 0);
    Date date2(31, 12, -1);
    Date date3(27, 8, 1919);
    ASSERT_TRUE(date1 != date2);
    ASSERT_TRUE(date2 != date3);
    ASSERT_TRUE(date3 != date1);
    ASSERT_TRUE(date1 >= date2);
    ASSERT_TRUE(date1 <= date3);
    ASSERT_TRUE(date3 > date2);
    ASSERT_FALSE(date1 == date2);
}

TEST(Date, Constructors)
{
    Date date(1, 1, 1970);
    std::string dt2 = "1-1-1970";
    Date date2(dt2);
    Date date3;
    date3.putDate(1, 1, 1970);
    ASSERT_TRUE(date == date2);
    ASSERT_TRUE(date2 == date3);
}

TEST(Date, Negative_Date)
{
    //Day and month are assumed to be typos if they are != 0 and corrected accordingly
    Date negday(-1, 1, 1970);
    Date date(1, 1, 1970);
    ASSERT_TRUE(date == negday);
    Date negmon(1, -3, 1970);
    Date date2(1, 3, 1970);
    ASSERT_TRUE(date2 == negmon);
}

TEST(Date, Addition)
{
    Date d1(3, 4, 2000);
    d1 + 10;
    ASSERT_EQ(d1.getDate(), "13-04-2000");
    d1 + 100;
    ASSERT_EQ(d1.getDate(), "22-07-2000");
    d1 + 150;
    ASSERT_EQ(d1.getDate(), "19-12-2000");
    d1 + 20;
    ASSERT_EQ(d1.getDate(), "08-01-2001");
    d1 + 99;
    ASSERT_EQ(d1.getDate(), "17-04-2001");
    d1 + 420;
    ASSERT_EQ(d1.getDate(), "11-06-2002");
    d1 + 999;
    ASSERT_EQ(d1.getDate(), "06-03-2005");
}

TEST(Date, Substraction)
{
    Date d1(3, 4, 2000);
    d1 - 10;
    ASSERT_EQ(d1.getDate(), "24-03-2000");
    d1 - 100;
    ASSERT_EQ(d1.getDate(), "15-12-1999");
    d1 - 150;
    ASSERT_EQ(d1.getDate(), "18-07-1999");
    d1 - 20;
    ASSERT_EQ(d1.getDate(), "28-06-1999");
    d1 - 99;
    ASSERT_EQ(d1.getDate(), "21-03-1999");
    d1 - 420;
    ASSERT_EQ(d1.getDate(), "25-01-1998");
    d1 - 999;
    ASSERT_EQ(d1.getDate(), "02-05-1995");
}