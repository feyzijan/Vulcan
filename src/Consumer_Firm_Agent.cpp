#include "Consumer_Firm_Agent.hpp"

#include <iostream>

using namespace std;




void Consumer_Firm_Agent::Print(){
    using namespace std;
    cout << "\n------ Consumer Firm Agent at address : " << this << endl;
    Firm_Agent::Print();
}






Consumer_Firm_Agent::Consumer_Firm_Agent(float propensities[3], int assets, int employee_need, int capital_inventory)
{
    
    dividend_ratio_optimist = propensities[0];
    dividend_ratio_pessimist = propensities[1];
    desired_inventory_factor = propensities[2];

    cash_on_hand = assets;
    total_assets = assets;
    employee_count_desired = employee_need;
    
    working_capital_inventory = capital_inventory;





    need_worker = 1;
    sentiment = 1;
    bankrupt = 0;
    inventory_factor = 0;

    //
    Consumer_Good* goods_on_market = new Consumer_Good(this, 0,0);
    Public_Info_Board* pPublic_Info_Board = nullptr;
    Loan* loan_book[loan_book_size] = {};

    // Production and sales figures
    production_current = 0;
    production_planned = 0;
    production_past = 0; 
    quantity_sold = 0;

    // Inflows
    total_income = 0;
    revenue_sales =0;
    new_loan_issuance =0; 
    subsidies = 0;
    good_price_current = 0;
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
    wage_offer = 0;
    w_target = 0;
    w_current = 0;

    // Inventories
    inventory = 0;
}




//Copy constructor
Consumer_Firm_Agent::Consumer_Firm_Agent(Consumer_Firm_Agent&)
{

}



// Destructor
Consumer_Firm_Agent::~Consumer_Firm_Agent()
{

} 




/* Function to initialize a fixed number of households given an array of suitable size allocated

*/
void Initialize_Consumer_Firms(Consumer_Firm_Agent * Cons_Firm_array, Public_Info_Board* pPublic_Board, int size, int* promised_jobs)
{
    cout << "\n Initializing " << size << " consumer firms" << endl;


     for (int i=0; i<n_consumer_firms; i++) {
        float propensities[] = {
            0.05, // dividend_ratio_optimist 
            0.03, // dividend_ratio_pessimist 
            float(i), // inventory factor
        };
        int assets = i*10000;
        int employee_need= i+4;
        *promised_jobs += employee_need;
        int capital_inventory = employee_need;


        Cons_Firm_array[i] = Consumer_Firm_Agent(propensities, assets, employee_need, capital_inventory);
        Cons_Firm_array[i].Set_Public_Info_Board(pPublic_Board);
    }

}



void Post_Initial_Job_Offers_Cons(Consumer_Firm_Agent * Cons_Firm_array, int size){
    for (int i=0; i<size; i++) {
        cout << "Now posting jobs for cons firm # " << i << endl;
        Cons_Firm_array[i].Set_Wage_Offer((i+1)*1000);
        Cons_Firm_array[i].Post_Jobs();
    }
}



void Check_Initial_Job_Offers_Cons(Consumer_Firm_Agent * Cons_Firm_array, int size){
        for (int i=0; i<size; i++) {
        Cons_Firm_array[i].Check_For_New_Employees();
    }
}
