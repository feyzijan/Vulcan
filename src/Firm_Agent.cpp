#include "Firm_Agent.hpp"

using namespace std;





void Firm_Agent::Print(){
    using namespace std;
    if (is_cons_firm){
        cout << "------ Consumer Firm Agent at address : " << this << endl;
    } else{
        cout << "------ Capital Firm Agent at address : " << this << endl;
    }
    

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
    
    for (auto i = active_job_list.begin(); i != active_job_list.end(); ++i) 
        labor_wage_bill += (*i)->Get_Wage();



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
    //cout << "Firm " << this << " posting " << new_postings << " job offers" << endl;
    for(int i=0; i< new_postings;i++){
        Job* job = new Job(this,nullptr,wage_offer,0); // Get actual date from public board
        //cout << "\n Firm Posting job with address: " <<  job <<" and wage: " << wage_offer <<endl;
        pPublic_Info_Board->Post_Job_To_Market(job);
        posted_job_list.push_back(job);
    }

}


/* This function will loop through the firm's posted_job_listings array, 
and move the ones marked as taken to the active_job_list arrays, and update employee counts

*/

void Firm_Agent::Check_For_New_Employees(){

    auto it = posted_job_list.begin();
    while(it !=  posted_job_list.end()) {
        if((*it)->Get_Status() == 1) { 
            active_job_list.push_back(*it);
            employee_count +=1;
            it = posted_job_list.erase(it);
        } else {
            it++;
        }
    }
}



/* Print Posted job offers
*/
void Firm_Agent::Print_Posted_Jobs(){
    cout << "Firm Agent Printing Posted Jobs: " << endl;
    for (auto i = posted_job_list.begin(); i !=  posted_job_list.end(); ++i){
        (*i)->Print();
    }
}


/* Print active(taken) job offers
*/
void Firm_Agent::Print_Active_Jobs(){
     cout << "Firm Agent Printing Active Jobs: " << endl;
    for (auto i = active_job_list.begin(); i !=  active_job_list.end(); ++i){
        (*i)->Print();
    }
}




/* Function to return a vector containing all class parameters
*/
std::vector<float>* Firm_Agent::Get_All_Params() {

    std::vector<float>* vec = new std::vector<float>;

    vec->push_back(production_current);
    vec->push_back(production_planned);
    vec->push_back(production_past);
    vec->push_back(quantity_sold);
    vec->push_back(total_income);
    vec->push_back(revenue_sales);
    vec->push_back(new_loan_issuance);
    vec->push_back(subsidies);
    vec->push_back(good_price_current);
    vec->push_back(good_price_past);
    vec->push_back(total_liabilities);
    vec->push_back(labor_wage_bill);
    vec->push_back(capital_costs);
    vec->push_back(tax_payments);
    vec->push_back(debt_principal_payments);
    vec->push_back(debt_interest_payments);
    vec->push_back(dividend_payments);
    vec->push_back(total_assets);
    vec->push_back(leverage_ratio);
    vec->push_back(cash_on_hand);
    vec->push_back(dividend_ratio);
    vec->push_back(dividend_ratio_optimist);
    vec->push_back(dividend_ratio_pessimist);
    vec->push_back(employee_count);
    vec->push_back(wage_offer);
    vec->push_back(employee_count_desired);
    vec->push_back(n_active_job_postings);
    vec->push_back(need_worker);
    vec->push_back(w_target);
    vec->push_back(w_current);
    vec->push_back(inventory);
    vec->push_back(working_capital_inventory);
    vec->push_back(desired_inventory_factor);
    vec->push_back(inventory_factor);
    vec->push_back(sentiment);
    vec->push_back(bankrupt);
    vec->push_back(is_cons_firm);

    return vec;
}





