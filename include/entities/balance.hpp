#ifndef balance_hpp
#define balance_hpp

#include <string>

namespace entities
{

struct Balance
{
    double free;
    double locked;

    std::string name() const { return "Balance"; }
};

}; // namespace entities

#endif