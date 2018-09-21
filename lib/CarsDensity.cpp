//
// Created by oleg on 9/20/18.
//

#include "CarsDensity.hpp"

#include <cassert>

#include <vector>
#include <algorithm>
#include <iterator>

using namespace lib;

cars_density_t lib::build_cars_density()
{
    return cars_density_t(date_time::operator<);
}

std::vector<int> lib::build_cars_cumulative(const cars_density_t& cars_density)
{
    if (cars_density.empty())
    {
        throw std::runtime_error("Cars density is empty");
    }

    std::vector<int> cars_cumulative(cars_density.size(), 0);
    std::transform(cars_density.begin(), cars_density.end(), cars_cumulative.begin(),
                   [count = 0](const auto& pair) mutable -> int {
                       count += pair.second;
                       return count;
                   });
    return cars_cumulative;
}

date_time_pair_t lib::find_first_busiest_time(const cars_density_t& cars_density)
{
    if (cars_density.empty())
    {
        throw std::runtime_error("Cars density is empty");
    }

    auto cars_cumulative = build_cars_cumulative(cars_density);
    auto iter = std::max_element(cars_cumulative.begin(), cars_cumulative.end());

    auto busiest_time = cars_density.begin();
    std::advance(busiest_time, iter - cars_cumulative.begin());
    assert(busiest_time != cars_density.end());

    date_time::date_time_t busiest_time_start = busiest_time->first;
    date_time::date_time_t busiest_time_end;
    do
    {
        busiest_time_end = (++busiest_time)->first;
    } while (busiest_time->second == 0);
    assert(busiest_time->second < 0);
    return std::make_pair(busiest_time_start, busiest_time_end);
};
