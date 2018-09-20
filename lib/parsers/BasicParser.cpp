//
// Created by oleg on 9/19/18.
//

#include "BasicParser.hpp"

#include <iostream>
#include <string>
#include <sstream>

#include "Common.hpp"
#include "DateTime.hpp"
#include "ParsersUtils.hpp"

using namespace lib;
using namespace lib::parsers;

cars_density_t BasicParser::parse(std::istream& stream) const
{
    auto cars_density = build_cars_density();

    std::string line;
    while (std::getline(stream, line))
    {
        std::stringstream line_stream(line);
        auto park_start = date_time::from(line_stream, g_time_format);
        auto park_end = date_time::from(line_stream, g_time_format);
        process_parking_range(park_start, park_end, cars_density);
    }
    return cars_density;
}
