//
// Created by oleg on 9/19/18.
//

#include "BasicParser.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

#include "Common.hpp"
#include "DateTime.hpp"

using namespace lib;
using namespace lib::parsers;

cars_density_t BasicParser::parse(std::istream& stream) const
{
    using lib::date_time::operator>;

    auto cars_density = build_cars_density();

    std::string line;
    while (std::getline(stream, line))
    {
        std::stringstream line_stream(line);
        auto start = date_time::from(line_stream, g_time_format);
        auto end = date_time::from(line_stream, g_time_format);
        if (start > end)
        {
            throw std::runtime_error("Invalid parking time range: start > end");
        }
        cars_density[start] += 1;
        cars_density[end] -= 1;
    }
    return cars_density;
}
