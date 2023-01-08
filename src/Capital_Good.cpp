#include "Capital_Good.hpp"



Capital_Good::Capital_Good(Capital_Firm_Agent *  seller_pointer, int price, int quantity)
{
    pSeller = seller_pointer;
    this->price = price;
    this->quantity = quantity;
}






