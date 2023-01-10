#include "Capital_Firm_Agent.hpp"





void Capital_Firm_Agent::Print(){
    using namespace std;
    cout << "\n------ Capital Firm Agent at address : " << this << endl;
    Firm_Agent::Print();
}






Capital_Firm_Agent::Capital_Firm_Agent(float propensities[3], int assets, int employee_count, int capital_inventory)
{
    
    dividend_ratio_optimist = propensities[0];
    dividend_ratio_pessimist = propensities[1];
    desired_inventory_factor = propensities[2];

    cash_on_hand = assets;
    total_assets = assets;
    this->employee_count_desired = employee_count;
    working_capital_inventory = capital_inventory;

    need_worker = 1;
    sentiment = 1;
    bankrupt = 0;
    inventory_factor = 0;

    //
    Capital_Good* goods_on_market = new Capital_Good(this, 0,0);
    Public_Info_Board* pPublic_Info_Board = nullptr;
    Loan* loan_book[loan_book_size] = {};
    Job* employee_jobs[employee_list_size] = {};

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
    this->employee_count = 0; // correctly set
    wage_offer = 0;
    w_target = 0;
    w_current = 0;

    // Inventories
    inventory = 0;
}






//Copy constructor
Capital_Firm_Agent::Capital_Firm_Agent(Capital_Firm_Agent&)
{

}



// Destructor
Capital_Firm_Agent::~Capital_Firm_Agent()
{

} 

