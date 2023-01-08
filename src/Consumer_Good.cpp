#include "Consumer_Good.hpp"



Consumer_Good::Consumer_Good(Consumer_Firm_Agent *  seller_pointer, int seller_price, int seller_quantity)
{
    pSeller = seller_pointer;
    this->price = seller_price;
    this->quantity = seller_quantity;
}






