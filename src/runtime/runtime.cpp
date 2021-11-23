#include "runtime/runtime.hpp"

#include "translator/object_registry.hpp"

namespace runtime
{

translator::ObjectRegistry &get_object_registry()
{
    static translator::ObjectRegistry s_object_registry;
    return s_object_registry;
}

} // namespace runtime