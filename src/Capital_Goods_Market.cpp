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
*/
int Capital_Goods_Market::Get_Cost_For_Given_Quantity(int q_desired){
    int q_current = 0;
    float total_price = 0;

    if (!cap_goods_list.empty()) {
        for(auto i=cap_goods_list.begin(); i!=cap_goods_list.end();i++){
            int q = (*i)->Get_Quantity(); 
            float price = (*i)->Get_Price();
            q_current += q; // current quantity we have "bought"
            if(q_current >= q_desired){ // we have bought enough
                q = q_desired - q_current; // quantity of this specific good we are "buying"
                q_current = q_desired;
            }
            total_price += price * q; // total price we will need to pay
            if(q_current==q_desired){
                return  total_price; 
            } else{
                continue;
            }
        }
    }
    cout << "Capital_Goods_Market::Get_Cost_For_Given_Quantity: There is not enough capital goods to meet demand" << endl;
    return total_price;// If we get here, we have not found enough goods
}


/* New simpler method to buy capital goods
*/

int* Capital_Goods_Market::Buy_Capital_Goods(int q_desired){
    int q_current = 0; // quantity the firm is purchasing
    float total_price = 0; // total price paid

    if (n_total_goods ==0){
        int* arr = new int[2];
        arr[0] = 0;
        arr[1] = 0;
        return arr;
    } else{

        for (vector<Capital_Good*>::iterator it = cap_goods_list.begin(); it != cap_goods_list.end(); ++it) 
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
            } else { // this good is all sold out, so the above checks are not made
                continue;
            }
        } //  We have looped through the entire market, so return whatever we have
        int* arr = new int[2]{q_current, int(total_price)};
        return arr;
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