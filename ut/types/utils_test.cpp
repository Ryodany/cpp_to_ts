#include "types/utils.hpp"

#include <catch2/catch.hpp>

#include <vector>
#include <bitset>
#include <array>
#include <string>
#include <tuple>
#include <type_traits>
#include <chrono>

namespace
{

class Dummy { };
class DummyWithConstNameMethod { public: std::string name() const { return "Dummy"; } };

}

TEST_CASE("It's of type bool")
{
    SECTION("Plain bool")
    {
        REQUIRE(types::is_bool<bool>());
    }

    SECTION("Qualifiers")
    {
        REQUIRE(types::is_bool<bool &>());
        REQUIRE(types::is_bool<const bool>());
        REQUIRE(types::is_bool<const bool &>());
        REQUIRE(types::is_bool<bool &&>());
        REQUIRE(types::is_bool<volatile bool>());
    }
}

TEST_CASE("It's not of type bool")
{
    SECTION("Types")
    {
        REQUIRE(not types::is_bool<int>());
        REQUIRE(not types::is_bool<float>());
        REQUIRE(not types::is_bool<const float>());
        REQUIRE(not types::is_bool<const float &>());
        REQUIRE(not types::is_bool<float &>());
        REQUIRE(not types::is_bool<size_t>());
        REQUIRE(not types::is_bool<uint64_t>());
        REQUIRE(not types::is_bool<short>());
        REQUIRE(not types::is_bool<long>());

        REQUIRE(not types::is_bool<std::string>());
        REQUIRE(not types::is_bool<std::vector<int>>());
    }

    SECTION("Qualifiers")
    {
        REQUIRE(not types::is_bool<bool *>());
        REQUIRE(not types::is_bool<const bool *>());
        REQUIRE(not types::is_bool<const bool * const>());
        REQUIRE(not types::is_bool<bool *&>());
    }

    SECTION("Functions")
    {
        REQUIRE(not types::is_bool<bool(*)()>());
        REQUIRE(not types::is_bool<bool(*)(int)>());
        REQUIRE(not types::is_bool<void(*)()>());
    }

    SECTION("Arrays")
    {
        REQUIRE(not types::is_bool<bool[]>());
        REQUIRE(not types::is_bool<bool[42]>());
        REQUIRE(not types::is_bool<std::array<bool, 42>>());
    }
}

TEST_CASE("It's of type number")
{
    SECTION("Plain number")
    {
        REQUIRE(types::is_number<char>());
        REQUIRE(types::is_number<wchar_t>());
        REQUIRE(types::is_number<unsigned char>());
        REQUIRE(types::is_number<int>());
        REQUIRE(types::is_number<short>());
        REQUIRE(types::is_number<long>());
        REQUIRE(types::is_number<signed long>());
        REQUIRE(types::is_number<float>());
        REQUIRE(types::is_number<double>());
        REQUIRE(types::is_number<size_t>());
        REQUIRE(types::is_number<int8_t>());
        REQUIRE(types::is_number<int16_t>());
        REQUIRE(types::is_number<int32_t>());
        REQUIRE(types::is_number<int64_t>());
        REQUIRE(types::is_number<uint8_t>());
        REQUIRE(types::is_number<uint16_t>());
        REQUIRE(types::is_number<uint32_t>());
        REQUIRE(types::is_number<uint64_t>());
    }

    SECTION("Qualifiers")
    {
        REQUIRE(types::is_number<int &>());
        REQUIRE(types::is_number<const int>());
        REQUIRE(types::is_number<const int &>());
        REQUIRE(types::is_number<int &&>());
        REQUIRE(types::is_number<volatile int>());
    }
}

TEST_CASE("It's not of type number")
{
    SECTION("Types")
    {
        REQUIRE(not types::is_number<bool>());
        REQUIRE(not types::is_number<std::bitset<64>>());
        REQUIRE(not types::is_number<std::string>());
        REQUIRE(not types::is_number<std::vector<int>>());
        REQUIRE(not types::is_number<std::vector<float>>());
        REQUIRE(not types::is_number<std::vector<double>>());
    }

    SECTION("Qualifiers")
    {
        REQUIRE(not types::is_number<int *>());
        REQUIRE(not types::is_number<const int *>());
        REQUIRE(not types::is_number<const int * const>());
        REQUIRE(not types::is_number<int *&>());
    }

    SECTION("Functions")
    {
        REQUIRE(not types::is_number<int(*)()>());
        REQUIRE(not types::is_number<int(*)(int)>());
        REQUIRE(not types::is_number<float(*)(int)>());
        REQUIRE(not types::is_number<double(*)(short)>());
        REQUIRE(not types::is_number<void(*)()>());
    }

    SECTION("Arrays")
    {
        REQUIRE(not types::is_number<char[]>());
        REQUIRE(not types::is_number<int[]>());
        REQUIRE(not types::is_number<int[42]>());
        REQUIRE(not types::is_number<float[42]>());
        REQUIRE(not types::is_number<double[42]>());
        REQUIRE(not types::is_number<uint64_t[42]>());
        REQUIRE(not types::is_number<std::array<int, 42>>());
        REQUIRE(not types::is_number<std::array<float, 42>>());
        REQUIRE(not types::is_number<std::array<int16_t, 42>>());
    }
}

template <typename T>
constexpr void require_is_string_helper()
{
    REQUIRE(types::is_string<T *>());
    REQUIRE(types::is_string<const T *>());
    REQUIRE(types::is_string<const T * const>());
    REQUIRE(types::is_string<T[]>());
    REQUIRE(types::is_string<const T[]>());
}

TEST_CASE("It's of type string")
{
    SECTION("Plain string")
    {
        require_is_string_helper<char>();
        require_is_string_helper<unsigned char>();
        require_is_string_helper<wchar_t>();
        require_is_string_helper<int8_t>();
        require_is_string_helper<uint8_t>();
        require_is_string_helper<int16_t>();
        require_is_string_helper<uint16_t>();
        require_is_string_helper<int64_t>();
        require_is_string_helper<uint64_t>();

        REQUIRE(types::is_string<std::string>());
        REQUIRE(types::is_string<std::wstring>());
    }

    SECTION("Qualifiers")
    {
        REQUIRE(types::is_string<char *&>());
        REQUIRE(types::is_string<const char *>());
        REQUIRE(types::is_string<const char *&>());
        REQUIRE(types::is_string<char *&&>());
        REQUIRE(types::is_string<volatile char *>());

        REQUIRE(types::is_string<std::string &>());
        REQUIRE(types::is_string<const std::string>());
        REQUIRE(types::is_string<const std::string &>());
        REQUIRE(types::is_string<std::string &&>());
        REQUIRE(types::is_string<volatile std::string>());

        REQUIRE(types::is_string<std::wstring &>());
        REQUIRE(types::is_string<const std::wstring>());
        REQUIRE(types::is_string<const std::wstring &>());
        REQUIRE(types::is_string<std::wstring &&>());
        REQUIRE(types::is_string<volatile std::wstring>());
    }

    SECTION("Arrays")
    {
        REQUIRE(types::is_string<char[]>());
        REQUIRE(types::is_string<char[42]>());
        REQUIRE(types::is_string<int[]>());
        REQUIRE(types::is_string<int[42]>());
        REQUIRE(types::is_string<uint64_t[42]>());
    }
}

TEST_CASE("It's not of type string")
{
    SECTION("Types")
    {
        REQUIRE(not types::is_string<bool>());
        REQUIRE(not types::is_string<std::bitset<64>>());
        REQUIRE(not types::is_string<std::vector<char>>());
        REQUIRE(not types::is_string<std::vector<wchar_t>>());
        REQUIRE(not types::is_string<std::vector<int>>());
        REQUIRE(not types::is_string<std::vector<float>>());
        REQUIRE(not types::is_string<std::vector<double>>());
    }

    SECTION("Qualifiers")
    {
        REQUIRE(not types::is_string<char **>());
        REQUIRE(not types::is_string<const char **>());
        REQUIRE(not types::is_string<const char ** const>());
        REQUIRE(not types::is_string<char **&>());

        REQUIRE(not types::is_string<std::string *>());
        REQUIRE(not types::is_string<const std::string *>());
        REQUIRE(not types::is_string<const std::string * const>());
        REQUIRE(not types::is_string<std::string *&>());

        REQUIRE(not types::is_string<std::wstring *>());
        REQUIRE(not types::is_string<const std::wstring *>());
        REQUIRE(not types::is_string<const std::wstring * const>());
        REQUIRE(not types::is_string<std::wstring *&>());
    }

    SECTION("Functions")
    {
        REQUIRE(not types::is_string<char(*)()>());
        REQUIRE(not types::is_string<char(*)(int)>());
        REQUIRE(not types::is_string<char *(*)()>());
        REQUIRE(not types::is_string<std::string(*)()>());
    }

    SECTION("Arrays")
    {
        REQUIRE(not types::is_string<float[]>());
        REQUIRE(not types::is_string<float[42]>());
        REQUIRE(not types::is_string<double[42]>());
        REQUIRE(not types::is_string<std::vector<char>>());
        REQUIRE(not types::is_string<std::vector<int>>());
        REQUIRE(not types::is_string<std::array<int, 42>>());
        REQUIRE(not types::is_string<std::array<float, 42>>());
        REQUIRE(not types::is_string<std::array<int16_t, 42>>());
    }
}

TEST_CASE("It's of type optional")
{
    SECTION("Plain optional")
    {
        REQUIRE(types::is_optional<std::optional<bool>>());
        REQUIRE(types::is_optional<std::optional<int>>());
        REQUIRE(types::is_optional<std::optional<std::string>>());
        REQUIRE(types::is_optional<std::optional<std::vector<std::optional<int>>>>());
    }

    SECTION("Qualifiers")
    {
        REQUIRE(types::is_optional<std::optional<std::string> &>());
        REQUIRE(types::is_optional<const std::optional<std::string>>());
        REQUIRE(types::is_optional<const std::optional<std::string> &>());
        REQUIRE(types::is_optional<std::optional<std::string> &&>());
        REQUIRE(types::is_optional<volatile std::optional<std::string>>());
    }
}

TEST_CASE("It's not of type optional")
{
    SECTION("Types")
    {
        REQUIRE(not types::is_optional<bool>());
        REQUIRE(not types::is_optional<std::bitset<64>>());
        REQUIRE(not types::is_optional<std::vector<std::optional<int>>>());
    }

    SECTION("Qualifiers")
    {
        REQUIRE(not types::is_optional<std::optional<std::string> *>());
        REQUIRE(not types::is_optional<const std::optional<std::string> *>());
        REQUIRE(not types::is_optional<const std::optional<std::string> * const>());
        REQUIRE(not types::is_optional<std::optional<std::string> *&>());
    }

    SECTION("Functions")
    {
        REQUIRE(not types::is_optional<std::optional<std::string>(*)()>());
        REQUIRE(not types::is_optional<char(*)(int)>());
    }
}

TEST_CASE("It's of type variant")
{
    SECTION("Plain variant")
    {
        REQUIRE(types::is_variant<std::variant<bool>>());
        REQUIRE(types::is_variant<std::variant<int>>());
        REQUIRE(types::is_variant<std::variant<int, bool>>());
        REQUIRE(types::is_variant<std::variant<Dummy, bool>>());
        REQUIRE(types::is_variant<std::variant<int, bool, std::string>>());
        REQUIRE(types::is_variant<std::variant<Dummy, bool, int>>());
    }

    SECTION("Qualifiers")
    {
        REQUIRE(types::is_variant<std::variant<std::string> &>());
        REQUIRE(types::is_variant<const std::variant<std::string>>());
        REQUIRE(types::is_variant<const std::variant<std::string> &>());
        REQUIRE(types::is_variant<std::variant<std::string> &&>());
        REQUIRE(types::is_variant<volatile std::variant<std::string>>());

        REQUIRE(types::is_variant<std::variant<std::string, int> &>());
        REQUIRE(types::is_variant<const std::variant<std::string, int>>());
        REQUIRE(types::is_variant<const std::variant<std::string, int> &>());
        REQUIRE(types::is_variant<std::variant<std::string, int> &&>());
        REQUIRE(types::is_variant<volatile std::variant<std::string, int>>());
    }
}

TEST_CASE("It's not of type variant")
{
    SECTION("Types")
    {
        REQUIRE(not types::is_variant<bool>());
        REQUIRE(not types::is_variant<std::bitset<64>>());
        REQUIRE(not types::is_variant<std::vector<std::variant<int>>>());
    }

    SECTION("Qualifiers")
    {
        REQUIRE(not types::is_variant<std::variant<std::string> *>());
        REQUIRE(not types::is_variant<const std::variant<std::string> *>());
        REQUIRE(not types::is_variant<const std::variant<std::string> * const>());
        REQUIRE(not types::is_variant<std::variant<std::string> *&>());

        REQUIRE(not types::is_variant<std::variant<std::string, int> *>());
        REQUIRE(not types::is_variant<const std::variant<std::string, int> *>());
        REQUIRE(not types::is_variant<const std::variant<std::string, int> * const>());
        REQUIRE(not types::is_variant<std::variant<std::string, int> *&>());
    }

    SECTION("Functions")
    {
        REQUIRE(not types::is_variant<std::variant<std::string>(*)()>());
        REQUIRE(not types::is_variant<char(*)(int)>());
    }
}

TEST_CASE("Get TS types names")
{
    REQUIRE(types::get_ts_type_name<bool>() == types::TYPE_NAME_BOOLEAN);
    REQUIRE(types::get_ts_type_name<bool &>() == types::TYPE_NAME_BOOLEAN);
    REQUIRE(types::get_ts_type_name<const bool>() == types::TYPE_NAME_BOOLEAN);
    REQUIRE(types::get_ts_type_name<const bool &>() == types::TYPE_NAME_BOOLEAN);

    REQUIRE(types::get_ts_type_name<char *>() == types::TYPE_NAME_STRING);
    REQUIRE(types::get_ts_type_name<int *>() == types::TYPE_NAME_STRING);
    REQUIRE(types::get_ts_type_name<const char *>() == types::TYPE_NAME_STRING);
    REQUIRE(types::get_ts_type_name<const int *>() == types::TYPE_NAME_STRING);
    REQUIRE(types::get_ts_type_name<std::string>() == types::TYPE_NAME_STRING);
    REQUIRE(types::get_ts_type_name<std::wstring>() == types::TYPE_NAME_STRING);
    REQUIRE(types::get_ts_type_name<std::basic_string<uint8_t>>() == types::TYPE_NAME_STRING);

    REQUIRE(types::get_ts_type_name<double>() == types::TYPE_NAME_NUMBER);
    REQUIRE(types::get_ts_type_name<float>() == types::TYPE_NAME_NUMBER);
    REQUIRE(types::get_ts_type_name<char>() == types::TYPE_NAME_NUMBER);
    REQUIRE(types::get_ts_type_name<int>() == types::TYPE_NAME_NUMBER);
    REQUIRE(types::get_ts_type_name<size_t>() == types::TYPE_NAME_NUMBER);
    REQUIRE(types::get_ts_type_name<int &>() == types::TYPE_NAME_NUMBER);
    REQUIRE(types::get_ts_type_name<double &>() == types::TYPE_NAME_NUMBER);
    REQUIRE(types::get_ts_type_name<const float>() == types::TYPE_NAME_NUMBER);
    REQUIRE(types::get_ts_type_name<const int>() == types::TYPE_NAME_NUMBER);
    REQUIRE(types::get_ts_type_name<const int &>() == types::TYPE_NAME_NUMBER);

    REQUIRE(types::get_ts_type_name<std::optional<Dummy>>() == types::TYPE_NAME_ANY);
    REQUIRE(types::get_ts_type_name<std::optional<int>>() == types::TYPE_NAME_NUMBER);
    REQUIRE(types::get_ts_type_name<std::optional<bool>>() == types::TYPE_NAME_BOOLEAN);

    REQUIRE(types::get_ts_type_name<std::variant<bool>>() == types::TYPE_NAME_BOOLEAN);
    REQUIRE(types::get_ts_type_name<std::variant<bool, double>>() == types::TYPE_NAME_BOOLEAN + " | " + types::TYPE_NAME_NUMBER);
    REQUIRE(types::get_ts_type_name<std::variant<int, bool>>() == types::TYPE_NAME_NUMBER + " | " + types::TYPE_NAME_BOOLEAN);
    REQUIRE(types::get_ts_type_name<std::variant<Dummy, std::string, int>>() == types::TYPE_NAME_ANY + " | " + types::TYPE_NAME_STRING + " | " + types::TYPE_NAME_NUMBER);
    REQUIRE(types::get_ts_type_name<std::variant<DummyWithConstNameMethod, std::string, int>>() ==
                DummyWithConstNameMethod().name() + " | " + types::TYPE_NAME_STRING + " | " + types::TYPE_NAME_NUMBER);

    REQUIRE(types::get_ts_type_name<Dummy>() == types::TYPE_NAME_ANY);
    REQUIRE(types::get_ts_type_name<DummyWithConstNameMethod>() == DummyWithConstNameMethod().name());
    REQUIRE(types::get_ts_type_name<const bool *>() == types::TYPE_NAME_ANY);
}

struct TypeDummy
{
    std::string name() const
    {
        return "Dummy";
    }
};

TEST_CASE("Get variant ts type")
{
    REQUIRE(types::get_variant_type<std::variant<bool>>() == types::TYPE_NAME_BOOLEAN);
    REQUIRE(types::get_variant_type<std::variant<bool, int>>() == types::TYPE_NAME_BOOLEAN + " | " + types::TYPE_NAME_NUMBER);
    REQUIRE(types::get_variant_type<std::variant<bool, int, std::string>>() == types::TYPE_NAME_BOOLEAN + " | " + types::TYPE_NAME_NUMBER + " | " + types::TYPE_NAME_STRING);
    REQUIRE(types::get_variant_type<std::variant<bool, int, double>>() == types::TYPE_NAME_BOOLEAN + " | " + types::TYPE_NAME_NUMBER + " | " + types::TYPE_NAME_NUMBER);
    REQUIRE(types::get_variant_type<std::variant<double, TypeDummy>>() == types::TYPE_NAME_NUMBER + " | " + TypeDummy().name());
}

TEST_CASE("Get tuple ts type")
{
    REQUIRE(types::get_variant_type<std::tuple<bool>>() == types::TYPE_NAME_BOOLEAN);
    REQUIRE(types::get_variant_type<std::tuple<bool, int>>() == types::TYPE_NAME_BOOLEAN + " | " + types::TYPE_NAME_NUMBER);
    REQUIRE(types::get_variant_type<std::tuple<bool, int, std::string>>() == types::TYPE_NAME_BOOLEAN + " | " + types::TYPE_NAME_NUMBER + " | " + types::TYPE_NAME_STRING);
    REQUIRE(types::get_variant_type<std::tuple<bool, int, double>>() == types::TYPE_NAME_BOOLEAN + " | " + types::TYPE_NAME_NUMBER + " | " + types::TYPE_NAME_NUMBER);
    REQUIRE(types::get_variant_type<std::tuple<double, TypeDummy>>() == types::TYPE_NAME_NUMBER + " | " + TypeDummy().name());
}

TEST_CASE("Is same templated type")
{
    REQUIRE(types::is_same_templated_type<std::tuple<bool>, std::tuple>());
    REQUIRE(types::is_same_templated_type<std::tuple<Dummy, bool, double>, std::tuple>());
    REQUIRE(types::is_same_templated_type<std::variant<bool>, std::variant>());
    REQUIRE(types::is_same_templated_type<std::variant<int, bool>, std::variant>());

    REQUIRE(not types::is_same_templated_type<std::variant<int, bool>, std::basic_string>());
    REQUIRE(not types::is_same_templated_type<std::tuple<int, bool>, std::variant>());
}

template <typename T>
struct TemplatedDummy { };

TEST_CASE("Is templated type")
{
    REQUIRE(types::is_templated_type<std::tuple>());
    REQUIRE(types::is_templated_type<std::tuple>());
    REQUIRE(types::is_templated_type<std::variant>());
    REQUIRE(types::is_templated_type<std::variant>());
    REQUIRE(types::is_templated_type<std::optional>());
    REQUIRE(types::is_templated_type<std::optional>());
    REQUIRE(types::is_templated_type<TemplatedDummy>());

    REQUIRE(not types::is_templated_type<bool>());
    REQUIRE(not types::is_templated_type<int>());
    REQUIRE(not types::is_templated_type<double>());
    REQUIRE(not types::is_templated_type<std::string>());
    REQUIRE(not types::is_templated_type<Dummy>());
}

struct DummyWithFields
{
    double price;
    std::optional<double> price_opt;
    std::variant<double, int> value;
};

template <typename T, typename Member>
bool is_same_helper_wrong(Member member)
{
    return std::is_same_v<Member, T>;
}

template <typename T, typename Member>
bool is_same_helper_ok(Member member)
{
    return std::is_same_v<decltype(types::member_actual_type(member)), T>;
}

TEST_CASE("Class member is bare type")
{
    REQUIRE(not is_same_helper_wrong<double>(&DummyWithFields::price));
    REQUIRE(is_same_helper_ok<double>(&DummyWithFields::price));
    REQUIRE(is_same_helper_ok<std::optional<double>>(&DummyWithFields::price_opt));
    REQUIRE(is_same_helper_ok<std::variant<double, int>>(&DummyWithFields::value));
}

TEST_CASE("To camel case")
{
    REQUIRE(types::to_camel_case("") == "");
    REQUIRE(types::to_camel_case("is_buy") == "isBuy");
    REQUIRE(types::to_camel_case("is_buy_") == "isBuy");
    REQUIRE(types::to_camel_case("is__buy_") == "isBuy");
    REQUIRE(types::to_camel_case("is__buy__") == "isBuy");
    REQUIRE(types::to_camel_case("is_buy_hehe_") == "isBuyHehe");
    REQUIRE(types::to_camel_case("is") == "is");
    REQUIRE(types::to_camel_case("_wow_wow") == "wowWow");
    REQUIRE(types::to_camel_case("__wow_wow") == "wowWow");
    REQUIRE(types::to_camel_case("__wow__wow") == "wowWow");
}

template <typename Function>
auto measure(Function func)
{
    auto start = std::chrono::steady_clock::now();
    func();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - start).count();
}

bool is_camel_case_algo_faster(const std::string &str)
{
    return measure([](){types::to_camel_case("");}) < measure([](){types::to_camel_case_regex("");});
}

TEST_CASE("To camel case measurements")
{
    REQUIRE(is_camel_case_algo_faster(""));
    REQUIRE(is_camel_case_algo_faster("is_buy"));
    REQUIRE(is_camel_case_algo_faster("is_buy_"));
    REQUIRE(is_camel_case_algo_faster("is__buy_"));
    REQUIRE(is_camel_case_algo_faster("is__buy__"));
    REQUIRE(is_camel_case_algo_faster("is_buy_hehe_"));
    REQUIRE(is_camel_case_algo_faster("is"));
    REQUIRE(is_camel_case_algo_faster("_wow_wow"));
    REQUIRE(is_camel_case_algo_faster("__wow_wow"));
    REQUIRE(is_camel_case_algo_faster("__wow__wow"));
}