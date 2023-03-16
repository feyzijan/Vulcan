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
    cons_goods_list.push_back(cons_good);
}

/*  Create pairs of cons_good_list_by_sector for each sector_id in the sector_id_list
    The pair contains the sector_id and a vector of consumer goods
    The vector of consumer goods can be initially empty
*/
void Consumer_Goods_Market::Divide_Goods_Into_Sectors(int* sector_id_list, int n_sectors){

    
    // Create each pair
    for (int i = 0; i < n_sectors; i++){
        cons_good_list_by_sector.push_back(std::make_pair(sector_id_list[i], std::vector<Consumer_Good*>()));
    }

    // Loop through the cons_goods_list and add each good to the correct sector
    // May be slow but only done once
    for (auto i = cons_goods_list.begin(); i != cons_goods_list.end(); i++){
        int sector_id = (*i)->Get_Sector_ID();
        for (auto j = cons_good_list_by_sector.begin(); j != cons_good_list_by_sector.end(); j++){
            if (sector_id == (*j).first){
                (*j).second.push_back(*i);
            }
        }
    }
}


/* Sort the market by price
*/
void Consumer_Goods_Market::Sort_Consumer_Goods_By_Price()
{
    std::sort(cons_goods_list.begin(), cons_goods_list.end(), 
    [](Consumer_Good* a, Consumer_Good* b) { 
    return a->Get_Price() < b->Get_Price(); });
}


/* Sort the market in each sector by price
*/
void Consumer_Goods_Market::Sort_Cons_Goods_By_Sector_By_Price() 
{
        // Iterate through each element in cons_good_list_by_sector
        for (auto& sector_and_goods : cons_good_list_by_sector) {
            // The second element of the pair is the vector of Consumer_Good pointers
            std::vector<Consumer_Good*>& goods = sector_and_goods.second;

            // Sort the goods vector by price
            std::sort(goods.begin(), goods.end(),
                [](Consumer_Good* a, Consumer_Good* b) {
                    return a->Get_Price() < b->Get_Price();
                });
        }
}






/* Satisfy the household purccahse budget with as many goods as possible
Loop through the market, sell the household as much goods as it can afford, return 
remaining budget when it can no longer afford to buy anything else
TODO: Test loop and simplify code, evaluate runtime
TODO: Doesn't return quantity, maybe return array that includes this
*/
std::pair<int, int> Consumer_Goods_Market::Buy_Consumer_Goods(int budget){
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
        } else{ // Household can't buy all, so will run out of budget after this purchase
            (*i)->Update_Quantity(-n);
            remaining_budget -= n*p;
            quantity_bought += n;
            break; // exit loop
        }
    }
    // Update price level and quantity for the market
    return std::make_pair(remaining_budget, quantity_bought);
}



/* Function to buy goods from each consumer sector
 The function receives an array with float values corresponding to the spending share of each sector from 1 to n
 Demand from each sector is attempted to be satisfied - this is usually not completely met because we can't buy fractions of goods
    The function returns a tuple with the following elements:
        1. A vector with the remaining budget for each sector
        2. A vector with the quantity bought for each sector
        3. The remaining budget after buying from all sectors
        4. The total quantity bought from all sectors
*/
    pair<vector<float>, vector<int>> Consumer_Goods_Market::Buy_Consumer_Goods_By_Sector(int budget, const vector<int>& spending_array ){
    
    
    vector<float> remaining_budget_by_sector; // initialize remaining budget vector
    vector<int> quantity_bought_by_sector; // initialize quantity bought vector

    int total_spending = 0;

    // loop through each sector
    for (int i = 0; i < spending_array.size(); ++i) {
        // find the goods for this sector - which should be sorted
        std::vector<Consumer_Good*>& goods_for_sector = cons_good_list_by_sector[i].second;

        // calculate the amount to spend in this sector
        int sector_budget = spending_array[i];

        // buy goods from this sector
        float sector_budget_remaining = sector_budget;
        int sector_quantity_bought = 0;
        for(Consumer_Good* pgood : goods_for_sector){ // Loop through the goods list, from cheapest to most expensive
            int q = pgood->Get_Quantity();
            float p = pgood->Get_Price();
            int n = sector_budget_remaining/p; // How much the household can afford to buy from this one listing

            if (n>=q){ // Household can buy all the goods, likely not satisfied
                n = q; // buy all the goods
                pgood->Update_Quantity(-n); // update the quantity of the good
                sector_quantity_bought += n; // update the quantity bought
                sector_budget_remaining -= n*p; // update the remaining budget
            } else if (n==0){ 
                break; // Household can no longer afford to buy anything -  exit loop
            } else { // Household can't buy q goods but rather only n , so will run out of budget after this purchase
                pgood->Update_Quantity(-n);
                sector_quantity_bought += n;
                sector_budget_remaining -= n*p;
                break; // exit loop
            }
        }
        remaining_budget_by_sector.push_back(sector_budget_remaining);
        quantity_bought_by_sector.push_back(sector_quantity_bought);
        total_spending += sector_budget - sector_budget_remaining;
    }   

    pair<vector<float>, vector<int>> result = make_pair(remaining_budget_by_sector, quantity_bought_by_sector);
    return result;
}




/* Update the price level of the market
*/
void Consumer_Goods_Market::Update_Price_Level(){
    n_total_goods = 0;
    total_weighed_price = 0;
    for(auto i=cons_goods_list.begin(); i!=cons_goods_list.end();i++){
        int q = (*i)->Get_Quantity();
        float p = (*i)->Get_Price();
        n_total_goods += q;
        total_weighed_price += float(p*q);
    }
    price_level = (float)total_weighed_price/(float)n_total_goods;
}

/* Reset the market
*/
void Consumer_Goods_Market::Reset_Market(){
    cons_goods_list.clear();
    n_total_goods = 0;
    total_weighed_price = 0;
    price_level = 0.0;
}


// Printing and debugging

/* Print all the goods in the market
*/
void Consumer_Goods_Market::Print(){
    std::cout << "Consumer Goods Market at " << this << std::endl;
    std::cout << "Price level: " << price_level << std::endl;
    std::cout << "Total number of goods: " << n_total_goods << std::endl;
    std::cout << "Total weighted price: " << total_weighed_price << std::endl;
    std::cout << "-------------------" << std::endl;
    
    /*std::cout << "Goods in the market: " << std::endl;
     for (int i = 0; i < cons_goods_list.size(); i++)
    {
        std::cout << "Good " << i << std::endl;
        cons_goods_list[i]->Print();
    }
    std::cout << "-------------------" << std::endl; */
}