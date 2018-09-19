//
// Created by oleg on 9/19/18.
//

#include "DateTime.hpp"

#include <iomanip>

using namespace lib;
using namespace lib::date_time;

const char* date_time::g_format = "%Y-%m-%d %H:%M:%S";

int date_time::year(const date_time_t& date_time)
{
    return date_time.tm_year + 1900;
}

int date_time::month(const date_time_t& date_time)
{
    return date_time.tm_mon + 1;
}

int date_time::day(const date_time_t& date_time)
{
    return date_time.tm_mday;
}

int date_time::hour(const date_time_t& date_time)
{
    return date_time.tm_hour;
}

int date_time::min(const date_time_t& date_time)
{
    return date_time.tm_min;
}

int date_time::sec(const date_time_t& date_time)
{
    return date_time.tm_sec;
}

date_time_t date_time::from_time(int hour, int min, int sec)
{
    std::tm tm = {};
    tm.tm_hour = hour;
    tm.tm_min = min;
    tm.tm_sec = sec;
    return tm;
}

date_time_t date_time::from_date_time(int year, int month, int day,
                                      int hour, int min, int sec)
{
    std::tm tm = {};
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = hour;
    tm.tm_min = min;
    tm.tm_sec = sec;
    return tm;
}

date_time_t date_time::from(std::istream& stream, const char* format)
{
    std::tm tm = {};
    if (!(stream >> std::get_time(&tm, format)))
    {
        throw std::runtime_error("Failed to parse date-time");
    }
    return tm;
}

date_time_t date_time::from(const std::string& str, const char* format)
{
    std::stringstream stream(str);
    return from(stream, format);
}

std::string date_time::to_string(const date_time_t& date_time, const char* format)
{
    const size_t buffer_size = 64;
    char buf[buffer_size];
    buf[std::strftime(buf, buffer_size, format, &date_time)] = '\0';
    return std::string(buf);
}

std::ostream& date_time::operator<<(std::ostream& stream, const date_time_t& date_time)
{
    return stream << to_string(date_time);
}

bool date_time::operator==(const date_time_t& left, const date_time_t& right)
{
    return left.tm_sec == right.tm_sec
           && left.tm_min == right.tm_min
           && left.tm_hour == right.tm_hour
           && left.tm_mday == right.tm_mday
           && left.tm_mon == right.tm_mon
           && left.tm_year == right.tm_year
           && left.tm_wday == right.tm_wday
           && left.tm_yday == right.tm_yday
           && left.tm_isdst == right.tm_isdst;
}

bool date_time::operator==(const date_time_t& date_time, const std::string& str)
{
    return date_time == from(str);
}

bool date_time::operator==(const std::string& str, const date_time_t& date_time)
{
    return operator==(date_time, str);
}

bool date_time::operator<(const date_time_t& left, const date_time_t& right)
{
    std::tm tmp_left = left;
    std::tm tmp_right = right;
    std::time_t left_since_epoch = std::mktime(&tmp_left);
    std::time_t right_since_epoch = std::mktime(&tmp_right);
    if (left_since_epoch == -1 || right_since_epoch == -1)
    {
        throw std::runtime_error("Cannot convert std::tm to time_t");
    }
    return left_since_epoch < right_since_epoch;
}

bool date_time::operator<=(const date_time_t& left, const date_time_t& right)
{
    return operator<(left, right) || operator==(left, right);
}

bool date_time::operator>(const date_time_t& left, const date_time_t& right)
{
    return !operator<=(left, right);
}

bool date_time::operator>=(const date_time_t& left, const date_time_t& right)
{
    return !operator<(left, right);
}

