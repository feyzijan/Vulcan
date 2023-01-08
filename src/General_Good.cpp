#include "General_Good.hpp"
#include "Firm_Agent.hpp"


General_Good::General_Good(Firm_Agent *  seller_pointer, int price, int quantity)
{
    pSeller = seller_pointer;
    this->price = price;
    this->quantity = quantity;
}






