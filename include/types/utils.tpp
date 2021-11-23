#ifndef types_utils_tpp
#define types_utils_tpp

#ifndef types_utils_hpp
#error "Template files should only be included by their header file"
#endif

#include "entities/utils.hpp"

#include <type_traits>
#include <string>
#include <map>
#include <optional>
#include <variant>

namespace types
{

    template <typename C, typename T>
    T member_actual_type(T C::*v);

    template <typename T>
    constexpr std::string get_ts_type_name();

    template <typename T1, typename T2>
    constexpr bool is_of_type()
    {
        return std::is_same_v<typename std::decay_t<T1>, T2>;
    }

    template <typename T>
    constexpr bool is_bool()
    {
        return is_of_type<T, bool>();
    }

    template <typename T>
    constexpr bool is_number()
    {
        return std::is_arithmetic_v<typename std::decay_t<T>> && !is_bool<T>();
    }

    namespace
    {

        template <typename T>
        constexpr bool is_integral()
        {
            return std::is_integral_v<T> && !is_bool<T>();
        }

        template <typename>
        constexpr bool is_templated_type() { return false; }

        template <template <typename...> typename T>
        constexpr bool is_templated_type() { return true; }

        template <typename, template <typename...> typename>
        struct is_same_templated_type_helper : public std::false_type
        {
        };

        template <typename... T, template <typename...> typename U>
        struct is_same_templated_type_helper<U<T...>, U> : public std::true_type
        {
        };

        template <typename T, template <typename...> typename BaseType>
        constexpr bool is_same_templated_type()
        {
            typedef typename std::decay_t<T> DecayedType;

            return is_same_templated_type_helper<DecayedType, BaseType>();
        }

        template <typename T>
        struct extract_single_template_parameter
        {
            typedef T type;
        };

        template <template <typename, typename...> typename TemplatedType, typename T, typename... Args>
        struct extract_single_template_parameter<TemplatedType<T, Args...>>
        {
            typedef T type;
        };

        template <typename T>
        constexpr std::string get_variant_type_name()
        {
            if constexpr (entities::has_const_name_method<T>())
                return T().name();
            else
                return get_ts_type_name<T>();
        }

        const std::string TS_VARIANT_SEPARATOR = " | ";
        template <template <typename...> typename TemplatedType, typename... T>
        constexpr std::string concat_variant_type(const TemplatedType<T...> &)
        {
            return (... += (get_variant_type_name<T>() + TS_VARIANT_SEPARATOR));
        }

    } // anonymous namespace

    // TODO: try not to use this function, get the ts type names in a container and
    // then concatenate them with TS_VARIANT_SEPARATOR to avoid having to remove the last separator
    template <typename T>
    constexpr std::string get_variant_type()
    {
        std::string ret = concat_variant_type(T{});
        return ret.substr(0, ret.find_last_not_of(TS_VARIANT_SEPARATOR) + 1);
    }

    template <typename T>
    constexpr bool is_string()
    {
        typedef typename std::decay_t<T> DecayedType;
        typedef typename std::remove_pointer_t<typename std::remove_all_extents_t<DecayedType>> BareType;

        constexpr bool is_cstring = is_integral<BareType>() && std::is_pointer_v<DecayedType>;
        return is_same_templated_type<DecayedType, std::basic_string>() || is_cstring;
    }

    template <typename T>
    constexpr bool is_optional()
    {
        return is_same_templated_type<T, std::optional>();
    }

    template <typename T>
    constexpr bool is_variant()
    {
        return is_same_templated_type<T, std::variant>();
    }

    template <typename T>
    constexpr std::string get_ts_type_name()
    {
        if constexpr (is_bool<T>())
        {
            return TYPE_NAME_BOOLEAN;
        }
        else if constexpr (is_number<T>())
        {
            return TYPE_NAME_NUMBER;
        }
        else if constexpr (is_string<T>())
        {
            return TYPE_NAME_STRING;
        }
        else if constexpr (is_optional<T>())
        {
            typedef typename extract_single_template_parameter<T>::type optional_value_type;
            return get_ts_type_name<optional_value_type>();
        }
        else if constexpr (is_variant<T>())
        {
            return get_variant_type<T>();
        }
        else if constexpr (is_same_templated_type<T, std::tuple>())
        {
            return get_variant_type<T>();
        }
        else if constexpr (entities::has_const_name_method<T>())
        {
            return T().name();
        }
        else
        {
            return TYPE_NAME_ANY;
        }
    }

} // namespace types

#endif