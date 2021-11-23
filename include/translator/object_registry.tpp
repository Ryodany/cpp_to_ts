#ifndef object_registry_tpp
#define object_registry_tpp

#ifndef object_registry_hpp
#error "Template files should only be included by their header file"
#endif

#include "runtime/runtime.hpp"
#include "translator/object_registry.hpp"

#include "types/utils.hpp"

#include <string>

namespace translator
{

template<typename T>
Binder<T>::Binder()
{
    m_class_descriptor = { T().name(), {} };
}

template<typename T>
Binder<T>::~Binder()
{
    runtime::get_object_registry().append(m_class_descriptor);
}

template <typename T>
template <typename Attribute>
void Binder<T>::set(std::string name, Attribute attribute)
{
    m_class_descriptor.properties.push_back({
        types::to_camel_case(name),
        types::get_ts_type_name<decltype(types::member_actual_type(attribute))>(),
        types::is_optional<decltype(types::member_actual_type(attribute))>()
    });
}

} // namespace translator

#endif