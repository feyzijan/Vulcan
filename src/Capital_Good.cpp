#include "Capital_Good.hpp"



Capital_Good::Capital_Good(Capital_Firm_Agent *  seller_pointer, float seller_price, int seller_quantity,int date, int duration)
{
    pSeller = seller_pointer;
    price = seller_price;
    value = seller_price;
    quantity = seller_quantity;
    depreciation_period = duration;
    sold_date = date;
    expiry_date = sold_date + depreciation_period;
}






