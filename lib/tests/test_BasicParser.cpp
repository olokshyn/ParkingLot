//
// Created by oleg on 9/20/18.
//

#include <string>
#include <sstream>
#include <algorithm>
#include <stdexcept>

#include "gtest/gtest.h"

#include "parsers/BasicParser.hpp"

using namespace lib;

namespace
{

void check_case(const std::string& input,
                const std::vector<std::pair<date_time::date_time_t, int>>& result)
{
    std::stringstream stream(input);
    parsers::BasicParser parser;
    auto cd = parser.parse(stream);
    ASSERT_EQ(result.size(), cd.size());
    EXPECT_TRUE(std::equal(cd.begin(), cd.end(), result.begin(),
                           [](const auto& left, const auto& right) -> bool
                           {
                               using date_time::operator==;
                               return left.first == right.first
                                      && left.second == right.second;
                           }));
}

}

TEST(BasicParser, ZeroLines)
{
    check_case(
            "",
            {});
}

TEST(BasicParser, OneLine)
{
    check_case(
            "12:01 13:17",
            {
                    {date_time::from_time(12, 1), 1},
                    {date_time::from_time(13, 17), -1}
            });
}

TEST(BasicParser, TwoLines)
{
    check_case(
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
    check_case(
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
    check_case(
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
    check_case(
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
