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
            return average_price*q_current; // return total price
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
std::vector<Capital_Good*>* Capital_Goods_Market::Buy_Capital_Goods(int q_desired){
    std::vector<Capital_Good*>* sold_good_list = new vector<Capital_Good*>(); // Vector of pointers to sold goods
    int q_current = 0; // quantity the firm is purchasing
    float total_price = 0;
    float average_price = 0;
    
    for(auto cap_good : cap_goods_list){
        int q_on_market = cap_good->Get_Quantity();
        int q_sold = 0;
        float price = cap_good->Get_Price();
        if ( q_on_market > 0) {
            if( q_current + q_on_market >= q_desired){  // This posting is enough to satisfy all our demand
                q_sold = q_desired - q_current; // How much we will buy
                q_current  = q_desired; // all demand is satisfied
                // Add good to our list
                Capital_Good* sold_good = new Capital_Good(*cap_good);
                sold_good->Set_Quantity(q_sold); // Set quantity bought properly
                sold_good_list->push_back(sold_good);
                // Deduct quantity from the original good on the market
                cap_good->Update_Quantity(-q_sold); 
            } else if (q_on_market >0){ // Not enough to satisfy our demand, so we will buy all and move on
                Capital_Good* sold_good = new Capital_Good(*cap_good); // Add good to our list  - Unsureif this copies correctly
                q_current += q_on_market; // Update number of goods purchased by firm
                //sold_good->Update_Quantity(q_on_market);
                sold_good_list->push_back(sold_good);
                // Deduct quantity from the original good on the market 
                cap_good->Set_Quantity(0); // All of it has been bouht
            } 
        }
              
        if (q_current == q_desired){
            return sold_good_list;
        } else{
            continue;
        }
    }
}

/* New simpler method to buy capital goods
*/

int* Capital_Goods_Market::Buy_Capital_Goods_Simple(int q_desired){
    int q_current = 0; // quantity the firm is purchasing
    float total_price = 0; // total price paid

    if (n_total_goods ==0){
        int* arr = new int[2];
        arr[0] = 0;
        arr[1] = 0;
        return arr;
    } else{

        for (std::vector<Capital_Good*>::iterator it = cap_goods_list.begin(); it != cap_goods_list.end(); ++it) 
        { // Loop through the capital goods list
            Capital_Good* cap_good = *it; // select current good
            int q_on_market = cap_good->Get_Quantity();
            int q_sold = 0; // how much of this one good we are buying
            float price = cap_good->Get_Price(); 
            if (q_on_market > 0) 
            {
                if (q_current + q_on_market >= q_desired) // This posting is enough to satisfy all our demand
                {  
                    q_sold = q_desired - q_current; // We buy only enough to satisfy our demand
                    q_current = q_desired; // all demand is satisfied
                    
                    cap_good->Update_Quantity(-q_sold); // Deduct quantity from the original good on the market
                    n_total_goods -= q_sold; // Deduct quantity from market

                } else { // Not enough to satisfy our demand, so we will buy all and move on
                    q_current += q_on_market; // Update number of goods purchased by firm
                    cap_good->Set_Quantity(0); // Deduct quantity from the original good on the market 
                    n_total_goods -= q_on_market;
                }

                if (q_current == q_desired || n_total_goods == 0 ) // We satisfied our demand or the shop is now empty so lets return
                {
                    int* arr = new int[2];  // allocate array of size 2 on the heap
                    arr[0] = q_current;  // store first integer in array
                    arr[1] = total_price;  // store second integer in array
                    return arr;
                } else {
                    continue;
                }
            } else { // this good is all sold out
                continue;
            }

        }
    }

}



/* Update price level fo the market */
void Capital_Goods_Market::Update_Price_Level(){
    n_total_goods = 0;
    total_weighed_price = 0;
    for(auto i=cap_goods_list.begin(); i!=cap_goods_list.end();i++){
        int q = (*i)->Get_Quantity();
        int p = (*i)->Get_Price();
        n_total_goods += q;
        total_weighed_price += float(p*q);
    }
    price_level = (float)total_weighed_price/(float)n_total_goods;
}



/* Function to reset market, emptying the list of goods
*/
void Capital_Goods_Market::Reset_Market(){
    cap_goods_list.clear();
    n_total_goods = 0;
    total_weighed_price = 0;
    price_level = 0.0;
}



//----------------------------------------------
// Printing and debugging

/* Print all the goods in the market
*/
void Capital_Goods_Market::Print() {
    std::cout << "Capital Goods Market at " << this << std::endl;
    std::cout << "Price level: " << price_level << std::endl;
    std::cout << "Total number of goods: " << n_total_goods << std::endl;
    std::cout << "Total weighted price: " << total_weighed_price << std::endl;
    std::cout << "-------------------" << std::endl;

/*     std::cout << "Goods in the market: " << std::endl;
    for (int i = 0; i < cap_goods_list.size(); i++)
    {
        std::cout << "Good " << i << std::endl;
        cap_goods_list[i]->Print();
    }
    std::cout << "-------------------" << std::endl; */

}