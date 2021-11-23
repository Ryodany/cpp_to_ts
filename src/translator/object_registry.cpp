#include "translator/object_registry.hpp"

#include <sstream>
#include <algorithm>

namespace translator
{

void ObjectRegistry::append(const ClassDescriptor &descriptor)
{
    m_descriptors.push_back(descriptor);
};

std::string indent(size_t spaces)
{
    std::string ret;
    std::fill_n(std::back_inserter(ret), spaces, ' ');

    return ret;
}

std::string ObjectRegistry::render() const
{
    std::stringstream ss{};

    for (const ClassDescriptor &descriptor : m_descriptors)
    {
        ss << "class " << descriptor.name << " {" << std::endl;

        for (const ClassDescriptorProperty &property : descriptor.properties)
        {
            ss << indent(INDENTATION_SPACES) << property.key << (property.optional ? "?" : "")
                << ": " << property.type << ";" << std::endl;
        }

        ss << "};" << std::endl << std::endl;
    }

    std::stringstream endline;
    endline << std::endl;

    std::string ret = ss.str();
    return ret.substr(0, ret.find_last_not_of(endline.str()) + 1);
}

}