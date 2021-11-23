#ifndef runtime_hpp
#define runtime_hpp

namespace translator
{
class ObjectRegistry;
}

namespace runtime
{

translator::ObjectRegistry &get_object_registry();

} // namespace runtime

#endif