#include "../gtest/gtest.h"

#include "../Headers/Date.h"

using namespace ::testing;

TEST(Date_isLeap,Normal_Leap_Year){ASSERT_TRUE(Date::isLeap(2000));};
TEST(Date_isLeap,Older_Leap_Year){ASSERT_TRUE(Date::isLeap(1600));};
TEST(Date_isLeap,Last_Leap_Year){ASSERT_TRUE(Date::isLeap(2020));};
TEST(Date_isLeap,End_of_the_world_Year){ASSERT_TRUE(Date::isLeap(2012));};
TEST(Date_isLeap,Random_Leap_Year){ASSERT_TRUE(Date::isLeap(1324));};
TEST(Date_isLeap,Random_Leap_Year_2){ASSERT_TRUE(Date::isLeap(1992));};
TEST(Date_isLeap,Negative_Leap_Year){ASSERT_TRUE(Date::isLeap(-2000));};
TEST(Date_isLeap,Negative_Leap_Year_2){ASSERT_TRUE(Date::isLeap(-444));};
TEST(Date_isLeap,Zero){ASSERT_TRUE(Date::isLeap(0));};

TEST(Date_isLeap,Normal_NonLeap_Year){ASSERT_FALSE(Date::isLeap(2019));}
TEST(Date_isLeap,Older_NonLeap_Year){ASSERT_FALSE(Date::isLeap(1922));}
TEST(Date_isLeap,Current_NonLeap_Year){ASSERT_FALSE(Date::isLeap(2021));}
TEST(Date_isLeap,We_Survived_the_End_NonLeap_Year){ASSERT_FALSE(Date::isLeap(2013));};
TEST(Date_isLeap,Random_NonLeap_Year){ASSERT_FALSE(Date::isLeap(2173));}
TEST(Date_isLeap,Random_NonLeap_Year_2){ASSERT_FALSE(Date::isLeap(213));}
TEST(Date_isLeap,We_Are_Number_One_NonLeap_Year){ASSERT_FALSE(Date::isLeap(1111));}
TEST(Date_isLeap,Negative_NonLeap_Year){ASSERT_FALSE(Date::isLeap(-1));}
TEST(Date_isLeap,Negative_NonLeap_Year_2){ASSERT_FALSE(Date::isLeap(-2021));}



TEST(Date_toDay,Normal_Date){ASSERT_EQ(21, Date::toDay(21, 1, 2000));}
TEST(Date_toDay,Normal_Date_2){ASSERT_EQ(31, Date::toDay(31, 1, 2000));}
TEST(Date_toDay,February_Normal){ASSERT_EQ(57, Date::toDay(26, 2, 2000));}
TEST(Date_toDay,February_Leap){ASSERT_EQ(60, Date::toDay(29, 2, 2000));}
TEST(Date_toDay,February_29_Not_Leap){ASSERT_EQ(60, Date::toDay(29, 2, 2001));}
TEST(Date_toDay,December_Non_Leap){ASSERT_EQ(350, Date::toDay(16, 12, 2021));}
TEST(Date_toDay,December_Leap){ASSERT_EQ(351, Date::toDay(16, 12, 2020));}
TEST(Date_toDay,Random_Date){ASSERT_EQ(147, Date::toDay(27, 5, 1999));}

TEST(Date_toDay,Negative_Year){ASSERT_EQ(21, Date::toDay(21, 1, -2000));} // Works as expected
TEST(Date_toDay,Negative_Day){ASSERT_EQ(21, Date::toDay(-21, 1, 2000));} //Assuming a typo and correcting it to the same date but positive
TEST(Date_toDay,Negative_January){ASSERT_EQ(21, Date::toDay(21, -1, 2000));} //^^
TEST(Date_toDay,Negative_Month){ASSERT_EQ(148, Date::toDay(27, -5, 2000));}  //^^



TEST(Date_fromDay,Normal_Date){ASSERT_EQ("21-01-2001", Date::fromDay(21, 2001));}
TEST(Date_fromDay,B4_Leap_Date){ASSERT_EQ("25-02-2004", Date::fromDay(56, 2004));}
TEST(Date_fromDay,Leap_Date){ASSERT_EQ("29-02-1608", Date::fromDay(60, 1608));}
TEST(Date_fromDay,After_Leap_Date){ASSERT_EQ("01-03-1976", Date::fromDay(61, 1976));}
TEST(Date_fromDay,December_Date_NonLeap){ASSERT_EQ("16-12-2021", Date::fromDay(350, 2021));}
TEST(Date_fromDay,December_Date_Leap){ASSERT_EQ("15-12-2020", Date::fromDay(350, 2020));}
TEST(Date_fromDay,Random_Date){ASSERT_EQ("19-08-1273", Date::fromDay(231, 1273));}

TEST(Date_fromDay,Negative_Days){ASSERT_EQ("19-08-1273", Date::fromDay(-231, 1273));}
TEST(Date_fromDay,Negative_Year){ASSERT_EQ("19-08-1273", Date::fromDay(231, -1273));}
TEST(Date_fromDay,Year_0){ASSERT_EQ("18-08-0000", Date::fromDay(231, 0));}
TEST(Date_fromDay,Day_0){ASSERT_EQ("", Date::fromDay(0, 1273));}


