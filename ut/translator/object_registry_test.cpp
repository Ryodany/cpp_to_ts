#include "entities/balance.hpp"
#include "entities/order.hpp"

#include "translator/class.hpp"
#include "translator/object_registry.hpp"

#include "runtime/runtime.hpp"

#include <catch2/catch.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("Rendered ts file matches target.ts")
{
    using namespace entities;

    BINDER_BEGIN(MarketPolicy)
    BINDER_END()

    BINDER_BEGIN(LimitPolicy)
    BINDER_SET("price", &LimitPolicy::price)
    BINDER_SET("stop", &LimitPolicy::stop)
    BINDER_END()

    BINDER_BEGIN(Order)
    BINDER_SET("symbol", &Order::symbol)
    BINDER_SET("quantity", &Order::quantity)
    BINDER_SET("is_buy", &Order::is_buy)
    BINDER_SET("policy", &Order::policy)
    BINDER_END()

    BINDER_BEGIN(Balance)
    BINDER_SET("free", &Balance::free)
    BINDER_SET("locked", &Balance::locked)
    BINDER_END()

    const std::string TARGET_TS_FILENAME = "target.ts";
    const std::string TARGET_TS_PATH = fs::path(__FILE__).parent_path().string() + "/test_files/" + TARGET_TS_FILENAME;

    const std::ifstream target_file(TARGET_TS_PATH);
    std::stringstream ss;
    ss << target_file.rdbuf();

    const std::string target_content = ss.str();
    REQUIRE(runtime::get_object_registry().render() == target_content);
}
