//
// Created by oleg on 9/19/18.
//

#ifndef PARKINGLOT_CARSDENSITY_HPP
#define PARKINGLOT_CARSDENSITY_HPP

#include <map>

#include "DateTime.hpp"

namespace lib
{
    using cars_density_t = std::map<
            date_time::date_time_t, int,
            decltype(&date_time::operator<)>;
    cars_density_t build_cars_density();
}

#endif //PARKINGLOT_CARSDENSITY_HPP
