//
// Created by oleg on 9/20/18.
//

#include "gtest/gtest.h"

#include "CarsDensity.hpp"
#include "parsers/ParsersUtils.hpp"

using namespace lib;

namespace
{

cars_density_t fill_cars_density(const std::vector<date_time_pair_t>& ranges)
{
    auto cars_density = build_cars_density();
    for (const auto& [time_start, time_end] : ranges)
    {
        parsers::process_parking_range(time_start, time_end, cars_density);
    }
    return cars_density;
}

}

TEST(CarsDensity, Build)
{
    using date_time::operator==;

    auto cars_density = build_cars_density();
    EXPECT_TRUE(cars_density.empty());

    cars_density[date_time::from_time(12, 35)] = -1;
    cars_density[date_time::from_time(10, 15)] = 1;

    auto iter = cars_density.begin();
    EXPECT_TRUE(date_time::from_time(10, 15) == iter++->first);
    EXPECT_TRUE(date_time::from_time(12, 35) == iter++->first);
    EXPECT_EQ(cars_density.end(), iter);
}

TEST(CarsDensity, build_cars_cumulative_0)
{
    auto cars_density = fill_cars_density(
            {

            });
    EXPECT_THROW(build_cars_cumulative(cars_density), std::runtime_error);
}

TEST(CarsDensity, build_cars_cumulative_1)
{
    using date_time::from_time;

    auto cars_density = fill_cars_density(
            {
                    {from_time(10, 15), from_time(12, 15)}
            });
    EXPECT_EQ(std::vector<int>({1, 0}), build_cars_cumulative(cars_density));
}

TEST(CarsDensity, build_cars_cumulative_1_the_same)
{
    using date_time::from_time;

    auto cars_density = fill_cars_density(
            {
                    {from_time(10, 15), from_time(12, 15)},
                    {from_time(10, 15), from_time(12, 15)},
                    {from_time(10, 15), from_time(12, 15)},
                    {from_time(13, 15), from_time(13, 15)},
                    {from_time(13, 15), from_time(13, 15)},
                    {from_time(13, 15), from_time(13, 15)}
            });
    EXPECT_EQ(std::vector<int>({3, 0, 0}), build_cars_cumulative(cars_density));
}


TEST(CarsDensity, build_cars_cumulative_2_interleaved)
{
    using date_time::from_time;

    auto cars_density = fill_cars_density(
            {
                    {from_time(10, 15), from_time(12, 15)},
                    {from_time(11, 20), from_time(13, 35)}
            });
    EXPECT_EQ(std::vector<int>({1, 2, 1, 0}), build_cars_cumulative(cars_density));
}

TEST(CarsDensity, build_cars_cumulative_2_intersected)
{
    using date_time::from_time;

    auto cars_density = fill_cars_density(
            {
                    {from_time(10, 15), from_time(12, 15)},
                    {from_time(12, 15), from_time(13, 35)}
            });
    EXPECT_EQ(std::vector<int>({1, 1, 0}), build_cars_cumulative(cars_density));
}

TEST(CarsDensity, build_cars_cumulative_2_intersected_2)
{
    using date_time::from_time;

    auto cars_density = fill_cars_density(
            {
                    {from_time(10, 15), from_time(12, 15)},
                    {from_time(12, 15), from_time(12, 15)}
            });
    EXPECT_EQ(std::vector<int>({1, 0}), build_cars_cumulative(cars_density));
}

TEST(CarsDensity, build_cars_cumulative_3_interleaved)
{
    using date_time::from_time;

    auto cars_density = fill_cars_density(
            {
                    {from_time(10, 15), from_time(12, 15)},
                    {from_time(12, 15), from_time(13, 35)},
                    {from_time(12, 0), from_time(13, 0)}
            });
    EXPECT_EQ(std::vector<int>({1, 2, 2, 1, 0}), build_cars_cumulative(cars_density));
}

TEST(CarsDensity, find_first_busiest_time_0)
{
    auto cars_density = fill_cars_density(
            {

            });
    EXPECT_THROW(find_first_busiest_time(cars_density), std::runtime_error);
}

TEST(CarsDensity, find_first_busiest_time_1)
{
    using date_time::from_time;
    using date_time::operator==;

    auto cars_density = fill_cars_density(
            {
                    {from_time(10, 15), from_time(12, 15)}
            });
    auto busiest_time = find_first_busiest_time(cars_density);
    EXPECT_TRUE(from_time(10, 15) == busiest_time.first);
    EXPECT_TRUE(from_time(12, 15) == busiest_time.second);
}

TEST(CarsDensity, find_first_busiest_time_2_nested)
{
    using date_time::from_time;
    using date_time::operator==;

    auto cars_density = fill_cars_density(
            {
                    {from_time(10, 15), from_time(12, 15)},
                    {from_time(11, 33), from_time(11, 59)}
            });
    auto busiest_time = find_first_busiest_time(cars_density);
    EXPECT_TRUE(from_time(11, 33) == busiest_time.first);
    EXPECT_TRUE(from_time(11, 59) == busiest_time.second);
}

TEST(CarsDensity, find_first_busiest_time_2_interleaved)
{
    using date_time::from_time;
    using date_time::operator==;

    auto cars_density = fill_cars_density(
            {
                    {from_time(10, 15), from_time(12, 15)},
                    {from_time(11, 33), from_time(13, 40)}
            });
    auto busiest_time = find_first_busiest_time(cars_density);
    EXPECT_TRUE(from_time(11, 33) == busiest_time.first);
    EXPECT_TRUE(from_time(12, 15) == busiest_time.second);
}

TEST(CarsDensity, find_first_busiest_time_2_intersected)
{
    using date_time::from_time;
    using date_time::operator==;

    auto cars_density = fill_cars_density(
            {
                    {from_time(10, 15), from_time(12, 15)},
                    {from_time(12, 15), from_time(13, 40)}
            });
    auto busiest_time = find_first_busiest_time(cars_density);
    EXPECT_TRUE(from_time(10, 15) == busiest_time.first);
    EXPECT_TRUE(from_time(13, 40) == busiest_time.second);
}

TEST(CarsDensity, find_first_busiest_time_2_separated)
{
    using date_time::from_time;
    using date_time::operator==;

    auto cars_density = fill_cars_density(
            {
                    {from_time(10, 15), from_time(12, 15)},
                    {from_time(12, 30), from_time(13, 40)}
            });
    auto busiest_time = find_first_busiest_time(cars_density);
    EXPECT_TRUE(from_time(10, 15) == busiest_time.first);
    EXPECT_TRUE(from_time(12, 15) == busiest_time.second);
}

TEST(CarsDensity, find_first_busiest_time_3_nested)
{
    using date_time::from_time;
    using date_time::operator==;

    auto cars_density = fill_cars_density(
            {
                    {from_time(10, 15), from_time(12, 15)},
                    {from_time(11, 45), from_time(11, 50)},
                    {from_time(11, 33), from_time(11, 59)}
            });
    auto busiest_time = find_first_busiest_time(cars_density);
    EXPECT_TRUE(from_time(11, 45) == busiest_time.first);
    EXPECT_TRUE(from_time(11, 50) == busiest_time.second);
}

TEST(CarsDensity, find_first_busiest_time_3_interleaved)
{
    using date_time::from_time;
    using date_time::operator==;

    auto cars_density = fill_cars_density(
            {
                    {from_time(10, 15), from_time(12, 15)},
                    {from_time(11, 45), from_time(12, 30)},
                    {from_time(11, 33), from_time(13, 40)}
            });
    auto busiest_time = find_first_busiest_time(cars_density);
    EXPECT_TRUE(from_time(11, 45) == busiest_time.first);
    EXPECT_TRUE(from_time(12, 15) == busiest_time.second);
}

TEST(CarsDensity, find_first_busiest_time_3_intersected)
{
    using date_time::from_time;
    using date_time::operator==;

    auto cars_density = fill_cars_density(
            {
                    {from_time(12, 0), from_time(13, 0)},
                    {from_time(10, 15), from_time(12, 15)},
                    {from_time(12, 15), from_time(13, 40)}
            });
    auto busiest_time = find_first_busiest_time(cars_density);
    EXPECT_TRUE(from_time(12, 0) == busiest_time.first);
    EXPECT_TRUE(from_time(13, 0) == busiest_time.second);
}

TEST(CarsDensity, find_first_busiest_time_3_separated)
{
    using date_time::from_time;
    using date_time::operator==;

    auto cars_density = fill_cars_density(
            {
                    {from_time(10, 15), from_time(12, 15)},
                    {from_time(12, 30), from_time(13, 40)},
                    {from_time(14, 5), from_time(18, 18)}
            });
    auto busiest_time = find_first_busiest_time(cars_density);
    EXPECT_TRUE(from_time(10, 15) == busiest_time.first);
    EXPECT_TRUE(from_time(12, 15) == busiest_time.second);
}

TEST(CarsDensity, find_first_busiest_time_several_intersected)
{
    using date_time::from_time;
    using date_time::operator==;

    auto cars_density = fill_cars_density(
            {
                    {from_time(9, 0), from_time(18, 0)},
                    {from_time(10, 15), from_time(12, 15)},
                    {from_time(12, 15), from_time(13, 40)},
                    {from_time(13, 40), from_time(15, 25)},
                    {from_time(15, 25), from_time(16, 30)},
                    {from_time(16, 30), from_time(18, 20)}
            });
    auto busiest_time = find_first_busiest_time(cars_density);
    EXPECT_TRUE(from_time(10, 15) == busiest_time.first);
    EXPECT_TRUE(from_time(18, 0) == busiest_time.second);
}
