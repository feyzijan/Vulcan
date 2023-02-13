#include "Consumer_Firm_Agent.hpp"

#include <iostream>

/* Constructors and Destructor
*/
Consumer_Firm_Agent::Consumer_Firm_Agent(float float_vals[4], int int_vals[6]): Firm_Agent::Firm_Agent(float_vals,int_vals)
{

    is_cons_firm = true;
    goods_on_market = new Consumer_Good(this, good_price_current,production_current-quantity_sold);
    //Send_Goods_To_Market();
}


//Copy constructor
Consumer_Firm_Agent::Consumer_Firm_Agent(Consumer_Firm_Agent&){}

// Destructor
Consumer_Firm_Agent::~Consumer_Firm_Agent(){} 
//------------------------------------------------------------

// ------- Main Loop Methods-----------------

/* Function to loop through vector of capital goods the firm possesses,
mark down their value, and remove the ones with zero value, i.e. end of life
*/
/* void Consumer_Firm_Agent::Depreciate_Capital(){

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
void Consumer_Firm_Agent::Depreciate_Good_Inventory(){
    inventory  = int(inventory*(1-cons_good_inv_depr_rate));
}


/* Increment Firm inventory by the number of machines, productivity per machine,
*/
void Consumer_Firm_Agent::Produce_Consumer_Goods(){

    labor_utilization = max((float)employee_count / float(working_capital_inventory*cons_workers_per_machine), float(1.0));
    machine_utilization = max((float)working_capital_inventory / float(employee_count/cons_workers_per_machine), float(1.0));
    
    int production_max = working_capital_inventory * cons_productivity;
    
    production_current = int(production_max*labor_utilization);
    inventory += production_current;
    inventory_factor = float(inventory) / float(average_sale_quantity);
}


/* Post Produced goods to market
*/
void Consumer_Firm_Agent::Send_Goods_To_Market(){
    //cout << "cons firm " << this << " sending goods to market" << endl;
    //goods_on_market->Print();
    pPublic_Info_Board->Send_Cons_Good_To_Market(goods_on_market);
}



//--------------------------------------------------------------   
//----- NonClass Functions  


/* Initialize a fixed number of households given an array of suitable size allocated
*/
void Initialize_Consumer_Firms(vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector, Public_Info_Board* pPublic_Board, int size, int* promised_jobs)
{
    cout << "\n Initializing " << size << " consumer firms" << endl;

    Normal_Dist_Generator init_dividend_ratio_optimist(init_dividend_ratio_optimist_mean, init_dividend_ratio_optimist_std, init_dividend_ratio_optimist_min, init_dividend_ratio_optimist_max);
    Normal_Dist_Generator init_dividend_ratio_pessimist(init_dividend_ratio_pessimist_mean, init_dividend_ratio_pessimist_std, init_dividend_ratio_pessimist_min, init_dividend_ratio_pessimist_max);
    Normal_Dist_Generator init_desired_inventory_factor(init_desired_inventory_factor_mean, init_desired_inventory_factor_std, init_desired_inventory_factor_min, init_desired_inventory_factor_max);
    Normal_Dist_Generator init_total_assets(init_total_assets_mean, init_total_assets_std, init_total_assets_min, init_total_assets_max);
    Normal_Dist_Generator init_employee_count_desired(init_employee_count_desired_mean, init_employee_count_desired_std, init_employee_count_desired_min, init_employee_count_desired_max);
    Normal_Dist_Generator init_working_capital_inventory(init_working_capital_inventory_mean, init_working_capital_inventory_std, init_working_capital_inventory_min, init_working_capital_inventory_max);
    Normal_Dist_Generator init_inventory(init_inventory_mean, init_inventory_std, init_inventory_min, init_inventory_max);
    Normal_Dist_Generator init_wage_offer(init_wage_offer_mean, init_wage_offer_std, init_wage_offer_min, init_wage_offer_max);
    Normal_Dist_Generator init_production_planned(init_production_planned_mean, init_production_planned_std, init_production_planned_min, init_production_planned_max);
    Normal_Dist_Generator init_good_price_current(init_good_price_current_mean, init_good_price_current_std, init_good_price_current_min, init_good_price_current_max);
   
     for (int i=0; i<n_consumer_firms; i++) {
        cout << " Cons firm initializing #" << i << endl;
        float float_vals[] = {
            init_dividend_ratio_optimist(),  
            init_dividend_ratio_pessimist(),
            init_desired_inventory_factor(), 
            init_good_price_current()
        };
        int int_vals[]{
            int(init_total_assets()),
            int(init_employee_count_desired()),
            int(init_working_capital_inventory()),
            int(init_inventory()),
            int(init_wage_offer()),
            int(init_production_planned()),
        };

        *promised_jobs += int_vals[1];
        //cout << " set up arrays now passign them in " << endl;
        pConsumer_Firm_vector->push_back(new Consumer_Firm_Agent(float_vals, int_vals));
        cout << "Cons firm initialized! #" << i << endl;
        pConsumer_Firm_vector->at(i)->Set_Public_Info_Board(pPublic_Board);
        
    }
    cout << "Consumer Firms initialized" << endl;

}


/* Post all the job offers for all the firms in the array
*/
void Post_Initial_Job_Offers_Cons(vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector, int size){
    int i = 0;
    for (Consumer_Firm_Agent* cons_firm_ptr : *pConsumer_Firm_vector) {
        i +=1000;
        cons_firm_ptr->Set_Wage_Offer(i);
        cons_firm_ptr->Post_Jobs();
    }
}


/* Check all the job offers for all the firms in the array
*/
void Check_Initial_Job_Offers_Cons(vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector, int size){
    // loop through all the firms in vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector and call Check_For_new_Employees()
    for (Consumer_Firm_Agent* cons_firm_ptr : *pConsumer_Firm_vector) {
        cons_firm_ptr->Check_For_New_Employees();
    }
}