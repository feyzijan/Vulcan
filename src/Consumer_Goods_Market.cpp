#include "Consumer_Goods_Market.hpp"

/* Constructor
*/
Consumer_Goods_Market::Consumer_Goods_Market(){
    n_total_goods = 0;
    total_weighed_price = 0;
    price_level = 0.0;

}

// ------------------ Market operations

/* Function to add a consumer good to market 
Price level is updated as well
*/
void Consumer_Goods_Market::Add_Consumer_Good_To_Market(Consumer_Good * cons_good)
{
    //cout << "Cons good market adding good " << cons_good << endl;
    cons_goods_list.push_back(cons_good);
    //cout << "Cons good market added good " << cons_good << endl;
    int q = cons_good->Get_Quantity();
    float p = cons_good->Get_Price();
    n_total_goods += q;
    total_weighed_price += float(p*q);
    price_level = (float)total_weighed_price/(float)n_total_goods;
    //cout << "new price level " << price_level;
}


/* Sort the market by price
*/
void Consumer_Goods_Market::Sort_Consumer_Goods_By_Price()
{
    std::sort(cons_goods_list.begin(), cons_goods_list.end(), 
    [](Consumer_Good* a, Consumer_Good* b) { 
    return a->Get_Price() < b->Get_Price(); });
}

/* Satisfy the household purccahse budget with as many goods as possible
Loop through the market, sell the household as much goods as it can afford, return 
remaining budget when it can no longer afford to buy anything else
TODO: Test loop and simplify code, evaluate runtime
TODO: Doesn't return quantity, maybe return array that includes this
*/
int Consumer_Goods_Market::Buy_Consumer_Goods(int budget){
    int remaining_budget = budget;
    int quantity_bought = 0;
    for(auto i=cons_goods_list.begin(); i!=cons_goods_list.end();i++){
        int q = (*i)->Get_Quantity();
        float p = (*i)->Get_Price();
        int n = remaining_budget/p; // How much the household can afford to buy
        if (n>=q){ // Household buys all the goods, likely not satisfied
            n = q;
            (*i)->Update_Quantity(-n);
            quantity_bought += n;
            remaining_budget -= n*p;
        } else if (n==0) // Household can no longer afford to buy anything
        {
            break; // exit loop
        } else{ // Household can't buy all, so has run out of budget
            (*i)->Update_Quantity(-n);
            remaining_budget -= n*p;
             quantity_bought += n;
            break; // exit loop
        }
        return remaining_budget;
    }
}


// Printing and debugging

/* Print all the goods in the market
*/
void Consumer_Goods_Market::Print(){
    std::cout << "Consumer Goods Market at " << this << std::endl;
    std::cout << "-------------------" << std::endl;
    std::cout << "Price level: " << price_level << std::endl;
    std::cout << "Total number of goods: " << n_total_goods << std::endl;
    std::cout << "Total weighted price: " << total_weighed_price << std::endl;
    std::cout << "-------------------" << std::endl;
    std::cout << "Goods in the market: " << std::endl;
    for (int i = 0; i < cons_goods_list.size(); i++)
    {
        std::cout << "Good " << i << std::endl;
        cons_goods_list[i]->Print();
    }
    std::cout << "-------------------" << std::endl;
}