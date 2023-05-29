#include "Consumer_Goods_Market.hpp"

/* Constructor
*/
Consumer_Goods_Market::Consumer_Goods_Market(){
    n_total_goods = 0;
    price_level = 0.0;
    for (float i = 0; i < emission_sensitivity_max + emission_sensitivity_threshold; i += emission_sensitivity_threshold){
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
void Consumer_Goods_Market::Divide_Goods_Into_Sectors(){
    
    cout << "Divind consumer goods into " << sector_count << " sectors" << endl;
    // Create the pairs to store the goods ** Note that i starts from 1
    for (int i = 0; i < sector_count; i++){
        cons_good_list_by_sector.push_back(std::make_pair(i, vector<Consumer_Good*>()));
    }

    // Loop through the cons_goods_list and add each good to the correct sector
    // May be slow but this is only done once at t = 0
    // *** The sector id's used below start from 1
    for (auto i = cons_goods_list.begin(); i != cons_goods_list.end(); i++){
        int sector_id = (*i)->Get_Sector_ID(); // Get sector of given good
        for (auto j = cons_good_list_by_sector.begin(); j != cons_good_list_by_sector.end(); j++){ // find matching list
            if (sector_id == (*j).first){
                (*j).second.push_back(*i);
            }
        }
    }
}


/* Divide the market into different brackets by their associated emission sensitivity
and sort each one by emission adjusted prices
*/
void Consumer_Goods_Market::Divide_Goods_Into_Emission_Adjusted_Price_Levels(){
    // Loop through each element of the default_emission_sensitivites vector, create an entry in the cons_goods_by_emission_adj_price
    // where the key is the sensitivity and the value is a copy of the cons_good_list_by_sector vector 

    for (float sensitivity : default_emission_sensitivities) {
        cons_goods_by_emission_adj_price[sensitivity] = cons_good_list_by_sector;
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
    // Loop through each entry of the  cons_goods_by_emission_adj_price map, and sort the associated vector of pairs by emission adjsuted price
    for (auto& sensitivity_and_sector : cons_goods_by_emission_adj_price) {
        // The second element of the pair is the vector of pairs of sector and Consumer_Good pointers
        vector<pair<int, vector<Consumer_Good*>>>& sector_and_goods = sensitivity_and_sector.second;

        // Loop through each sector
        for (auto& sector_and_goods : sector_and_goods) {
            // The second element of the pair is the vector of Consumer_Good pointers
            vector<Consumer_Good*>& goods = sector_and_goods.second;

            // Sort the goods vector by emission adjusted price
            std::sort(goods.begin(), goods.end(),
                [sensitivity_and_sector](Consumer_Good* a, Consumer_Good* b) {
                    return a->Get_Emission_Adjusted_Price(sensitivity_and_sector.first) < b->Get_Emission_Adjusted_Price(sensitivity_and_sector.first);
                });
        }
    }
}

/* Function to buy goods from each consumer sector based on emission sensitivities
TO DO: Edit this to work
*/
tuple<vector<long long>, vector<long long>, vector<long long>> Consumer_Goods_Market::Buy_Consumer_Goods_By_Sector_And_Emission(
    const vector<long long>& spending_array, const vector<float>& emission_sensitives_array){
    
    // Initialize vectors to be returned
    vector<long long> remaining_budget_by_sector; 
    vector<long long> quantity_bought_by_sector;
    vector<long long> emission_by_sector;

    //long long total_spending = 0;

    // loop through each sector ** i starts from 1!
    for (int i = 0; i < spending_array.size(); i++) {

        // Round the emission sens value to the nearest threshold, i.e. nearest multiple of 0.05
        float emission_sensitivity = roundf(emission_sensitives_array[i] * 20.0) / 20.0;

        // Select the appropriate sorted goods list - index by sensitivity and sector id
        vector<Consumer_Good*>& goods_for_sector = cons_goods_by_emission_adj_price[emission_sensitivity][i].second;

        // Sector specific local variables
        long long sector_budget = spending_array[i];  // Amount to spend in this sector
        double sector_budget_remaining = sector_budget; // Amount leftover
        long long sector_quantity_bought = 0;
        double sector_emissions = 0;
        for(Consumer_Good* pgood : goods_for_sector){ // Loop through the goods list, from cheapest to most expensive
            long long q = pgood->Get_Quantity();
            float p = pgood->Get_Price();
            long long n = sector_budget_remaining/p; // How much the household can afford to buy from this one listing

            if (n > q){ // Household can afford to buy all the goods, demand likely not satisfied
                n = q; // buy all the goods
                pgood->Add_Quantity(-n); // update the quantity of the good
                sector_quantity_bought += n; // update the quantity bought
                sector_budget_remaining -= n*p; // update the remaining budget
                sector_emissions += n*pgood->Get_Unit_Emissions(); // update the emissions
            } else if (n==0){ 
                break; // Household can no longer afford to buy anything -  exit loop
            } else { // Household can't buy q goods but rather only n : n<=q so household will run out of budget after this purchase
                pgood->Add_Quantity(-n);
                sector_quantity_bought += n;
                sector_budget_remaining -= n*p;
                sector_emissions += n* pgood->Get_Unit_Emissions(); // update the emissions
                break; // exit loop
            }
        }
        // Update the global variables that track values for each sector
        remaining_budget_by_sector.push_back(sector_budget_remaining);
        quantity_bought_by_sector.push_back(sector_quantity_bought);
        emission_by_sector.push_back(static_cast<long long>(sector_emissions)); // convert double to long
        //total_spending += sector_budget - sector_budget_remaining;
    }   

    tuple<vector<long long>, vector<long long>, vector<long long>> result = make_tuple(remaining_budget_by_sector, quantity_bought_by_sector, emission_by_sector);
    return result;
}




/* Update the price level of the market by sector
*/
void Consumer_Goods_Market::Update_Price_Level(){
    // Loop through the cons_good_list_by_sector vector of pairs, calculating the weighted price for each sector
    // store these in order in the price_level_by_sector vector

    price_level_by_sector.clear();
    n_goods_by_sector.clear();
    price_level = 0;

    // Loop through the sectors 
    for (int i = 0; i < cons_good_list_by_sector.size(); i++) { 
        long long n_total_goods = 0;
        double total_weighed_price = 0;
        vector<Consumer_Good*>* pgoods_for_sector = &(cons_good_list_by_sector[i].second); // Get the goods for this sector

        for(Consumer_Good* pgood : *pgoods_for_sector){ // Loop through the goods list, from cheapest to most expensive
            int q = pgood->Get_Quantity();
            float p = pgood->Get_Price();
            n_total_goods += q;
            total_weighed_price += float(p*q);
        }
        price_level_by_sector.push_back(total_weighed_price/(float)n_total_goods);
        n_goods_by_sector.push_back(n_total_goods);
    }

    // Calculate the price level for the whole market

}




/* Reset the market
*/
void Consumer_Goods_Market::Reset_Market(){
    cons_goods_list.clear();
    n_total_goods = 0;
    price_level = 0.0;
}