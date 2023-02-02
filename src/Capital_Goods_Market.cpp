#include "Capital_Goods_Market.hpp"


/* Constructor
*/
Capital_Goods_Market::Capital_Goods_Market(){
    n_total_goods = 0;
    total_weighed_price = 0;
    price_level = 0.0;

}

// ----------- Market operations

/* Function to add a capital good to marke
Price level is updated as well
*/
void Capital_Goods_Market::Add_Capital_Good_To_Market(Capital_Good * cap_good)
{
    cap_goods_list.push_back(cap_good);
    int q = cap_good->Get_Quantity();
    int p = cap_good->Get_Price();
    n_total_goods += q;
    total_weighed_price += float(p*q);
    price_level = (float)total_weighed_price/(float)n_total_goods;
}


/* Sort the market by price
*/
void Capital_Goods_Market::Sort_Capital_Goods_By_Price()
{
    std::sort(cap_goods_list.begin(), cap_goods_list.end(), 
    [](Capital_Good* a, Capital_Good* b) { 
    return a->Get_Price() < b->Get_Price(); });
}

// Printing and debugging

/* Print all the goods in the market
*/
void Capital_Goods_Market::Print() {
    std::cout << "Capital Goods Market at " << this << std::endl;
    std::cout << "-------------------" << std::endl;
    std::cout << "Price level: " << price_level << std::endl;
    std::cout << "Total number of goods: " << n_total_goods << std::endl;
    std::cout << "Total weighted price: " << total_weighed_price << std::endl;
    std::cout << "-------------------" << std::endl;
    std::cout << "Goods in the market: " << std::endl;
    for (int i = 0; i < cap_goods_list.size(); i++)
    {
        std::cout << "Good " << i << std::endl;
        cap_goods_list[i]->Print();
    }
    std::cout << "-------------------" << std::endl;

}