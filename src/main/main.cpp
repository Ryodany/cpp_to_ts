#include "entities/balance.hpp"
#include "entities/order.hpp"

#include "translator/class.hpp"
#include "translator/object_registry.hpp"

#include "runtime/runtime.hpp"

#include <iostream>

using entities::Balance;
using entities::LimitPolicy;
using entities::MarketPolicy;
using entities::Order;

int main(int argc, char *argv[])
{
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

    std::cout << runtime::get_object_registry().render() << std::endl;
};