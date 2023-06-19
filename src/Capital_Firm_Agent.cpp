#include "Capital_Firm_Agent.hpp"

// -------------- Constructors ---------



Capital_Firm_Agent::Capital_Firm_Agent(float init_values[7]) : Firm_Agent::Firm_Agent(init_values)
{
    // Set parameters specific to capital firms from the global variables
    is_cons_firm = false;
    workers_per_machine = firm_cap_workers_per_machine; // global param
    output_per_machine = firm_cap_productivity; // global param
    unit_good_cost = firm_cap_good_unit_cost; // global param
    inv_depreciation_rate = firm_cap_inv_depr_rate;
    inv_reaction_factor = firm_cap_inv_reaction_factor;
    dividend_ratio_optimist = firm_cap_init_dividend_ratio_optimist;
    dividend_ratio_pessimist =  firm_cap_init_dividend_ratio_pessimist;

    sector_id = -1;

    // Initialize goods 
    cap_goods_on_market = new Capital_Good(this, good_price_current, firm_cap_machine_lifespan); // will update quantity
    goods_on_market = cap_goods_on_market;
    //unit_good_cost = dynamic_cast<General_Good*>(cons_goods_on_market);
}


//Copy constructor
Capital_Firm_Agent::Capital_Firm_Agent(Capital_Firm_Agent&){}

// Destructor
Capital_Firm_Agent::~Capital_Firm_Agent(){
    // Remove capital goods from the market by updating quantity to zero, and setting seller pointer to zero
    cap_goods_on_market->Set_Quantity(0);
    cap_goods_on_market->Set_Seller_Pointer(nullptr); 
} 

/*
*/
void Capital_Firm_Agent::Initialize_Production(){
    // Call base class method
    Firm_Agent::Initialize_Production();

    // Set the correct values to the capital good
    cap_goods_on_market->Update_Quantity_And_Value(inventory - quantity_sold);

    // Post the goods to market
    pPublic_Info_Board->Send_Cap_Good_To_Market(cap_goods_on_market);
}




// ------- Main Loop Methods-----------------

/* Function to depreciate(i.e. destroy) a fraction of the firm's inventory of consumer goods
The depreciation rate is set exogenously in the initialization parameter for all firms
*/

void Capital_Firm_Agent::Depreciate_Good_Inventory(){
    inventory  = static_cast<long long>(inventory*(1.0-firm_cap_inv_depr_rate));
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


/* Update goods on market - Update the attributes of the goods referred by the pointer
cap_goods_on_market,  which should update the market as well */
void Capital_Firm_Agent::Update_Goods_On_Market(){
    cap_goods_on_market->Set_Quantity(inventory);
    cap_goods_on_market->Set_Price(good_price_current);
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

    pPublic_Info_Board->Update_Cap_firm_sentiment_sum(static_cast<int>(sentiment));
}


/* Determine new production - call the base class method and don't do anything about sensing emissions*/
void Capital_Firm_Agent::Determine_New_Production(){
    
    // Check if price is high relative to the market, and inventory is low relative to desired
    float average_market_price = pPublic_Info_Board->Get_Capital_Good_Price_Level();
    bool price_high = good_price_current >= average_market_price;
    bool inventory_high = inventory >= desired_inventory; 

    // Determine randomised price and production change factors
    float rand_price_change = Uniform_Dist_Float(1.0- firm_cap_fixed_price_change- firm_cap_rand_price_change_upper_limit, 
        1.0 + firm_cap_fixed_price_change + firm_cap_rand_price_change_upper_limit); 
    float rand_price_increase = Uniform_Dist_Float(1.0, 1.0 + firm_cap_fixed_price_change + firm_cap_rand_price_change_upper_limit);
    float rand_price_decrease = Uniform_Dist_Float(1.0- firm_cap_fixed_price_change - firm_cap_rand_price_change_upper_limit, 1.0);

    // Case 1: Inventory low, Price high - > Maintain price, increase prod
    if (!inventory_high && price_high){
        //production_planned*= (1.0+prod_change);  

    } // Case 2: Inventory low, Price low - > Increase Price slightly, to around  average, + increase  production slightly 
    else if( !inventory_high && !price_high){
        //production_planned *= (1.0+prod_change/2.0);
        //good_price_current = average_market_price * rand_price_change;
        good_price_current *= rand_price_increase;
    
    } // Case 3: Inventory high, Price high - > Decrease production slightly + decrease price slightly to around average
    else if (inventory_high && price_high){
        //production_planned *= (1.0-prod_change/2.0);
        //good_price_current = average_market_price * rand_price_change;
        good_price_current *= rand_price_decrease;
        //good_price_current >= pPublic_Info_Board->Get_Capital_Good_Price_Level();

    } // Case 4: Inventory high, Price low -> Reduce Production
    else{
        //production_planned*= (1.0-prod_change);
    }

    // Set floor on prices at 0
    good_price_current = max(good_price_current, unit_good_cost*1.1f);

    /* Alternative quantity adjustment formula  from jamel paper - overrides above quantity adjustments */
    production_planned = static_cast<long long>(average_sale_quantity - (inventory - desired_inventory)/inv_reaction_factor);
    production_planned = max(production_planned, static_cast<long long>(1)); // Floor at 1
    
    pPublic_Info_Board->Update_Capital_Goods_Planned_Production(production_planned);
}




//------------------Non member functions---------------------------


