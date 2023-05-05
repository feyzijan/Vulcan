#include "Capital_Firm_Agent.hpp"

// -------------- Constructors ---------



Capital_Firm_Agent::Capital_Firm_Agent(float float_vals[4], int int_vals[6]) : Firm_Agent::Firm_Agent(float_vals, int_vals)
{
    //identifier
    is_cons_firm = false;
    workers_per_machine = firm_cap_workers_per_machine; // global param
    output_per_machine = firm_cap_productivity; // global param
    unit_good_cost = firm_cap_good_unit_cost; // global param
    production_current = max(working_capital_inventory * firm_cap_workers_per_machine * firm_cap_productivity, employee_count_desired / firm_cap_workers_per_machine * firm_cap_productivity);
    inventory = production_current * desired_inventory_factor * Uniform_Dist_Float(0.5,1.5);
    quantity_sold = inventory *  firm_cons_init_quantity_sold_ratio; 
    average_sale_quantity = quantity_sold;
    
    cap_goods_on_market = new Capital_Good(this, good_price_current,inventory-quantity_sold, firm_cap_machine_lifespan);
    goods_on_market = cap_goods_on_market;
    // Put goods on Market
    //Send_Goods_To_Market();
    sector_id = 0;
}


//Copy constructor
Capital_Firm_Agent::Capital_Firm_Agent(Capital_Firm_Agent&){}

// Destructor
Capital_Firm_Agent::~Capital_Firm_Agent(){} 


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
    pPublic_Info_Board->Update_Capital_Goods_Production_Planned(production_planned);
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


/* Update sentiment and post to public board*/
void Capital_Firm_Agent::Update_Sentiment(){
    Firm_Agent::Update_Sentiment();
    pPublic_Info_Board->Update_Cap_firm_sentiment_sum(sentiment);
}


/* Determine new production - call the base class method but update public
board accordingly*/




//------------------Non member functions---------------------------


