//
// Created by oleg on 9/19/18.
//

#ifndef PARKINGLOT_IPARSER_HPP
#define PARKINGLOT_IPARSER_HPP

#include <iosfwd>

#include "CarsDensity.hpp"

namespace lib::parsers
{

class IParser
{
public:
    virtual ~IParser() = default;

    virtual cars_density_t parse(std::istream& stream) const = 0;
};

}

#endif //PARKINGLOT_IPARSER_HPP
