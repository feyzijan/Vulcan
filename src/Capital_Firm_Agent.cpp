#include "Capital_Firm_Agent.hpp"

// -------------- Constructors ---------



Capital_Firm_Agent::Capital_Firm_Agent(float float_vals[4], int int_vals[6]) : Firm_Agent::Firm_Agent(float_vals, int_vals)
{
    //identifier
    is_cons_firm = false;

    cap_goods_on_market = new Capital_Good(this, good_price_current,inventory-quantity_sold, machine_lifespan);
    goods_on_market = cap_goods_on_market;
    // Put goods on Market
    //Send_Goods_To_Market();
}


//Copy constructor
Capital_Firm_Agent::Capital_Firm_Agent(Capital_Firm_Agent&){}

// Destructor
Capital_Firm_Agent::~Capital_Firm_Agent(){} 


// ------- Main Loop Methods-----------------

/* Function to loop through vector of capital goods the firm possesses,
mark down their value, and remove the ones with zero value, i.e. end of life
*/
/* void Capital_Firm_Agent::Depreciate_Capital(){

    for(auto i= capital_goods.begin(); i!=capital_goods.end(); i++){
        float original_price = (*i)->Get_Price();
        float current_val  =  (*i)->Get_Value();
        int depreciation_rate = (*i)->Get_Depreciation_Period();
        
        (*i)->Update_Value(current_val - original_price/depreciation_rate);

        if ((*i)->Get_Value() <= 0){capital_goods.erase(i);}
    }
    working_capital_inventory = int(capital_goods.size());
} */

/* Function to depreciate(i.e. destroy) a fraction of the firm's inventory of consumer goods
The depreciation rate is set exogenously in the initialization parameter for all firms
*/
void Capital_Firm_Agent::Depreciate_Good_Inventory(){
    inventory  = int(float(inventory)*(1.0-cap_good_inv_depr_rate));
}




/* Increment Firm inventory by the number of machines, productivity per machine,
*/
void Capital_Firm_Agent::Produce_Capital_Goods(){
    
    labor_utilization = max((float)employee_count / float(working_capital_inventory*cons_workers_per_machine), float(1.0));
    machine_utilization = max((float)working_capital_inventory / float(employee_count/cons_workers_per_machine), float(1.0));
    
    int production_max = working_capital_inventory * cap_productivity;
    
    production_current = int(production_max*labor_utilization);
    inventory += production_current;
    inventory_factor = float(inventory) / float(average_sale_quantity);
}

/* Post Produced goods to market
*/
void Capital_Firm_Agent::Send_Goods_To_Market(){
    //cout << "Cap firm " << this <<" sending goods to market" << endl;
    pPublic_Info_Board->Send_Cap_Good_To_Market(cap_goods_on_market);
}



//------------------Non member functions---------------------------


