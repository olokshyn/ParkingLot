//
// Created by oleg on 9/19/18.
//

#include <string>
#include <sstream>
#include <stdexcept>

#include "gtest/gtest.h"

#include "Common.hpp"
#include "DateTime.hpp"

using namespace lib;
using namespace lib::date_time;

TEST(DateTime, ConstructionTime)
{
    auto time_point = from_time(0, 0, 0);
    EXPECT_EQ(0, hour(time_point));
    EXPECT_EQ(0, min(time_point));
    EXPECT_EQ(0, sec(time_point));

    time_point = from_time(11, 55, 3);
    EXPECT_EQ(11, hour(time_point));
    EXPECT_EQ(55, min(time_point));
    EXPECT_EQ(3, sec(time_point));
}

TEST(DateTime, ConstructionDateTime)
{
    auto time_point = from_date_time(0, 0, 0, 0, 0, 0);
    EXPECT_EQ(0, year(time_point));
    EXPECT_EQ(0, month(time_point));
    EXPECT_EQ(0, day(time_point));
    EXPECT_EQ(0, hour(time_point));
    EXPECT_EQ(0, min(time_point));
    EXPECT_EQ(0, sec(time_point));

    time_point = from_date_time(1998, 7, 4, 13, 55);
    EXPECT_EQ(1998, year(time_point));
    EXPECT_EQ(7, month(time_point));
    EXPECT_EQ(4, day(time_point));
    EXPECT_EQ(13, hour(time_point));
    EXPECT_EQ(55, min(time_point));
    EXPECT_EQ(0, sec(time_point));
}

TEST(DateTime, Parse)
{
    auto time_point = from("13:25", g_time_format);
    EXPECT_TRUE(from_time(13, 25) == time_point);

    time_point = from("2016-05-01 06:36:00");
    EXPECT_TRUE(from_date_time(2016, 5, 1, 6, 36) == time_point);

    time_point = from("2016-05-01T06:36:00", g_date_time_format);
    EXPECT_TRUE(from_date_time(2016, 5, 1, 6, 36) == time_point);
}

TEST(DateTime, ParseInvalidFormat)
{
    EXPECT_THROW(from("", g_time_format), std::runtime_error);
    EXPECT_THROW(from("1:25", g_time_format), std::runtime_error);
    EXPECT_THROW(from("13:", g_time_format), std::runtime_error);
    EXPECT_THROW(from("24:00", g_time_format), std::runtime_error);
    EXPECT_THROW(from("abc:def", g_time_format), std::runtime_error);

    EXPECT_THROW(from("", g_date_time_format), std::runtime_error);
    EXPECT_THROW(from("2013-11", g_time_format), std::runtime_error);
    EXPECT_THROW(from("2018-12-01T03:22:00", g_time_format), std::runtime_error);
    EXPECT_THROW(from("some-string-stuff", g_time_format), std::runtime_error);
}

TEST(DateTime, ToString)
{
    EXPECT_EQ("1995-10-28 02:55:03",
              to_string(from_date_time(1995, 10, 28, 2, 55, 03)));
    EXPECT_EQ("2015-11-13T06:18:23",
              to_string(from_date_time(2015, 11, 13, 6, 18, 23),
                        g_date_time_format));
}

TEST(DateTime, CompareEqual)
{
    EXPECT_TRUE(from_time(0, 0) == from_time(0, 0));
    EXPECT_FALSE(from_time(0, 0) == from_time(23, 59));

    EXPECT_TRUE(from_date_time(1972, 6, 30, 15, 45)
                == from_date_time(1972, 6, 30, 15, 45));
    EXPECT_FALSE(from_date_time(2002, 2, 23, 10, 15)
                 == from_date_time(1972, 6, 30, 15, 45));
}

TEST(DateTime, CompareLess)
{
    EXPECT_TRUE(from_time(9, 23) < from_time(10, 15));
    EXPECT_FALSE(from_time(9, 23) < from_time(9, 23));
    EXPECT_TRUE(from_time(9, 23) <= from_time(9, 23));
    EXPECT_FALSE(from_time(11, 59) < from_time(10, 15));

    EXPECT_TRUE(from_date_time(2008, 6, 11, 9, 23)
                < from_date_time(2008, 6, 12, 9, 23));
    EXPECT_FALSE(from_date_time(2008, 6, 11, 9, 23)
                 < from_date_time(2008, 6, 11, 9, 23));
    EXPECT_TRUE(from_date_time(2008, 6, 11, 9, 23)
                <= from_date_time(2008, 6, 11, 9, 23));
    EXPECT_FALSE(from_date_time(2008, 6, 11, 9, 23)
                 < from_date_time(2008, 5, 11, 9, 23));
}

TEST(DateTime, CompareGreater)
{
    EXPECT_TRUE(from_time(23, 59) > from_time(14, 44));
    EXPECT_FALSE(from_time(0, 0) > from_time(0, 0));
    EXPECT_TRUE(from_time(0, 0) >= from_time(0, 0));
    EXPECT_FALSE(from_time(0, 0) > from_time(23, 59));

    EXPECT_TRUE(from_date_time(2020, 11, 31, 8, 50)
                > from_date_time(2019, 11, 31, 8, 50));
    EXPECT_FALSE(from_date_time(2020, 11, 31, 8, 50)
                 > from_date_time(2020, 11, 31, 8, 50));
    EXPECT_TRUE(from_date_time(2020, 11, 31, 8, 50)
                >= from_date_time(2020, 11, 31, 8, 50));
    EXPECT_FALSE(from_date_time(2010, 10, 30, 8, 50)
                 > from_date_time(2010, 11, 31, 8, 50));
}
