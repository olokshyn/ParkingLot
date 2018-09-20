//
// Created by oleg on 9/20/18.
//

#include "JsonParser.hpp"

#include <iostream>

#include "nlohmann/json.hpp"

#include "Common.hpp"
#include "ParsersUtils.hpp"

using json = nlohmann::json;

using namespace lib;
using namespace lib::parsers;

cars_density_t JsonParser::parse(std::istream& stream) const
{
    auto cars_density = build_cars_density();

    json j_data;
    stream >> j_data;

    for (const auto& entry : j_data)
    {
        if (entry.find("ArrivalTime") == entry.end()
            || entry.find("LeaveTime") == entry.end())
        {
            throw std::runtime_error("Invalid JSON object");
        }
        auto park_start = date_time::from(entry["ArrivalTime"], g_date_time_format);
        auto park_end = date_time::from(entry["LeaveTime"], g_date_time_format);
        process_parking_range(park_start, park_end, cars_density);
    }
    return cars_density;
}
