#ifndef object_registry_hpp
#define object_registry_hpp

#include "translator/class.hpp"

#include <string>
#include <vector>

namespace translator
{

template <typename T>
class Binder
{
private:
    ClassDescriptor m_class_descriptor;

public:
    Binder();
    ~Binder();

    template <typename Attribute>
    void set(std::string name, Attribute attribute);
};

#define BINDER_BEGIN(Class) \
{ \
    translator::Binder<Class> binder;

#define BINDER_SET(name, attribute) \
    binder.set(name, attribute);

#define BINDER_END() \
}

class ObjectRegistry
{
public:
    ObjectRegistry() = default;

    void append(const ClassDescriptor &descriptor);

    std::string render() const;

private:
    const size_t INDENTATION_SPACES = 4;

    std::vector<ClassDescriptor> m_descriptors;
};

} // namespace translator

#include "translator/object_registry.tpp"

#endif