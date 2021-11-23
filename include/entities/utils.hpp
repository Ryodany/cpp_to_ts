#ifndef utils_hpp
#define utils_hpp

#include <type_traits>
#include <string>

namespace entities
{

template <typename C>
struct has_const_name_method_helper
{
    template <typename T>
    static std::true_type test_signature(std::string (T::*)() const);

    template <typename T>
    static decltype(test_signature(&T::name)) test(std::nullptr_t);

    template <typename T>
    static std::false_type test(...);

public:
    using type = decltype(test<C>(nullptr));
    static const bool value = type::value;
};

template <typename T>
constexpr bool has_const_name_method()
{
    return has_const_name_method_helper<T>::value;
}

} // namespace entities

#endif