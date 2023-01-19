#include "Firm_Agent.hpp"

using namespace std;





void Firm_Agent::Print(){
    using namespace std;
    cout << "------ Firm Agent at address : " << this << endl;

    // Employee info
    cout << "Number of employees: " << employee_count << " Desired employees: " << employee_count_desired << 
    " Need Worker: " << need_worker << " Current Wage Offer: " << wage_offer << endl;
    cout << "Labor utilization current: " << w_current << " Desired: " << w_target << endl;
    
    
    //Inventory 
    cout << "Desired Inventory Factor: " << desired_inventory_factor << " Current inventory: " << inventory << " Current Inv Factor: " 
    << inventory_factor <<  " Capital inventory: " << working_capital_inventory << endl;

    // Sentiment
    cout << "Positive Sentiment: " << sentiment << " Bankruptcy: " << bankrupt <<endl;
    

    //Production and sales figures
    cout << "Production - current/actual: " << production_current << " planned: " << production_planned << " past: " << production_past <<endl;
    cout << "Quantity sold: " << quantity_sold << " Current price: " << good_price_current << " Past price: " << good_price_past << endl;

    //Inflows
    cout << "Total income: " << total_income << " Sales Revenue: " << revenue_sales << " New loans: " << new_loan_issuance  << " subsidies: " << subsidies << endl;

    //Expenditures
    cout << "Total Liabilities: " << total_liabilities << " Wage bill: " << labor_wage_bill << " Capital costs: " << capital_costs << " Tax: " << tax_payments << endl;
    cout << "Debt principal payments: " << debt_principal_payments << " Interest payments: " << debt_interest_payments << " Dividends: " << dividend_payments << endl;

    //Assets and financials
    cout << "Assets: " << total_assets << " Savings: " << cash_on_hand <<  " Leverage Ratio: " << leverage_ratio << endl;

    //Dividend characteristics
    cout << "Dividend ratio actual: " << dividend_ratio << " pessimist: " << dividend_ratio_pessimist << " optimist: " << dividend_ratio_optimist << endl;

    //Public Board
    cout << "Connected to public board at address: " << pPublic_Info_Board << endl;
    cout << "\n"<< endl;
}





/* TODO: Complete Function below
Seeks loans needed to cover shortfall, returns new funding
*/

int Firm_Agent::Seek_Loans(int shortfall)
{
    return 1;
}



/* TODO: Complete Function below
Checks if inventory is above the desired level and returns true if so
*/

bool Firm_Agent::Inventory_Above_Desire()
{
    return true;
}



void Firm_Agent::Update_Price()
{
    //int current_price = GetPrice();
    //n_uniform = uniform_dist(0,0.5);
    float n_uniform = 1; //Update this to be from uniform dist

    if (Inventory_Above_Desire())
    {
        good_price_current *= (1 + n_uniform);
    } else{
        good_price_current *= (1 - n_uniform);
    }


}

void Firm_Agent::Adjust_Wage_Offers()
{
    float w_stoc; // a stochastic cutoff value for labor
    float n_uniform; // value drawn from uniform dist

    if (w_current - w_target >= w_current)
    {
        wage_offer*= (1+n_uniform);
    } else{
        wage_offer*= (1-n_uniform);
    }


}





/* Function that sets desired production for next timestep

*/
void Firm_Agent::Plan_Production()
{
    int n_uniform = 1; //Update this to be from uniform dist

    if (Inventory_Above_Desire())
    {
        production_planned = production_current *  (1 + n_uniform);
    } else {
        good_price_current = production_current *  (1 - n_uniform);
    }

}




/* Function to check sales in the preceeding period,
Update inventory, sales figure, etc.

*/
void Firm_Agent::Check_Sales()
{
    production_past = production_current; // The then current production is now past
    production_current = 0; // initialize current prod to zero
    quantity_sold = production_past -  goods_on_market->Get_Quantity(); // determine how much has been sold
    inventory += goods_on_market->Get_Quantity(); // determine how much is in inventory

    good_price_past = good_price_current;// The then current price is now past
    good_price_current = 0; // initialize current price to zero

    revenue_sales =  quantity_sold * good_price_past;

}




/* Function to pay liabilities and seek loans or go bankrupt if necessary

*/

void Firm_Agent::Pay_Liabilities(){
    //Initialize debt payments to zero
    debt_principal_payments, debt_interest_payments = 0;
    
    //Sum up all needed debt repayments
    for (int i = 0; i++; i<sizeof(loan_book))
    {
        if (loan_book[i] != NULL){
            debt_principal_payments += loan_book[i]->Calculate_Principal_Repayment();
            debt_interest_payments += loan_book[i]->Calculate_Interest_Repayment();
        }
    }

    //Sum up wage bill
    labor_wage_bill = 0;
    employee_count = 0;

    for (int i = 0; i++; i<sizeof(employee_jobs))
    {
        if (employee_jobs[i] != NULL){
            labor_wage_bill += employee_jobs[i]->Get_Wage();
            employee_count += 1;
        }
    }

    total_liabilities = labor_wage_bill + debt_principal_payments + debt_interest_payments;

    int money_on_hand = revenue_sales + cash_on_hand < total_liabilities; 
    if (money_on_hand  < 0)
    {
        new_loan_issuance = Seek_Loans(money_on_hand); // implement this method, have it update new_loan_issuance
    }

    money_on_hand += new_loan_issuance;

    if (money_on_hand  < 0)
    {
       bankrupt = true;

    } else {
        dividend_payments = money_on_hand * dividend_ratio;
    }


}



void Firm_Agent::Post_Jobs(){
    using namespace std;
    int new_postings =  employee_count_desired - employee_count - n_active_job_postings ;
    //cout << "Employee count desired: " << employee_count_desired << " Current employees: " << employee_count << endl;
    cout << "Firm " << this << " posting " << new_postings << " job offers" << endl;
    for(int i=0; i< new_postings;i++){
        Job* job = new Job(this,nullptr,wage_offer,0); // Get actual date from public board
        //cout << "\n Firm Posting job with address: " <<  job <<" and wage: " << wage_offer <<endl;
        pPublic_Info_Board->Post_Job_To_Market(job);
    }

}


