#ifndef types_utils_hpp
#define types_utils_hpp

#include <string>

namespace types
{

    std::string to_camel_case(std::string str);
    std::string to_camel_case_regex(std::string str);

    const std::string TYPE_NAME_BOOLEAN = "boolean";
    const std::string TYPE_NAME_NUMBER = "number";
    const std::string TYPE_NAME_STRING = "string";
    const std::string TYPE_NAME_ANY = "any";

} // namespace types

#include "types/utils.tpp"

#endif