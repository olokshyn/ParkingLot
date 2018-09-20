//
// Created by oleg on 9/20/18.
//

#include <string>
#include <sstream>
#include <stdexcept>

#include "gtest/gtest.h"

#include "parsers/BasicParser.hpp"
#include "TestsUtils.hpp"

using namespace lib;

#define CHECK_CASE check_case<parsers::BasicParser>

TEST(BasicParser, ZeroLines)
{
    CHECK_CASE(
            "",
            {});
}

TEST(BasicParser, OneLine)
{
    CHECK_CASE(
            "12:01 13:17",
            {
                    {date_time::from_time(12, 1), 1},
                    {date_time::from_time(13, 17), -1}
            });
}

TEST(BasicParser, TwoLines)
{
    CHECK_CASE(
            "12:01 13:17\n"
            "03:04 11:56",
            {
                    {date_time::from_time(3, 4), 1},
                    {date_time::from_time(11, 56), -1},
                    {date_time::from_time(12, 1), 1},
                    {date_time::from_time(13, 17), -1}
            });
}

TEST(BasicParser, ThreeLines)
{
    CHECK_CASE(
            "20:23 21:40\n"
            "18:35 19:02\n"
            "18:00 18:40\n",
            {
                    {date_time::from_time(18, 0), 1},
                    {date_time::from_time(18, 35), 1},
                    {date_time::from_time(18, 40), -1},
                    {date_time::from_time(19, 2), -1},
                    {date_time::from_time(20, 23), 1},
                    {date_time::from_time(21, 40), -1}
            });
}

TEST(BasicParser, InterleavingRanges)
{
    CHECK_CASE(
            "01:20 22:30\n"
            "05:30 18:00\n"
            "08:00 18:00\n"
            "09:05 19:30\n"
            "08:00 19:30\n"
            "08:00 18:00",
            {
                    {date_time::from_time(1, 20), 1},
                    {date_time::from_time(5, 30), 1},
                    {date_time::from_time(8, 0), 3},
                    {date_time::from_time(9, 5), 1},
                    {date_time::from_time(18, 0), -3},
                    {date_time::from_time(19, 30), -2},
                    {date_time::from_time(22, 30), -1}
            });
}

TEST(BasicParser, EmptyTimeRange)
{
    CHECK_CASE(
            "05:45 05:45\n"
            "05:45 05:45",
            {
                    {date_time::from_time(5, 45), 0}
            });
}

TEST(BasicParser, InvalidTimeRange)
{
    std::stringstream stream("20:23 21:40\n"
                             "18:35 17:02\n"
                             "18:00 18:40\n");
    parsers::BasicParser parser;
    EXPECT_THROW(parser.parse(stream), std::runtime_error);
}

TEST(BasicParser, InvalidFormat)
{
    std::stringstream stream("20:23 21:40\n"
                             "18:35\n"
                             "18:00 18:40\n");
    parsers::BasicParser parser;
    EXPECT_THROW(parser.parse(stream), std::runtime_error);
}
