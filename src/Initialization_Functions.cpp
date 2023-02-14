#include "Initialization_Functions.hpp"

// ----------------------- Consumer firms

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
        //cout << " Cons firm initializing #" << i << endl;
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
        //cout << "Cons firm initialized! #" << i << endl;
        pConsumer_Firm_vector->at(i)->Set_Public_Info_Board(pPublic_Board);
        
    }
    //cout << "Consumer Firms initialized" << endl;

}


/* Post all the job offers for all the firms in the array
*/
void Post_Initial_Job_Offers_Cons(vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector, int size){
    for (Consumer_Firm_Agent* cons_firm_ptr : *pConsumer_Firm_vector) {
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


// ----------------------- Capital firms

void Initialize_Capital_Firms(vector<Capital_Firm_Agent*> *pCapital_Firm_vector, Public_Info_Board* pPublic_Board, int size, int* promised_jobs)
{
    cout << "\n Initializing " << size << " capital firms" << endl;
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
   
    for (int i=0; i<n_capital_firms; i++) {
        //cout << "cap firm initializing #: "<< i << endl;
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
        
        pCapital_Firm_vector->push_back(new Capital_Firm_Agent(float_vals, int_vals));
        //cout << "Cons firm initialized! #" << i << endl;
        pCapital_Firm_vector->at(i)->Set_Public_Info_Board(pPublic_Board);
    }
    //cout << "Capital firms initialized" << endl;
}


void Post_Initial_Job_Offers_Cap(vector<Capital_Firm_Agent*> *pCapital_Firm_vector, int size)
{
    for (Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector) {
        firm_ptr->Post_Jobs();
    }
}


void Check_Initial_Job_Offers_Cap(vector<Capital_Firm_Agent*> *pCapital_Firm_vector, int size)
{  
    for (Capital_Firm_Agent* firm_ptr : *pCapital_Firm_vector) {
        firm_ptr->Check_For_New_Employees();
    }
}

// ----------------------- Households
void Initialize_Households(vector<Household_Agent*> *pHousehold_vector, Public_Info_Board* pPublic_Board, int size)
{   
    cout << "\n Initializing " << size << " households" << endl;
    
    //Set up Random Generators
    Normal_Dist_Generator init_c(init_c_mean, init_c_std, init_c_min, init_c_max);
    Normal_Dist_Generator init_s_optimist(init_s_optimist_mean, init_s_optimist_std, init_s_optimist_min, init_s_optimist_max);
    Normal_Dist_Generator init_s_pessimist(init_s_pessimist_mean, init_s_pessimist_std, init_s_pessimist_min, init_s_pessimist_max);
    Normal_Dist_Generator init_c_f(init_c_f_mean, init_c_f_std, init_c_f_min, init_c_f_max);
    Normal_Dist_Generator init_c_h(init_c_h_mean, init_c_h_std, init_c_h_min, init_c_h_max);
    Normal_Dist_Generator init_c_excess(init_c_excess_mean, init_c_excess_std, init_c_excess_min, init_c_excess_max);
    Normal_Dist_Generator init_p_majority(init_p_majority_mean, init_p_majority_std, init_p_majority_min, init_p_majority_max);
    Normal_Dist_Generator init_wealth(init_wealth_mean, init_wealth_std, init_wealth_min, init_wealth_max);
    Normal_Dist_Generator init_unemp_tolerance(init_unemp_tolerance_mean, init_unemp_tolerance_std, init_unemp_tolerance_min, init_unemp_tolerance_max);
    Normal_Dist_Generator init_res_wage(init_res_wage_mean, init_res_wage_std, init_res_wage_min, init_res_wage_max);

    for (int i=0; i<size; i++) {
        float propensities[] = { 
            init_c(), // consumption propensity
            init_s_optimist(), // saving_propensity_optimist 
            init_s_pessimist(), // saving_propensity_pessimist
            init_c_f(), // c_f
            init_c_h(), // c_h
            init_c_excess(), // c_excess_money
            init_p_majority(), // p_majority_op_adoption
         };

        int vals[] = {
            int(init_wealth()),
            int(init_unemp_tolerance()),
            int(init_res_wage())
        };


        pHousehold_vector->push_back(new Household_Agent(propensities, vals,pPublic_Board));
        //Household_array[i].Set_Public_Info_Board(pPublic_Board);
        //cout << "The c_h value is " << Household_array[i].Get_C_h() << endl;
    }
}


/* Loop through households and call seek jobs function
*/
void Initialize_Household_Jobs(vector<Household_Agent*> *pHousehold_vector,  int size)
{
    for (Household_Agent* household_ptr : *pHousehold_vector) {
        household_ptr->Seek_Jobs();}
}






// ----------------------- Job market
/*Function to set up Job market at t=0
Needs pointers to agent arrays and public board
*/
void Initialize_Job_Market(vector<Household_Agent*> *pHousehold_vector,
    vector<Consumer_Firm_Agent*> *pConsumer_Firm_vector, vector<Capital_Firm_Agent*> *pCapital_Firm_vector,
    Public_Info_Board* pPublic_Info_Board){

    //cout << "Now initializing job market" << endl;

    cout << "Posting Jobs: Consumer Firms- Begin" << endl;
    Post_Initial_Job_Offers_Cons(pConsumer_Firm_vector, n_consumer_firms);
    cout << "Posting Jobs: Consumer Firms- End" << endl;
    cout << "Posting Jobs: Capital Firms- Begin" << endl;
    Post_Initial_Job_Offers_Cap(pCapital_Firm_vector, n_capital_firms); 
    cout << "Posting Jobs: Capital Firms- End" << endl;
    

    Job_Market* pJob_Market = pPublic_Info_Board->Get_Job_Market_Ptr();
    //cout << "Sorting Job Market - begin" <<endl;
    pPublic_Info_Board->Sort_Job_Market();
    //cout << "Sorting Job Market - end" <<endl;
    //pJob_Market->Print_Size(); 

    cout << "Household job initialization - begin" << endl;
    Initialize_Household_Jobs(pHousehold_vector, n_households);
    cout << "Household job initialization - end" << endl;

    // All firms Check for their new employees
    cout << "Now Consumer firms are checking their job postings" << endl;
    Check_Initial_Job_Offers_Cons(pConsumer_Firm_vector, n_consumer_firms);
    cout << "Now Capital firms are checking their job postings" << endl;
    Check_Initial_Job_Offers_Cap(pCapital_Firm_vector, n_capital_firms);

    cout << " Job Market Initialization Now Complete" << endl;
    
}