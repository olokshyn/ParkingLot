//
// Created by oleg on 9/19/18.
//

#ifndef PARKINGLOT_BASICPARSER_HPP
#define PARKINGLOT_BASICPARSER_HPP

#include "IParser.hpp"

namespace lib::parsers
{

class BasicParser : public IParser
{
public:
    cars_density_t parse(std::istream& stream) const override;
};

}

#endif //PARKINGLOT_BASICPARSER_HPP
