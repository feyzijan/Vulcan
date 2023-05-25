#include "Consumer_Firm_Agent.hpp"

#include <iostream>

/* Constructors and Destructor
*/
Consumer_Firm_Agent::Consumer_Firm_Agent(float float_vals[2], int int_vals[5]): Firm_Agent::Firm_Agent(float_vals,int_vals)
{
    is_cons_firm = true;

    workers_per_machine = firm_cons_workers_per_machine;
    output_per_machine = firm_cons_productivity;
    unit_good_cost = firm_cons_good_unit_cost;
    inv_depreciation_rate = firm_cons_inv_depr_rate;
    inv_reaction_factor = firm_cons_inv_reaction_factor;
    max_production_climbdown = firm_cons_max_production_climbdown;
    unit_emissions = firm_cons_init_emissions_per_unit;
    
    dividend_ratio_optimist = firm_cons_init_dividend_ratio_optimist;
    dividend_ratio_pessimist =  firm_cons_init_dividend_ratio_pessimist;

    production_current = max(working_capital_inventory * firm_cons_workers_per_machine * firm_cons_productivity,employee_count_desired / firm_cons_workers_per_machine * firm_cons_productivity);
    production_planned = production_current;
    inventory = production_current * target_inv_factor * int_vals[3]; // TODO ADD this as a param
    quantity_sold = inventory *  firm_cons_init_quantity_sold_ratio; 
    average_sale_quantity = quantity_sold;
    revenue_sales = production_current * good_price_current;
    total_income = revenue_sales;
    average_profit = revenue_sales;


    // Emissions - Set default values for now
    unit_emissions = 1; // TODO: Replace with variable
    total_emissions = 0;

    cons_goods_on_market = new Consumer_Good(this, good_price_current,inventory-quantity_sold, unit_emissions);
    goods_on_market = cons_goods_on_market;
    //Send_Goods_To_Market();
    sector_id = 1;
}


//Copy constructor
Consumer_Firm_Agent::Consumer_Firm_Agent(Consumer_Firm_Agent&){}

//------------------------------------------------------------

/* Delete references to the consumer good object on the market produced by this firm 
*/
Consumer_Firm_Agent::~Consumer_Firm_Agent() {

    // Consumer goods
    // Set quantity and seller pointer to 0
    cons_goods_on_market->Set_Quantity(0);
    cons_goods_on_market->Set_Seller_Pointer(nullptr);

}


// ------- Main Loop Methods-----------------


/* Function to depreciate(i.e. destroy) a fraction of the firm's inventory of consumer goods
The depreciation rate is set exogenously in the initialization parameter for all firms
*/
void Consumer_Firm_Agent::Depreciate_Good_Inventory(){
    inventory  = int(float(inventory)*(1.0-firm_cons_inv_depr_rate));
}


/* Increment Firm inventory by the number of machines, productivity per machine,
*/
void Consumer_Firm_Agent::Produce_Goods(){

   Firm_Agent::Produce_Goods();

    // Update the unit_emission_of the newly produced goods
    //*** CHECK DIVISIONS ARE OKAY
    total_emissions += 0;
    total_emissions += production_current * unit_emissions;

    long long new_total_emissions = production_current * unit_emissions - emission_total_allowance;
    long long past_production = inventory - production_current;
    long long past_total_emissions = past_production * unit_emissions_adj;
    unit_emissions_adj = (past_total_emissions + new_total_emissions) / inventory;

    // Update consumer good object to use this new adjusted emission
    cons_goods_on_market->Set_Unit_Emission(unit_emissions_adj);

    // Update the public info board
    pPublic_Info_Board->Update_Consumer_Goods_Production(sector_id, production_current);
    pPublic_Info_Board->Update_Consumer_Goods_Inventory(sector_id, production_planned);
    pPublic_Info_Board->Update_Firm_Emissions_By_Sector(sector_id, new_total_emissions);

}



/* Check sales and update public board*/
void Consumer_Firm_Agent::Check_Sales(){
    Firm_Agent::Check_Sales();
    pPublic_Info_Board->Update_Consumer_Goods_Sale_Quantities(sector_id, quantity_sold);
}


/* Post Produced goods to market - Only do this in initialization period
*/
void Consumer_Firm_Agent::Send_Goods_To_Market(){
    //cout << "cons firm " << this << " sending goods to market" << endl;
    pPublic_Info_Board->Send_Cons_Good_To_Market(cons_goods_on_market);
}

/* Update the goods object via the stored pointer, the market already contains this pointer
*/
void Consumer_Firm_Agent::Update_Goods_On_Market(){
    goods_on_market->Update_Price(good_price_current);
    goods_on_market->Set_Quantity(inventory);
}


void Consumer_Firm_Agent::Random_Experimentation(){
    target_inv_factor *= Uniform_Dist_Float(1.0-firm_cons_rand_desired_inventory_factor_change
    ,1.0 + firm_cons_rand_desired_inventory_factor_change);
    dividend_ratio_optimist *= Uniform_Dist_Float(1.0-firm_cons_rand_dividend_change, 1.0 + firm_cons_rand_dividend_change);
    dividend_ratio_pessimist *= Uniform_Dist_Float(1.0-firm_cons_rand_dividend_change, 1.0 + firm_cons_rand_dividend_change);
}


/* Update sentiment and post to public board*/
void Consumer_Firm_Agent::Update_Sentiment(){
    Firm_Agent::Update_Sentiment();

    bool adopt_majority= Uniform_Dist_Float(0,1)  < firm_cons_rand_sentiment_adoption;
    if(adopt_majority){
        sentiment = (pPublic_Info_Board->Get_Cons_Firm_Sentiment() > 0.50); }

    // Update dividend ratio based on sentiment
    if (sentiment){dividend_ratio = dividend_ratio_optimist;
    } else{dividend_ratio = dividend_ratio_pessimist;}

    // Update the desired inventory?

    pPublic_Info_Board->Update_Cons_firm_sentiment_sum(sentiment);
}


void Consumer_Firm_Agent::Determine_New_Production(){
    
    // Check if price is high relative to the market
    bool price_high = good_price_current >= pPublic_Info_Board->Get_Cons_Sector_Price_Level(sector_id);

    // Check if emissiosn are high relative to the market
    float emission_overshoot = unit_emissions_adj - pPublic_Info_Board->Get_Average_Unit_Emissions_by_Sector(sector_id);
    bool emission_high = emission_overshoot > 0; 

    // Calculate how many offsets you need to buy to reach the average unit emissions
    int emission_offsets_needed = 0;
    // Add the amount we need to buy so that our inventory is at average emissions
    emission_offsets_needed += static_cast<int>(emission_overshoot * inventory);


    good_price_past = good_price_current; // store current price incase we want to see the change
    production_past = production_current;

    bool inventory_high = inventory >= desired_inventory; 
    // Determine randomised price and production change factors
    float price_change =  firm_cons_fixed_price_change + Uniform_Dist_Float(0.0,firm_cons_rand_price_change_upper_limit); 
    float prod_change =  firm_cons_fixed_prod_change + Uniform_Dist_Float(0.0,firm_cons_rand_prod_change_upper_limit); 


    /* Change price, production, and emission based on data
    Cases 1-4: Inventory low == Sales high, so no need to worry about emission
    */

    // Cases 1 & 2 : Inventory low, price low, emissions low or high -> Increase production slightly +  increase price slightly 
    if (!price_high && !inventory_high) {
        production_planned*= (1.0+prod_change/2.0);
        good_price_current *= (1.0+price_change/2.0);
    
    } // Cases 3 & 4: Inventory low, price high, emissions low or high -> Increase production
    else if (price_high && !inventory_high) {
        production_planned*= (1.0+prod_change);
        
    } // Case 5: Inventory high, price low, emissions low -> Reduce production
    else if (!price_high && inventory_high && !emission_high) {
        production_planned*= (1.0-prod_change);

    } // Case 6: Inventory high, price low, emissions high -> Reduce emissions + reduce production slightly
    else if (!price_high && inventory_high && emission_high) {
        production_planned*= (1.0-prod_change/2.0);
        // Add the amount we need to buy to offset the emissions of the goods we plan to produce
        emission_offsets_needed += static_cast<int>(production_planned * unit_emissions_adj);
        Buy_Emission_Offsets(emission_offsets_needed);
        
    } // Case 7: Inventory high, price high, emissions low -> Decrease production slightly + decrease price slightly
     else if (price_high && inventory_high && !emission_high) {
        production_planned*= (1.0-prod_change/2.0);
        good_price_current *= (1.0-price_change/2.0);

    } // Case 8: Inventory high, price high, emissions high -> Decrease production slightly + decrease price slightly
    else if (price_high && inventory_high && emission_high) {
        production_planned*= (1.0-prod_change/2.0);
        good_price_current *= (1.0-price_change/2.0);
        // ** TODO: Maybe buy offsets here as well?
    }

    
    // set floor on prices at 0
    good_price_current = max(good_price_current, 0.0f);

    /* Alternative quantity adjustment formula  from jamel paper - overrides above quantity adjustments 
    Additionally impose limit on how much they can tone down production
    TODO:*/
    /*production_planned = average_sale_quantity - (inventory - desired_inventory)/inv_reaction_factor;
    int production_planned_min = static_cast<int>(production_past*(1-firm_cons_max_production_climbdown));
    int production_planned_max = static_cast<int>(production_past*(1+firm_cons_max_production_climbdown));
    if(production_planned < production_planned_min){
        production_planned = production_planned_min;
    } else if (production_planned > production_planned_max){
        production_planned = production_planned_max;
    }
    */
    pPublic_Info_Board->Update_Consumer_Goods_Production_Planned(sector_id, production_planned);

}


/* Function to buy the required amount of emission offsets, and seek a long term loan if necessary
*/
void Consumer_Firm_Agent::Buy_Emission_Offsets(int n_offsets) {
        // Calculate total cost of emissions we wish to buy 
        int emission_offset_needed_cost = n_offsets * pPublic_Info_Board->Get_Emission_Offset_Price();
        long_term_funding_gap =  max(emission_offset_needed_cost - cash_on_hand,static_cast<long long>(0)); // Funding gap must be positive
        if (long_term_funding_gap > 0){
            Seek_Long_Term_Loan();
        }
        if (long_term_funding_gap == 0){
            pPublic_Info_Board->Buy_Emission_Offsets(n_offsets, sector_id);
        }
}



/* Function that receives pointer to the sector struct and assigns the firm to that sector
Needs to update: 
*/
void Consumer_Firm_Agent::Assign_Sector(Consumer_Firm_Sector* pSector_Struct){

    // Update the sector of the firm
    sector_id = pSector_Struct->sector_id;

    // Update the sector of the consumer goods the firm is producing
    cons_goods_on_market->Set_Sector_ID(pSector_Struct->sector_id);

    // Update certain firm characteristics to match that of the sector

    output_per_machine = pSector_Struct->output_per_machine;
    workers_per_machine = pSector_Struct->output_per_machine;
    unit_good_cost = pSector_Struct->good_unit_cost;
    max_production_climbdown = pSector_Struct->max_production_climbdown;
    inv_depreciation_rate = pSector_Struct->inv_depr_rate;
    unit_emissions = pSector_Struct->emission_per_unit;

}


/* Call the public board to update emission allowances for the next time period
*/
void Consumer_Firm_Agent::Update_Emission_Allowances(){
    emission_total_allowance = pPublic_Info_Board->Distribute_Emission_Allowances(quantity_sold, unit_emissions);
}

//--------------------------------------------------------------   
//----- NonClass Functions  


