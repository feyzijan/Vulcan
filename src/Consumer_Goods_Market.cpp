#include "Consumer_Goods_Market.hpp"


Consumer_Goods_Market::Consumer_Goods_Market(){
    n_total_goods = 0;
    total_weighed_price = 0;
    price_level = 0.0;

}


/* Todo:
Function that returns the average weighed consumer good price
*/
float Consumer_Goods_Market::Get_Price_Level()
{
    return price_level;
}


/* Function to add a consumer good to the market
Price level is updated as this is done
*/

void Consumer_Goods_Market::Add_Consumer_Good_To_Market(Consumer_Good * cons_good)
{
    cons_goods_list.push_back(cons_good);
    int q = cons_good->Get_Quantity();
    int p = cons_good->Get_Price();
    n_total_goods += q;
    total_weighed_price += p*q;
    price_level = (float)total_weighed_price/(float)n_total_goods;
}