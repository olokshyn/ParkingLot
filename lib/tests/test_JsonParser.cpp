//
// Created by oleg on 9/20/18.
//

#include "gtest/gtest.h"

#include "parsers/JsonParser.hpp"
#include "TestsUtils.hpp"

using namespace lib;

#define CHECK_CASE check_case<parsers::JsonParser>

TEST(JsonParser, ZeroEntries)
{
    CHECK_CASE(
            "[]",
            {});
}

TEST(JsonParser, OneEntry)
{
    CHECK_CASE(
            "["
            "{\n"
            "\"Id\": 0,\n"
            "\"ArrivalTime\": \"2016-05-01T06:36:00\",\n"
            "\"LeaveTime\": \"2016-05-01T13:28:00\"\n"
            "}"
            "]",
            {
                    {date_time::from_date_time(2016, 5, 1, 6, 36), 1},
                    {date_time::from_date_time(2016, 5, 1, 13, 28), -1}
            });
}

TEST(JsonParser, TwoEntries)
{
    CHECK_CASE(
            "["
            "{\n"
            "\"Id\": 0,\n"
            "\"ArrivalTime\": \"2015-05-02T05:15:00\",\n"
            "\"LeaveTime\": \"2015-05-03T18:42:00\"\n"
            "},\n"
            "{\n"
            "\"Id\": 1,\n"
            "\"ArrivalTime\": \"2015-05-02T12:17:00\",\n"
            "\"LeaveTime\": \"2015-05-03T19:00:00\"\n"
            "}"
            "]",
            {
                    {date_time::from_date_time(2015, 5, 2, 5, 15), 1},
                    {date_time::from_date_time(2015, 5, 2, 12, 17), 1},
                    {date_time::from_date_time(2015, 5, 3, 18, 42), -1},
                    {date_time::from_date_time(2015, 5, 3, 19, 00), -1}
            });
}

TEST(JsonParser, ThreeEntries)
{
    CHECK_CASE(
            "["
            "{\n"
            "\"Id\": 0,\n"
            "\"ArrivalTime\": \"2016-05-01T06:36:00\",\n"
            "\"LeaveTime\": \"2016-05-01T13:28:00\"\n"
            "},\n"
            "{\n"
            "\"Id\": 1,\n"
            "\"ArrivalTime\": \"2016-05-01T14:17:00\",\n"
            "\"LeaveTime\": \"2016-05-02T01:35:00\"\n"
            "},\n"
            "{\n"
            "\"Id\": 2,\n"
            "\"ArrivalTime\": \"2016-05-04T00:15:00\",\n"
            "\"LeaveTime\": \"2016-05-04T06:55:00\"\n"
            "}"
            "]",
            {
                    {date_time::from_date_time(2016, 5, 1, 6, 36), 1},
                    {date_time::from_date_time(2016, 5, 1, 13, 28), -1},
                    {date_time::from_date_time(2016, 5, 1, 14, 17), 1},
                    {date_time::from_date_time(2016, 5, 2, 1, 35), -1},
                    {date_time::from_date_time(2016, 5, 4, 0, 15), 1},
                    {date_time::from_date_time(2016, 5, 4, 6, 55), -1}
            });
}

TEST(JsonParser, InterleavingRanges)
{
    CHECK_CASE(
            "["
            "{\n"
            "\"Id\": 0,\n"
            "\"ArrivalTime\": \"2016-05-01T06:36:00\",\n"
            "\"LeaveTime\": \"2016-05-01T13:28:00\"\n"
            "},\n"
            "{\n"
            "\"Id\": 1,\n"
            "\"ArrivalTime\": \"2016-05-01T05:17:00\",\n"
            "\"LeaveTime\": \"2016-05-01T13:28:00\"\n"
            "},\n"
            "{\n"
            "\"Id\": 2,\n"
            "\"ArrivalTime\": \"2016-05-01T06:36:00\",\n"
            "\"LeaveTime\": \"2016-05-01T15:20:00\"\n"
            "},\n"
            "{\n"
            "\"Id\": 3,\n"
            "\"ArrivalTime\": \"2016-05-01T06:36:00\",\n"
            "\"LeaveTime\": \"2016-05-02T15:20:00\"\n"
            "}"
            "]",
            {
                    {date_time::from_date_time(2016, 5, 1, 5, 17), 1},
                    {date_time::from_date_time(2016, 5, 1, 6, 36), 3},
                    {date_time::from_date_time(2016, 5, 1, 13, 28), -2},
                    {date_time::from_date_time(2016, 5, 1, 15, 20), -1},
                    {date_time::from_date_time(2016, 5, 2, 15, 20), -1},
            });
}

TEST(JsonParser, EmptyTimeRange)
{
    CHECK_CASE(
            "["
            "{\n"
            "\"Id\": 0,\n"
            "\"ArrivalTime\": \"2016-05-01T06:36:00\",\n"
            "\"LeaveTime\": \"2016-05-01T06:36:00\"\n"
            "}"
            "]",
            {
                    {date_time::from_date_time(2016, 5, 1, 6, 36), 0}
            });
}

TEST(JsonParser, InvalidTimeRange)
{
    std::stringstream stream("["
                             "{\n"
                             "\"Id\": 0,\n"
                             "\"ArrivalTime\": \"2016-05-01T06:36:00\",\n"
                             "\"LeaveTime\": \"2016-05-01T06:35:00\"\n"
                             "}"
                             "]");
    parsers::JsonParser parser;
    EXPECT_THROW(parser.parse(stream), std::runtime_error);
}

TEST(JsonParser, InvalidFormat)
{
    parsers::JsonParser parser;

    std::stringstream stream("["
                             "{\n"
                             "\"Id\": 0,\n"
                             "\"LeaveTime\": \"2016-05-01T06:35:00\"\n"
                             "}"
                             "]");
    EXPECT_THROW(parser.parse(stream), std::runtime_error);

    stream.str("["
               "{\n"
               "\"Id\": 0,\n"
               "\"ArrivalTime\": \"2016-05-01T06:36:00\"\n"
               "}"
               "]");
    stream.clear();
    EXPECT_THROW(parser.parse(stream), std::runtime_error);

    stream.str("["
               "{\n"
               "\"Id\": 0,\n"
               "\"ArrivalTime\": \"01T06:36:00\",\n"
               "\"LeaveTime\": \"2016-05-01T06:35:00\"\n"
               "}"
               "]");
    stream.clear();
    EXPECT_THROW(parser.parse(stream), std::runtime_error);
}
