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
long long Capital_Goods_Market::Get_Cost_For_Given_Quantity(long long q_desired){
    int q_bought_total = 0;
    double total_price = 0;

    if (!cap_goods_list.empty()) {
        for(auto i=cap_goods_list.begin(); i!=cap_goods_list.end();i++){
            int q = (*i)->Get_Quantity(); 
            float price = (*i)->Get_Price();
            q_bought_total += q; // current quantity we have "bought"
            if(q_bought_total >= q_desired){ // we have bought enough
                q = q_desired - q_bought_total; // quantity of this specific good we are "buying"
                q_bought_total = q_desired;
            }
            total_price += price * q; // total price we will need to pay
            if(q_bought_total==q_desired){
                return  static_cast<long long>(total_price); 
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

long long* Capital_Goods_Market::Buy_Capital_Goods(long long q_desired){
    long long q_bought_total = 0; // quantity the firm is purchasing
    double total_price = 0; // total price paid

    if (n_total_goods == 0){
        long long* arr = new long long[2];
        arr[0] = 0;
        arr[1] = 0;
        return arr;
    } else{

        for (vector<Capital_Good*>::iterator it = cap_goods_list.begin(); it != cap_goods_list.end(); ++it) 
        { // Loop through the capital goods list
            Capital_Good* cap_good = *it; // select current good
            long long q_good_on_market = cap_good->Get_Quantity();
            long long q_good_bought = 0; // how much of this one good we are buying
            double price = static_cast<double>(cap_good->Get_Price()); 
            if (q_good_on_market > 0) // There is smt to buy
            {
                if (q_bought_total + q_good_on_market >= q_desired) // This posting is enough to satisfy all our demand
                {  
                    q_good_bought = q_desired - q_bought_total; // We buy only enough to satisfy our demand
                    q_bought_total = q_desired; // all demand is satisfied
                    
                    cap_good->Set_Quantity(q_good_on_market - q_good_bought); // Deduct quantity from the original good on the market
                    n_total_goods -= q_good_bought; // Deduct from the aggreate market quantity 

                    total_price += price * q_good_bought; // Update total price paid

                } else { // There isn't enough to satisfy our demand, so we will buy all and move on
                    q_good_bought = q_good_on_market; // We buy all that is available
                    q_bought_total += q_good_bought; // Update number of goods purchased by firm

                    cap_good->Set_Quantity(0); // Deduct quantity from the original good on the market 
                    n_total_goods -= q_good_on_market; // Deduct from the aggreate market quantity

                    total_price += price * q_good_bought; // Update total price paid
                }


                // We satisfied our demand or the shop is now empty so lets return
                if (q_bought_total == q_desired || n_total_goods == 0 ) 
                {
                    long long* arr = new long long[2];  // allocate array of size 2 on the heap
                    arr[0] = q_bought_total; 
                    arr[1] = static_cast<long long>(total_price); 
                    return arr;
                } else {
                    continue;
                }
            } else { // this good is all sold out, so the above checks are not made
                continue;
            }
        } //  We have looped through the entire market, so return whatever we have
        long long* arr = new long long[2]{q_bought_total, static_cast<long long>(total_price)};
        return arr;
    }
}



/* Update price level fo the market */
void Capital_Goods_Market::Update_Price_Level(){
    n_total_goods = 0;
    double total_weighed_price = 0.0;
    for(auto i=cap_goods_list.begin(); i!=cap_goods_list.end();i++){
        long long n = (*i)->Get_Quantity();
        if (n <0){
                cout << "ERROR in Update_Price_Level in Cap market, n : " << n << endl;
            }
        n = max(n, static_cast<long long>(1)); // assume at least 1 good exists so we can calculate the price level if the market is empty
        
        float p = (*i)->Get_Price();
        n_total_goods += n;
        total_weighed_price += p * n;
    }
    price_level = static_cast<float>(total_weighed_price/n_total_goods);
    if ( total_weighed_price <0 || price_level <0){
        cout << "ERROR in Update_Price_Level in Cap market, sector_price_level: " << price_level << " total_weighed_price: " << total_weighed_price << endl;
    }
}



/* Function to reset market, emptying the list of goods
*/
void Capital_Goods_Market::Reset_Market(){
    cap_goods_list.clear();
    n_total_goods = 0;
    total_weighed_price = 0;
    price_level = 0.0;
}




/* Printing 
*/
void Capital_Goods_Market::Print(){
    cout << "Capital Goods Market: " << endl;
    cout << "\tAverage price level: " << price_level << " with total n_goods: " << n_total_goods << endl;
}