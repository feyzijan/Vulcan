#include "Capital_Firm_Agent.hpp"

// -------------- Constructors ---------



Capital_Firm_Agent::Capital_Firm_Agent(float float_vals[2], int int_vals[5]) : Firm_Agent::Firm_Agent(float_vals, int_vals)
{
    //identifier
    is_cons_firm = false;
    workers_per_machine = firm_cap_workers_per_machine; // global param
    output_per_machine = firm_cap_productivity; // global param
    unit_good_cost = firm_cap_good_unit_cost; // global param
    inv_depreciation_rate = firm_cap_inv_depr_rate;
    inv_reaction_factor = firm_cap_inv_reaction_factor;
    max_production_climbdown = firm_cap_max_production_climbdown;

    dividend_ratio_optimist = firm_cap_init_dividend_ratio_optimist;
    dividend_ratio_pessimist =  firm_cap_init_dividend_ratio_pessimist;

    production_current = max(working_capital_inventory * firm_cap_workers_per_machine * firm_cap_productivity, employee_count_desired / firm_cap_workers_per_machine * firm_cap_productivity);
    production_planned = production_current;
    inventory = production_current * target_inv_factor * int_vals[3];
    quantity_sold = inventory *  firm_cons_init_quantity_sold_ratio; 
    average_sale_quantity = quantity_sold;
    revenue_sales = production_current * good_price_current;
    total_income = revenue_sales;
    average_profit = revenue_sales;

    
    cap_goods_on_market = new Capital_Good(this, good_price_current,inventory-quantity_sold, firm_cap_machine_lifespan);
    goods_on_market = cap_goods_on_market;
    // Put goods on Market
    //Send_Goods_To_Market();
    sector_id = 0;
}


//Copy constructor
Capital_Firm_Agent::Capital_Firm_Agent(Capital_Firm_Agent&){}

// Destructor
Capital_Firm_Agent::~Capital_Firm_Agent(){
    
    // Capital goods
    // Remove capital goods from the market by updating quantity to zero, and setting seller pointer to zero
    cap_goods_on_market->Set_Quantity(0);
    cap_goods_on_market->Set_Seller_Pointer(nullptr); 
} 


// ------- Main Loop Methods-----------------

/* Function to depreciate(i.e. destroy) a fraction of the firm's inventory of consumer goods
The depreciation rate is set exogenously in the initialization parameter for all firms
*/

void Capital_Firm_Agent::Depreciate_Good_Inventory(){
    inventory  = int(float(inventory)*(1.0-firm_cap_inv_depr_rate));
}




/* Increment Firm inventory by the number of machines, productivity per machine,
*/
void Capital_Firm_Agent::Produce_Goods(){
    Firm_Agent::Produce_Goods();
    // Update the public info board
    pPublic_Info_Board->Update_Capital_Goods_Production(production_current);
}

/* Check sales and update public board
*/
void Capital_Firm_Agent::Check_Sales(){
    Firm_Agent::Check_Sales();
    pPublic_Info_Board->Update_Capital_Goods_Sale_Quantities(quantity_sold);
}


/* Post Produced goods to market - only do this once at the beinning
*/
void Capital_Firm_Agent::Send_Goods_To_Market(){
    //cout << "Cap firm " << this <<" sending goods to market" << endl;
    pPublic_Info_Board->Send_Cap_Good_To_Market(cap_goods_on_market);

}

/* Update goods on market - Update the attributes of the goods referred by the pointer
cap_goods_on_market,  which should update the market as well */
void Capital_Firm_Agent::Update_Goods_On_Market(){
    cap_goods_on_market->Set_Quantity(inventory);
    cap_goods_on_market->Update_Price(good_price_current);
    cap_goods_on_market->Update_Value(good_price_current);
}


void Capital_Firm_Agent::Random_Experimentation(){
    target_inv_factor *= Uniform_Dist_Float(1.0-firm_cap_rand_desired_inventory_factor_change
    ,1.0 + firm_cap_rand_desired_inventory_factor_change);
    dividend_ratio_optimist *= Uniform_Dist_Float(1.0-firm_cap_rand_dividend_change, 1.0 + firm_cap_rand_dividend_change);
    dividend_ratio_pessimist *= Uniform_Dist_Float(1.0-firm_cap_rand_dividend_change, 1.0 + firm_cap_rand_dividend_change);
}


/* Update sentiment and post to public board*/
void Capital_Firm_Agent::Update_Sentiment(){
    Firm_Agent::Update_Sentiment();

    bool adopt_majority= Uniform_Dist_Float(0,1)  < firm_cap_rand_sentiment_adoption;
    if(adopt_majority){
        sentiment = (pPublic_Info_Board->Get_Cap_Firm_Sentiment() > 0.50); }

    // Update dividend ratio based on sentiment
    if (sentiment){dividend_ratio = dividend_ratio_optimist;
    } else{dividend_ratio = dividend_ratio_pessimist;}

    // Update the desired inventory?


    pPublic_Info_Board->Update_Cap_firm_sentiment_sum(sentiment);
}


/* Determine new production - call the base class method and don't do anything about sensing emissions*/
void Capital_Firm_Agent::Determine_New_Production(){
    
    bool price_high = good_price_current >= pPublic_Info_Board->Get_Capital_Good_Price_Level();
    
    good_price_past = good_price_current; // store current price incase we want to see the change
    production_past = production_current;

    bool inventory_high = inventory >= desired_inventory; 
    // Determine randomised price and production change factors
    float price_change =  firm_cap_fixed_price_change + Uniform_Dist_Float(0.0,firm_cap_rand_price_change_upper_limit); 
    float prod_change =  firm_cap_fixed_prod_change + Uniform_Dist_Float(0.0,firm_cap_rand_prod_change_upper_limit); 

    // Case 1: Inventory low, Price high - > Maintain price, increase prod
    if (!inventory_high && price_high){
        production_planned*= (1.0+prod_change);  

    } // Case 2: Inventory low, Price low - > Increase Price slightly + increase  production slightly 
    else if( !inventory_high && !price_high){
        good_price_current *= (1.0+price_change/2.0);
        production_planned*= (1.0+prod_change/2.0);

    } // Case 3: Inventory high, Price high - > Decrease production slightly + decrease price slightly
    else if (inventory_high && price_high){
        production_planned*= (1.0-prod_change/2.0);
        good_price_current *= (1.0-price_change/2.0);

    } // Case 4: Inventory high, Price low -> Reduce Production
    else{
        production_planned*= (1.0-prod_change);
    }

    
    // Set floor on prices at 0
    good_price_current = max(good_price_current, 0.0f);

    /* Alternative quantity adjustment formula  from jamel paper - overrides above quantity adjustments 
    Additionally impose limit on how much they can tone down production
    TODO:*/
    /*production_planned = average_sale_quantity - (inventory - desired_inventory)/inv_reaction_factor;
    int production_planned_min = static_cast<int>(production_past*(1-firm_cap_max_production_climbdown));
    int production_planned_max = static_cast<int>(production_past*(1+firm_cap_max_production_climbdown));
    if(production_planned < production_planned_min){
        production_planned = production_planned_min;
    } else if (production_planned > production_planned_max){
        production_planned = production_planned_max;
    } 
    */

    pPublic_Info_Board->Update_Capital_Goods_Planned_Production(production_planned);
}




//------------------Non member functions---------------------------


