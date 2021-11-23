#ifndef class_hpp
#define class_hpp

#include <string>
#include <vector>

namespace translator
{

struct ClassDescriptorProperty
{
    std::string key;
    std::string type;
    bool optional;
};

struct ClassDescriptor
{
    std::string name;
    std::vector<ClassDescriptorProperty> properties;
};

} // namespace translator

#endif