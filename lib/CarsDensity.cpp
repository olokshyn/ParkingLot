//
// Created by oleg on 9/20/18.
//

#include "CarsDensity.hpp"

using namespace lib;

cars_density_t lib::build_cars_density()
{
    return cars_density_t(date_time::operator<);
}
