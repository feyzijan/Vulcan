#include "General_Good.hpp"
#include "Firm_Agent.hpp"


General_Good::General_Good() {};
General_Good::General_Good(General_Good&){};
General_Good::~General_Good() {};






// Overloaded Operators, comparisons made based on price
bool General_Good::operator==(const General_Good& rhs){
 return price == rhs.price;
}
bool General_Good::operator<=(const General_Good& rhs){
    return price <= rhs.price;
}
bool General_Good::operator>=(const General_Good& rhs){
    return price >= rhs.price;
}
bool General_Good::operator>(const General_Good& rhs){
    return price > rhs.price;
}
bool General_Good::operator<(const General_Good& rhs){
    return price < rhs.price;
}
bool General_Good::operator!=(const General_Good& rhs){
    return price != rhs.price;
}







