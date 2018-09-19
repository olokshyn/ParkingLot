//
// Created by oleg on 9/19/18.
//

#ifndef PARKINGLOT_DATETIME_HPP
#define PARKINGLOT_DATETIME_HPP

#include <ctime>
#include <iosfwd>
#include <string>

namespace lib::date_time
{

typedef std::tm date_time_t;

extern const char* g_format;

int year(const date_time_t& date_time);

int month(const date_time_t& date_time);

int day(const date_time_t& date_time);

int hour(const date_time_t& date_time);

int min(const date_time_t& date_time);

int sec(const date_time_t& date_time);

date_time_t from_time(int hour, int min, int sec = 0);

date_time_t from_date_time(int year, int month, int day,
                           int hour, int min, int sec = 0);

date_time_t from(std::istream& stream, const char* format = g_format);

date_time_t from(const std::string& str, const char* format = g_format);

std::string to_string(const date_time_t& date_time, const char* format = g_format);

std::ostream& operator<<(std::ostream& stream, const date_time_t& date_time);

bool operator==(const date_time_t& left, const date_time_t& right);

bool operator==(const date_time_t& date_time, const std::string& str);

bool operator==(const std::string& str, const date_time_t& date_time);

bool operator<(const date_time_t& left, const date_time_t& right);

bool operator<=(const date_time_t& left, const date_time_t& right);

bool operator>(const date_time_t& left, const date_time_t& right);

bool operator>=(const date_time_t& left, const date_time_t& right);

}

#endif //PARKINGLOT_DATETIME_HPP
