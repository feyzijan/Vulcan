#include "General_Good.hpp"
#include "Firm_Agent.hpp"


class Consumer_Firm_Agent;
class Capital_Firm_Agent;

// Constructors and so on

General_Good::General_Good() {};
General_Good::General_Good(General_Good&){};
General_Good::~General_Good() {};





// Printing
void General_Good::Print(){
    cout << "General Good at address: " << this << endl;
    cout << "Price: " << price  << " Quantity: " << quantity << endl;
    cout << "Seller: " << pSeller << endl;
}



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







