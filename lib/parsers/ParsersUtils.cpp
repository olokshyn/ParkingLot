//
// Created by oleg on 9/20/18.
//

#include "ParsersUtils.hpp"

#include <stdexcept>

using namespace lib;

void parsers::process_parking_range(const date_time::date_time_t& park_start,
                                    const date_time::date_time_t& park_end,
                                    cars_density_t& cars_density)
{
    using lib::date_time::operator>;

    if (park_start > park_end)
    {
        throw std::runtime_error("Invalid parking time range: start > end");
    }
    cars_density[park_start] += 1;
    cars_density[park_end] -= 1;
}
