#include "patron.h"
#include <sstream>

double Patron::get_fee(const Chrono::Date& d) const
{
    std::stringstream ss;
    ss << d;
    return fees.at(ss.str());
}

void Patron::set_fee(const Chrono::Date& d, double fee)
{
    std::stringstream ss;
    ss << d;
    fees[ss.str()] = fee;
}
