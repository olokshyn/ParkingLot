//
// Created by oleg on 9/20/18.
//

#ifndef PARKINGLOT_TESTSUTILS_HPP
#define PARKINGLOT_TESTSUTILS_HPP

#endif //PARKINGLOT_TESTSUTILS_HPP

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#include "gtest/gtest.h"

#include "DateTime.hpp"

template <typename Parser>
void check_case(const std::string& input,
                const std::vector<std::pair<lib::date_time::date_time_t, int>>& result)
{
    std::stringstream stream(input);
    Parser parser;
    auto cd = parser.parse(stream);
    ASSERT_EQ(result.size(), cd.size());
    EXPECT_TRUE(std::equal(cd.begin(), cd.end(), result.begin(),
                           [](const auto& left, const auto& right) -> bool
                           {
                               using lib::date_time::operator==;
                               return left.first == right.first
                                      && left.second == right.second;
                           }));

}
