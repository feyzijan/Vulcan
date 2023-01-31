#include "General_Good.hpp"
#include "Firm_Agent.hpp"


General_Good::General_Good(Firm_Agent *  seller_pointer, float seller_price, int seller_quantity)
{
    pSeller = seller_pointer;
    price = seller_price;
    quantity = seller_quantity;
}






