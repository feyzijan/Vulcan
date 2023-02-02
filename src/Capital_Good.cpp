#include "Capital_Good.hpp"


/* Constructor
*/
Capital_Good::Capital_Good(Capital_Firm_Agent *  seller_pointer, float seller_price, int seller_quantity,int life_span)
{
    pSeller = seller_pointer;
    price = seller_price;
    value = seller_price;
    quantity = seller_quantity;
    depreciation_period = life_span;
    sold_date = global_date;
    expiry_date = sold_date + depreciation_period;
}


/* Printing
*/
void Capital_Good::Print() const{
    cout << "Capital Good at address: " << this << endl;
    cout << "Seller: " << pSeller << endl;
    cout << "Price: " << price  << " Quantity: " << quantity << endl;
    cout << "Value: " << value << " Depreciation Period: " << depreciation_period << endl;
    cout << "Sold Date: " << sold_date << " Expiry Date: " << expiry_date << endl;
}




