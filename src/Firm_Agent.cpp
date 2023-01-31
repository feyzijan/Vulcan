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


/* Function to adjust wage offers based on labor need and average wages
TODO: Improve this as it is a bit too simplistic, maybe use JAMEL
*/
void Firm_Agent::Adjust_Wage_Offers()
{
    float w_stoc; // a stochastic cutoff value for labor
    float n_uniform = Uniform_Dist_Float(0.0,0.5); //Update this to take bounds from initialization params
    int average_wage = pPublic_Info_Board->Get_Average_Wage();
    
    bool wage_high = wage_offer > average_wage;

    if (wage_high && need_worker){
        //wage_offer *= (1+n_uniform);
    } else if(wage_high && !need_worker){
        wage_offer *= (1-n_uniform);
    } else if(!wage_high && need_worker){
        wage_offer *= (1+n_uniform);
    } else{ // (!wage_high && !need_worker)

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

/* Function to check if any of the firm's active jobs have expired, 
and lay off employees if so
*/

void Firm_Agent::Cancel_Expired_Contracts(){
    auto it = active_job_list.begin();
    while(it !=  active_job_list.end()) {
        if((*it)->Get_Expiry_Status() == 1) { 
            it = active_job_list.erase(it);
            employee_count -=1;
        } else {
            it++;
        }
}
}

/* Function to randomly alter some firm parameters, such as targeted leverage, markup
TODO: Add the parameters to be altered here and fill in the function
*/
void Firm_Agent::Random_Experimentation(){

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


/* TODO: Incomplete Function
*/
void Firm_Agent::Calc_Quantity_Sold(){
    quantity_sold = inventory + production_past -  goods_on_market->Get_Quantity(); // determine how much has been sold
}


/* Function to update the firm's average profit
*/
void Firm_Agent::Update_Average_Profit(){
    average_profit += (revenue_sales -past_profits.front())/12;
    past_profits.pop();
    past_profits.push(revenue_sales);
}



void Firm_Agent::Update_Average_Profits_T1(){
    for(int i=1; i<=12; i++){
        past_profits.push(revenue_sales);
    }
    average_profit = revenue_sales;

}


/* Function to compute how much dividend can be paid to the shareholder
return this value, and deduct it from the company
This function will be called by the household, through the public board*/
int Firm_Agent::Pay_Dividends(){
    
    // Calculate dividend payment - Formula taken from Jamel
    dividend_payments = max(min(int(dividend_ratio * average_profit), cash_on_hand),0);

    cash_on_hand -= dividend_payments;

    return dividend_payments; 
}

/* Function to update new price and quantity based on past sales and price level
Follows EQ 38 from the general paper for pricing and Jamel for quantity setting
Note: I have not implemented the quantity adjustment in eq 38, but may do so

*/
void Firm_Agent::Determine_New_Production(){
    if (is_cons_firm){ 
        bool inventory_high = inventory >= desired_inventory;
        bool price_high = good_price_current >= pPublic_Info_Board->Get_Consumer_Good_Price_Level();
        
        float p = 0.01; // Chnage this to uniform distribution
        float q = 0.01; // Change this to uniform distribution


        // Case a: Inventory low, Price high - > Maintain price, ??increase Production??
        if (!inventory_high && price_high){
            production_planned*= (1.0+q);        
        } // Case b: Inventory low, Price low - > Increase Price, ??increase production slightly??
        else if( !inventory_high && !price_high){
            good_price_current *= (1.0+p);
            production_planned*= (1.0+q);
        } // Case c: Inventory high, Price high - > Maintain price, ??reduce production??
        else if (inventory_high && price_high){
            good_price_current *= (1.0-p);
        } // Case d:Inventory high, Price low -> Increase price, ??reduce production slightly??
        else{
            good_price_current *= (1.0+p);
            // Do nothing
        }

        // below eq is from jamel paper
        production_planned = average_sale_quantity - (inventory - desired_inventory)/inventory_reaction_factor;


    }else{
        float p_level = pPublic_Info_Board->Get_Consumer_Good_Price_Level();
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





