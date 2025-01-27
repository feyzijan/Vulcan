#include "General_Good.hpp"
#include "Firm_Agent.hpp"


class Consumer_Firm_Agent;
class Capital_Firm_Agent;


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







