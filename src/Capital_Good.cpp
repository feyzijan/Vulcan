#include "Capital_Good.hpp"


/* Constructor
*/
Capital_Good::Capital_Good(Capital_Firm_Agent *  seller_pointer, float seller_price, int seller_quantity,int life_span)
{
    pSeller = seller_pointer;
    price = seller_price;
    value = seller_price* seller_quantity;
    quantity = seller_quantity;
    depreciation_period = life_span;
    sold_date = global_date;
    expiry_date = sold_date + depreciation_period;
    sector_id = 0;
}

/* Copy constructor*/
Capital_Good::Capital_Good(const Capital_Good& other){
    pSeller = other.pSeller;
    price = other.price;
    value = other.value;
    quantity = other.quantity;
    depreciation_period = other.depreciation_period;
    sold_date = global_date;
    expiry_date = sold_date + depreciation_period;
}

/* Depreciate by selling_price/depreciation_period * quantity
NOTE: Depreciation may be off by 1 timestep because the division may not be exact, but this is not a big deal
*/
void Capital_Good::Depreciate(){
    value -= price/(depreciation_period*quantity);
    if (value <= 0){ depreciated = true;}
}




