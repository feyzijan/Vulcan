#include "Capital_Firm_Agent.hpp"


using namespace std;


void Capital_Firm_Agent::Print(){
    using namespace std;
    cout << "\n------ Capital Firm Agent at address : " << this << endl;
    Firm_Agent::Print();
}






Capital_Firm_Agent::Capital_Firm_Agent(float float_vals[4], int int_vals[6])
{
    
    dividend_ratio_optimist = float_vals[0];
    dividend_ratio_pessimist =  float_vals[1];
    desired_inventory_factor = float_vals[2];
    good_price_current = float_vals[3];

    total_assets = int_vals[0];
    employee_count_desired = int_vals[1];
    working_capital_inventory = int_vals[2];
    inventory = int_vals[3];
    wage_offer = int_vals[4];
    production_planned = int_vals[5];

    need_worker = 1;
    sentiment = 1;
    bankrupt = 0;
    inventory_factor = 0;
    cash_on_hand = total_assets; // unsure how these two differed

    // Initialize pointers
    Capital_Good* goods_on_market = new Capital_Good(this, 0,0);
    Public_Info_Board* pPublic_Info_Board = nullptr;
    Loan* loan_book[loan_book_size] = {};

    // Set evt else to zero
    // Production and sales figures
    production_current = 0;
    production_past = 0; 
    quantity_sold = 0;

    // Inflows
    total_income = 0;
    revenue_sales =0;
    new_loan_issuance =0; 
    subsidies = 0;
    good_price_past = 0;

    // Expenditures
    total_liabilities = 0;
    labor_wage_bill =0;
    capital_costs = 0;
    tax_payments =0; 
    debt_principal_payments = 0;
    debt_interest_payments = 0;
    dividend_payments = 0;

    // Assets and fianncials 
    leverage_ratio = 0; // correctly set
    
    // Dividend characteristics
    dividend_ratio = dividend_ratio_optimist;

    // Employees
    employee_count = 0; // correctly set
    n_active_job_postings = 0;
    w_target = 0;
    w_current = 0;

    //identifier
    is_cons_firm = 0;
}






//Copy constructor
Capital_Firm_Agent::Capital_Firm_Agent(Capital_Firm_Agent&)
{

}



// Destructor
Capital_Firm_Agent::~Capital_Firm_Agent()
{

} 



//------------------Non member functions---------------------------

void Initialize_Capital_Firms(Capital_Firm_Agent * Cap_Firm_array, Public_Info_Board* pPublic_Board, int size, int* promised_jobs)
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
        Cap_Firm_array[i] = Capital_Firm_Agent(float_vals, int_vals);
        Cap_Firm_array[i].Set_Public_Info_Board(pPublic_Board);
    }
}




void Post_Initial_Job_Offers_Cap(Capital_Firm_Agent * Cap_Firm_array, int size){
    for (int i=0; i<size; i++) {
        //cout << "Now posting jobs for cap firm # " << i << endl;
        Cap_Firm_array[i].Set_Wage_Offer((i+1)*1000);
        Cap_Firm_array[i].Post_Jobs();
    }
}


void Check_Initial_Job_Offers_Cap(Capital_Firm_Agent * Cap_Firm_array, int size){
        for (int i=0; i<size; i++) {
        Cap_Firm_array[i].Check_For_New_Employees();
    }
}
