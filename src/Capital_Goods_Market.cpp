#include "Capital_Goods_Market.hpp"


/* Constructor
*/
Capital_Goods_Market::Capital_Goods_Market(){
    n_total_goods = 0;
    total_weighed_price = 0;
    price_level = 0.0;

}
//----------------------------------------------
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

/* Function to return how much it would cost to buy q number of goods
TODO: Make this more efficient, perhaps return array for q[0,10]
*/
int Capital_Goods_Market::Get_Cost_For_Given_Quantity(int q_desired){
    int q_current = 0;
    float total_price = 0;
    float average_price = 0;
    for(auto i=cap_goods_list.begin(); i!=cap_goods_list.end();i++){
        int q = (*i)->Get_Quantity();
        float price = (*i)->Get_Price();
        q_current += q;
        if(q_current >= q_desired){ 
            q = q_desired - q_current;
            q_current = q_desired;
        }
        total_price += price * q;
        average_price = total_price / q_current;
        if(q_current==q_desired){
            return average_price*q_current;
        } else{
            continue;
        }
    }
    return average_price*q_current;// If we get here, we have not found enough goods
}

/* Buy Capital goods and return the quantity bought and price paid
TODO: Complete Function
TODO: The above function makes some of this redundant, as we already know the cost of
buying n goods, so simplify this
TODO: Check how to properly return a vector of capital good pointers, memorywise
*/
std::vector<Capital_Good*> Capital_Goods_Market::Buy_Capital_Goods(int q_desired){
    std::vector<Capital_Good*> sold_goods; // Unsure if this is the correct type of declaration
    int q_current = 0;
    float total_price = 0;
    float average_price = 0;
    for(auto i=cap_goods_list.begin(); i!=cap_goods_list.end();i++){
        int q = (*i)->Get_Quantity();
        int q_original = q;
        float price = (*i)->Get_Price();
        q_current += q;
        if(q_current >= q_desired){ 
            q = q_desired - q_current;
            q_current = q_desired;
        }
        if (q >0){
            // Add q number of these goods to the vector we have
            Capital_Good* sold_good = new Capital_Good( (*(*i))); // Unsureif this copies correctly
            sold_good->Update_Quantity(-q_original + q);
            sold_goods.push_back(sold_good);
            // Deduct quantity from the original good on the market
            (*i)->Update_Quantity(-q);
        }
        if (q_current == q_desired){
            return sold_goods;
        } else{
            continue;
        }
    }
}



//----------------------------------------------
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