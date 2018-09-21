//
// Created by oleg on 9/19/18.
//

#ifndef PARKINGLOT_CARSDENSITY_HPP
#define PARKINGLOT_CARSDENSITY_HPP

#include <map>
#include <vector>

#include "DateTime.hpp"

namespace lib
{

using cars_density_t = std::map<
        date_time::date_time_t, int,
        decltype(&date_time::operator<)>;

using date_time_pair_t = std::pair<date_time::date_time_t,
                                   date_time::date_time_t>;

cars_density_t build_cars_density();

std::vector<int> build_cars_cumulative(const cars_density_t& cars_density);

date_time_pair_t find_first_busiest_time(const cars_density_t& cars_density);

}

#endif //PARKINGLOT_CARSDENSITY_HPP
