//
// Created by oleg on 9/20/18.
//

#include <sstream>

#include "gtest/gtest.h"

#include "CarsDensity.hpp"
#include "parsers/BasicParser.hpp"
#include "parsers/JsonParser.hpp"

using namespace lib;

TEST(Integrational, BasicParser)
{
    using date_time::from_time;
    using date_time::operator==;

    std::stringstream stream("12:01 13:17\n"
                             "03:04 11:56\n"
                             "05:18 12:40\n");
    parsers::BasicParser parser;
    auto cars_density = parser.parse(stream);
    auto busiest_time = find_first_busiest_time(cars_density);
    EXPECT_TRUE(from_time(5, 18) == busiest_time.first);
    EXPECT_TRUE(from_time(11, 56) == busiest_time.second);
}

TEST(Integrational, JsonParser)
{
    using date_time::from_date_time;
    using date_time::operator==;

    std::stringstream stream("["
                             "{\n"
                             "\"Id\": 0,\n"
                             "\"ArrivalTime\": \"2016-05-01T06:36:00\",\n"
                             "\"LeaveTime\": \"2016-05-01T13:28:00\"\n"
                             "}, {\n"
                             "\"Id\": 1,\n"
                             "\"ArrivalTime\": \"2016-05-01T14:17:00\",\n"
                             "\"LeaveTime\": \"2016-05-02T01:35:00\"\n"
                             "},\n"
                             "{\n"
                             "\"Id\": 2,\n"
                             "\"ArrivalTime\": \"2016-05-04T00:15:00\",\n"
                             "\"LeaveTime\": \"2016-05-04T06:55:00\"\n"
                             "},\n"
                             "{\n"
                             "\"Id\": 3,\n"
                             "\"ArrivalTime\": \"2016-04-30T18:15:00\",\n"
                             "\"LeaveTime\": \"2016-05-02T01:35:00\"\n"
                             "}"
                             "]");
    parsers::JsonParser parser;
    auto cars_denity = parser.parse(stream);
    auto busiest_time = find_first_busiest_time(cars_denity);
    EXPECT_TRUE(from_date_time(2016, 5, 1, 6, 36) == busiest_time.first);
    EXPECT_TRUE(from_date_time(2016, 5, 1, 13, 28) == busiest_time.second);
}
