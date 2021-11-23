#include "entities/utils.hpp"

#include <catch2/catch.hpp>

namespace
{

struct Dummy { };
struct DummyWithConstNameMethod
{
    std::string name() const
    {
        return "dummy";
    }
};
struct DummyWithNonConstNameMethod
{
    std::string name()
    {
        return "dummy";
    }
};

}

TEST_CASE("Has const name method")
{
    REQUIRE(entities::has_const_name_method<DummyWithConstNameMethod>());

    REQUIRE(not entities::has_const_name_method<bool>());
    REQUIRE(not entities::has_const_name_method<int>());
    REQUIRE(not entities::has_const_name_method<std::string>());
    REQUIRE(not entities::has_const_name_method<Dummy>());
    REQUIRE(not entities::has_const_name_method<DummyWithNonConstNameMethod>());
}