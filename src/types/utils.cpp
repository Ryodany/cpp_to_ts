#include "types/utils.hpp"

#include <regex>

namespace types
{

std::string to_camel_case(std::string str)
{
    std::string ret;
    bool underscore = false;
    for (size_t index = str.find_first_not_of('_'); index < str.size(); index++)
    {
        if (str[index] == '_')
            underscore = true;
        else if (underscore)
        {
            ret += std::toupper(str[index]);
            underscore = false;
        }
        else
            ret += str[index];
    }

    return ret;
}

std::string to_camel_case_regex(std::string str)
{
    // takes roughly 223x the time of non-regex to_camel_case function
    std::string camel_case_str;

    std::regex snake_case(R"(([^_]*))");
    for (std::sregex_iterator it = std::sregex_iterator(str.begin(), str.end(), snake_case);
            it != std::sregex_iterator();
            it++)
    {
        std::string match = it->str();
        if (!camel_case_str.empty())
            match[0] = std::toupper(match[0]);

        camel_case_str += match;
    }

    return camel_case_str;
}

} // namespace types