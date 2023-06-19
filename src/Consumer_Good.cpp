#include "Consumer_Good.hpp"


/* Constructor with just seller, price, and quantity*/
Consumer_Good::Consumer_Good(Consumer_Firm_Agent *  seller_pointer, float seller_price, long long seller_quantity)
{
    pSeller = seller_pointer;
    price = seller_price;
    quantity = seller_quantity;
    sector_id = 0;
}

/* Constructor with just seller, price, quantity, and emission*/
Consumer_Good::Consumer_Good(Consumer_Firm_Agent *  seller_pointer, float seller_price, long long seller_quantity, float emissions_per_unit){
    pSeller = seller_pointer;
    price = seller_price;
    quantity = seller_quantity;
    sector_id = 0;
    unit_emissions = emissions_per_unit;
}

/* Constructor with sector*/
Consumer_Good::Consumer_Good(Consumer_Firm_Agent *  seller_pointer, float seller_price, long long seller_quantity, int seller_sector)
{
    pSeller = seller_pointer;
    price = seller_price;
    quantity = seller_quantity;
    sector_id = seller_sector;
}

/* Constructor with sector + emissions*/
Consumer_Good::Consumer_Good(Consumer_Firm_Agent *  seller_pointer, float seller_price, long long seller_quantity, int seller_sector, float emissions_per_unit)
{
    pSeller = seller_pointer;
    price = seller_price;
    quantity = seller_quantity;
    sector_id = seller_sector;
    unit_emissions = emissions_per_unit;
}








