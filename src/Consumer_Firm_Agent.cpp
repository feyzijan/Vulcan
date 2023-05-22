#include "Consumer_Firm_Agent.hpp"

#include <iostream>

/* Constructors and Destructor
*/
Consumer_Firm_Agent::Consumer_Firm_Agent(float float_vals[4], int int_vals[6]): Firm_Agent::Firm_Agent(float_vals,int_vals)
{
    is_cons_firm = true;

    workers_per_machine = firm_cons_workers_per_machine;
    output_per_machine = firm_cons_productivity;
    unit_good_cost = firm_cons_good_unit_cost;
    inventory_depreciation_rate = firm_cons_inv_depr_rate;
    max_production_climbdown = firm_cons_max_production_climbdown;
    unit_emissions = firm_cons_init_emissions_per_unit;

    production_current = max(working_capital_inventory * firm_cons_workers_per_machine * firm_cons_productivity,employee_count_desired / firm_cons_workers_per_machine * firm_cons_productivity);
    inventory = production_current * desired_inventory_factor * Uniform_Dist_Float(0.5,1.5);
    quantity_sold = inventory *  firm_cons_init_quantity_sold_ratio; 
    average_sale_quantity = quantity_sold;

    // Emissions - Set default values for now
    unit_emissions = 1; // TODO: Replace with variable
    total_emissions = 0;
    cumulative_emissions = 0;

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
    // Approach 1: Set the good quantity to 0
    /* cons_goods_on_market->Set_Quantity(0);
    cons_goods_on_market->Set_Seller_Pointer(nullptr); */

    // Approach 2: Directly delete goods
    delete cons_goods_on_market;

    // Call the base class destructor
    Firm_Agent::~Firm_Agent();
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
    float current_unit_emissions = emission_total_allowance / production_current;
    float past_unit_emissions = unit_emissions_adj;
    int past_production = inventory - production_current;
    unit_emissions_adj = (past_production * past_unit_emissions + production_current * current_unit_emissions) / inventory;


    // Update consumer good object to use this new adjusted emission
    cons_goods_on_market->Set_Unit_Emission(unit_emissions_adj);

    // Update the public info board
    pPublic_Info_Board->Update_Consumer_Goods_Production(sector_id, production_current);
    pPublic_Info_Board->Update_Consumer_Goods_Production_Planned(sector_id, production_planned);
    pPublic_Info_Board->Update_Consumer_Goods_Inventory(sector_id, production_planned);
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
    desired_inventory_factor *= Uniform_Dist_Float(1.0-firm_cons_rand_desired_inventory_factor_change
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
    
    bool price_high; // check if price is high relative to the market
    price_high = good_price_current >= pPublic_Info_Board->Get_Cons_Sector_Price_Level(sector_id);

    bool emission_high; // check if emissiosn are high relative to the market
    emission_high = unit_emissions_adj >= pPublic_Info_Board->Get_Unit_Emissions_by_Sector(sector_id);
    
    good_price_past = good_price_current; // store current price incase we want to see the change
    production_past = production_current;

    bool inventory_high = inventory >= desired_inventory; 
    float p = Uniform_Dist_Float(0.0,0.5); // Random production adjustment
    float q =  Uniform_Dist_Float(0.0,0.5); // Random price adjustment

    // Case a: Inventory low, Price high - > Maintain price, increase prod
    if (!inventory_high && price_high){
        production_planned*= (1.0+q);        
    } // Case b: Inventory low, Price low - > Increase Price and production
    else if( !inventory_high && !price_high){
        good_price_current *= (1.0+p);
        production_planned*= (1.0+q);
    } // Case c: Inventory high, Price high - > Reduce price, maintain prod
    else if (inventory_high && price_high){
        good_price_current *= (1.0-p);
    } // Case d:Inventory high, Price low -> Increase price, maintain prod
    else{
        good_price_current *= (1.0+p);}

    
    // set floor on prices at 0
    good_price_current = max(good_price_current, 0.0f);

    // below eq is from jamel paper - overrides above quantity adjustments
    production_planned = average_sale_quantity - (inventory - desired_inventory)/inventory_reaction_factor;

    // Impose limit on how much they can tone down production - maybe just change bariables above?
    production_planned = max(production_planned, static_cast<int>(production_past*(1-firm_cons_max_production_climbdown))); 



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
    inventory_depreciation_rate = pSector_Struct->inv_depr_rate;
    unit_emissions = pSector_Struct->emission_per_unit;

}


/* Call the public board to update emission allowances for the next time period
*/
void Consumer_Firm_Agent::Update_Emission_Allowances(){
    emission_total_allowance = pPublic_Info_Board->Distribute_Emission_Allowances(quantity_sold, unit_emissions);
}

//--------------------------------------------------------------   
//----- NonClass Functions  


