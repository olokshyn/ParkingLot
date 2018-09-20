//
// Created by oleg on 9/20/18.
//

#ifndef PARKINGLOT_JSONPARSER_HPP
#define PARKINGLOT_JSONPARSER_HPP

#include "IParser.hpp"

namespace lib::parsers
{

class JsonParser : public IParser
{
public:
    cars_density_t parse(std::istream& stream) const override;
};

}

#endif //PARKINGLOT_JSONPARSER_HPP
