#include "Consumer_Goods_Market.hpp"

/* Constructor
*/
Consumer_Goods_Market::Consumer_Goods_Market(){
    n_total_goods = 0;
    total_weighed_price = 0;
    price_level = 0.0;
    for (int i = 0; i < emission_sensitivity_max + emission_sensitivity_threshold; i += emission_sensitivity_threshold){
        default_emission_sensitivities.push_back(i);
    };

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
void Consumer_Goods_Market::Divide_Goods_Into_Sectors(int n_sectors){
    
    // Create each pair
    for (int i = 1; i < n_sectors+1; i++){
        cons_good_list_by_sector.push_back(std::make_pair(i, vector<Consumer_Good*>()));
    }

    // Loop through the cons_goods_list and add each good to the correct sector
    // May be slow but this is only done once at t = 0
    for (auto i = cons_goods_list.begin(); i != cons_goods_list.end(); i++){
        int sector_id = (*i)->Get_Sector_ID();
        for (auto j = cons_good_list_by_sector.begin(); j != cons_good_list_by_sector.end(); j++){
            if (sector_id == (*j).first){
                (*j).second.push_back(*i);
            }
        }
    }
}


/* Sort the market in each sector by price
*/
void Consumer_Goods_Market::Sort_Cons_Goods_By_Sector_By_Price() 
{
        // Iterate through each element in cons_good_list_by_sector
        for (auto& sector_and_goods : cons_good_list_by_sector) {
            // The second element of the pair is the vector of Consumer_Good pointers
            vector<Consumer_Good*>& goods = sector_and_goods.second;

            // Sort the goods vector by price
            std::sort(goods.begin(), goods.end(),
                [](Consumer_Good* a, Consumer_Good* b) {
                    return a->Get_Price() < b->Get_Price();
                });
        }
}


/* Check that the below works
 */
void Consumer_Goods_Market::Sort_Cons_Goods_By_Sector_By_Price_and_Emissions(){
    // Loop through each element of the default_emission_sensitivites vector, create an entry in the cons_goods_by_emission_adj_price
    // where the key is the sensitivity and the value is a copy of the cons_good_list_by_sector vector sorted based on emission adjusted price
    for (int i = 0; i < default_emission_sensitivities.size(); ++i) {
        float sensitivity = default_emission_sensitivities[i]; // Get the sensitivity
        vector<pair<int, vector<Consumer_Good*>>> cons_good_list_by_sector_copy;
        
        for (const auto& sector_and_goods : cons_good_list_by_sector) { // loop through each sector
            const vector<Consumer_Good*>& goods = sector_and_goods.second; // select given set of goods
            vector<Consumer_Good*> goods_copy;  

            // Copy the goods vector
            std::transform(goods.begin(), goods.end(), std::back_inserter(goods_copy),
            [](Consumer_Good* good) {
                return new Consumer_Good(*good); // Deep copy of Consumer_Good object
            });

            // Sort the goods vector by emisison adj price
            std::sort(goods.begin(), goods.end(),
                [sensitivity](const Consumer_Good* a, const Consumer_Good* b) {
                    return a->Get_Emission_Adjusted_Price(sensitivity) < b->Get_Emission_Adjusted_Price(sensitivity);
                });

            // Add the sorted vector to the copy of the cons_good_list_by_sector vector
            cons_good_list_by_sector_copy.emplace_back(sector_and_goods.first, goods_copy);
        }
        cons_goods_by_emission_adj_price[sensitivity] = cons_good_list_by_sector_copy; // Add the sorted vector to the map
    }
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
pair<vector<float>, vector<int>> Consumer_Goods_Market::Buy_Consumer_Goods_By_Sector(int budget, const vector<float>& spending_array ){
    
    
    vector<float> remaining_budget_by_sector; // initialize remaining budget vector
    vector<int> quantity_bought_by_sector; // initialize quantity bought vector

    int total_spending = 0;

    // loop through each sector
    for (int i = 0; i < spending_array.size(); ++i) {
        // find the goods for this sector - which should be sorted
        vector<Consumer_Good*>& goods_for_sector = cons_good_list_by_sector[i].second;

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


/* Function to buy goods from each consumer sector based on emission sensitivities
TO DO: Edit this to work
*/
tuple<vector<float>, vector<int>, vector<int>> Consumer_Goods_Market::Buy_Consumer_Goods_By_Sector_And_Emission(int budget, const vector<float>& spending_array, 
const vector<float>& emission_sensitives_array){
    
    
    vector<float> remaining_budget_by_sector; 
    vector<int> quantity_bought_by_sector;
    vector <int> emisison_by_sector;

    int total_spending = 0;

    // loop through each sector
    for (int i = 0; i < spending_array.size(); ++i) {
        // find the goods for this sector - which should be sorted
        // Select the correct sector and the correct emission
        //vector<Consumer_Good*>& goods_for_sector = cons_good_list_by_sector[i].second;

        // Round this value to the nearest threshold, i.e. nearest multiple of 0.05
        float emission_sensitivity = roundf(emission_sensitives_array[i] * 20) / 20;

        // Select the appropriate goods list
        vector<Consumer_Good*>& goods_for_sector = cons_goods_by_emission_adj_price[emission_sensitives_array[i]][i].second;

        // calculate the amount to spend in this sector
        int sector_budget = spending_array[i];

        // buy goods from this sector
        float sector_budget_remaining = sector_budget;
        int sector_quantity_bought = 0;
        float sector_emissions = 0;
        for(Consumer_Good* pgood : goods_for_sector){ // Loop through the goods list, from cheapest to most expensive
            int q = pgood->Get_Quantity();
            float p = pgood->Get_Price();
            int n = sector_budget_remaining/p; // How much the household can afford to buy from this one listing

            if (n>=q){ // Household can buy all the goods, likely not satisfied
                n = q; // buy all the goods
                pgood->Update_Quantity(-n); // update the quantity of the good
                sector_quantity_bought += n; // update the quantity bought
                sector_budget_remaining -= n*p; // update the remaining budget
                sector_emissions += n*pgood->Get_Unit_Emissions(); // update the emissions
            } else if (n==0){ 
                break; // Household can no longer afford to buy anything -  exit loop
            } else { // Household can't buy q goods but rather only n , so will run out of budget after this purchase
                pgood->Update_Quantity(-n);
                sector_quantity_bought += n;
                sector_budget_remaining -= n*p;
                sector_emissions += n*pgood->Get_Unit_Emissions(); // update the emissions
                break; // exit loop
            }
        }
        remaining_budget_by_sector.push_back(sector_budget_remaining);
        quantity_bought_by_sector.push_back(sector_quantity_bought);
        emisison_by_sector.push_back(int(sector_emissions));
        total_spending += sector_budget - sector_budget_remaining;
    }   

    tuple<vector<float>, vector<int>, vector<int>> result = make_tuple(remaining_budget_by_sector, quantity_bought_by_sector, emisison_by_sector);
    return result;
}




/* Update the price level of the market by sector
*/
void Consumer_Goods_Market::Update_Price_Level(){
    // Loop through the cons_good_list_by_sector vector of pairs, calculating the weighted price for each sector
    // store these in order in the price_level_by_sector vector

    price_level_by_sector.clear();
    n_goods_by_sector.clear();


    for (int i = 0; i < cons_good_list_by_sector.size(); ++i) { // Loop through the sectors
        int n_total_goods = 0;
        int total_weighed_price = 0;
        vector<Consumer_Good*>* pgoods_for_sector = &(cons_good_list_by_sector[i].second); // Get the goods for this sector

        for(Consumer_Good* pgood : *pgoods_for_sector){ // Loop through the goods list, from cheapest to most expensive
            int q = pgood->Get_Quantity();
            float p = pgood->Get_Price();
            n_total_goods += q;
            total_weighed_price += float(p*q);
        }
        price_level_by_sector.push_back((float)total_weighed_price/(float)n_total_goods);
        n_goods_by_sector.push_back(n_total_goods);
    }
}




/* Reset the market
*/
void Consumer_Goods_Market::Reset_Market(){
    cons_goods_list.clear();
    n_total_goods = 0;
    total_weighed_price = 0;
    price_level = 0.0;
}