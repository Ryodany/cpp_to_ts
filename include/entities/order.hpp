#ifndef order_hpp
#define order_hpp

#include <optional>
#include <string>
#include <variant>

namespace entities
{

struct MarketPolicy
{
    std::string name() const { return "MarketPolicy"; }
};

struct LimitPolicy
{
    double price;
    std::optional<double> stop;

    std::string name() const { return "LimitPolicy"; }
};

typedef std::variant<MarketPolicy, LimitPolicy> PolicyVariant;

struct Order
{
    std::string symbol;
    double quantity;
    bool is_buy;
    PolicyVariant policy;

    std::string name() const { return "Order"; }
};

}; // namespace entities

#endif