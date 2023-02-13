#include "Consumer_Good.hpp"



Consumer_Good::Consumer_Good(Consumer_Firm_Agent *  seller_pointer, float seller_price, int seller_quantity)
{
    pSeller = seller_pointer;
    price = seller_price;
    quantity = seller_quantity;
}

void Consumer_Good::Print(){
    cout << "Consumer Good at address: " << this << endl;
    cout << "Price: " << price  << " Quantity: " << quantity << endl;
    cout << "Seller: " << pSeller << endl;

}







