//
// Created by oleg on 9/20/18.
//

#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <stdexcept>

#include "Common.hpp"
#include "CarsDensity.hpp"
#include "parsers/BasicParser.hpp"
#include "parsers/JsonParser.hpp"

using namespace lib;
using namespace parsers;
using namespace date_time;

bool str_ends_with(const std::string& str, const std::string& ending)
{
    if (str.size() >= ending.size())
    {
        return str.compare(str.length() - ending.length(), ending.length(), ending) == 0;
    }
    return false;
}

int main(int argc, const char* argv[])
{
    try
    {
        if (argc < 2)
        {
            std::cout << "Usage: " << argv[0] << " [input_file.txt|input_file.json]" << std::endl;
            throw std::runtime_error("Expected one argument: a file name");
        }
        std::string filename = argv[1];

        std::unique_ptr<IParser> parser;
        const char* format;
        if (str_ends_with(filename, ".txt"))
        {
            parser = std::make_unique<BasicParser>();
            format = g_time_format;
        }
        else if (str_ends_with(filename, ".json"))
        {
            parser = std::make_unique<JsonParser>();
            format = g_date_time_format;
        }
        else
        {
            throw std::runtime_error("Only .txt and .json files are supported");
        }

        std::ifstream stream(filename);
        if (!stream.is_open())
        {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        auto busiest_time = find_first_busiest_time(parser->parse(stream));
        std::cout << "The first busiest time is from "
                  << to_string(busiest_time.first, format) << " till "
                  << to_string(busiest_time.second, format) << std::endl;

        return 0;
    }
    catch (const std::runtime_error& error)
    {
        std::cerr << "Error: " << error.what() << std::endl;
    }
    catch (const std::exception& exc)
    {
        std::cerr << "Unhandled exception: " << exc.what() << std::endl;
    }
    return 1;
}
