//
// Created by oleg on 9/20/18.
//

#ifndef PARKINGLOT_PARSERSUTILS_HPP
#define PARKINGLOT_PARSERSUTILS_HPP

#include "CarsDensity.hpp"

namespace lib::parsers
{

void process_parking_range(const date_time::date_time_t& park_start,
                           const date_time::date_time_t& park_end,
                           cars_density_t& cars_density);

}

#endif //PARKINGLOT_PARSERSUTILS_HPP
