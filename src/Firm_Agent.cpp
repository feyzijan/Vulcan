#include "Firm_Agent.hpp"

using namespace std;

// Printing methods

/* Print all Firm parameters
TODO: Update to include newly added parameters
*/
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
//--------------------------------------------------------------

// ----------- Initialization methods t = 0


// ----------- Initialization methods t = 1

/* Function to fill past average profit array with initial profits
*/
void Firm_Agent::Update_Average_Profits_T1(){
    for(int i=1; i<=12; i++){
        past_profits.push(revenue_sales);
    }
    average_profit = revenue_sales;
}

//--------------------------------------------------------------

// ------- Main Loop Methods in order --

/* Function to lay off active employees with expired contracts
*/
void Firm_Agent::Cancel_Expired_Contracts(){
    auto it = active_job_list.begin();
    while(it !=  active_job_list.end()) {
        if((*it)->Get_Expiry_Status() == 1) { 
            it = active_job_list.erase(it);
            employee_count -=1;
        } else {it++;}
    }
}

/*  Function to randomly alter some firm parameters, such as targeted leverage, markup
    TODO: Add the parameters to be altered here and fill in the function*/
void Firm_Agent::Random_Experimentation(){}

/* Function to calculate how many goods have been sold
    TODO: Check if this is correct, not sure what the inventory value is at this point
    it should be the inventory at the end of the last period*/
void Firm_Agent::Calc_Quantity_Sold(){
    quantity_sold = inventory -  goods_on_market->Get_Quantity(); // determine how much has been sold
}

/* Function to update the firm's average profit*/
void Firm_Agent::Update_Average_Profit(){
    average_profit += (revenue_sales - past_profits.front())/12;
    past_profits.pop();
    past_profits.push(revenue_sales);
}

/* Pay dividends to firm owner- formula taken from Jamel*/
int Firm_Agent::Pay_Dividends(){ 
    dividend_payments = max(min(int(dividend_ratio * average_profit), cash_on_hand),0);
    cash_on_hand -= dividend_payments;
    return dividend_payments; 
}


/* Function to update new price and quantity based on past sales and price level
Updates good_price_current and production_planned variables
Follows EQ 38 from the general paper for pricing and Jamel for quantity setting
Note: I have not implemented the quantity adjustment in eq 38, but may do so 
TODO: Update random variation in price and quantity
*/
void Firm_Agent::Determine_New_Production(){
    bool price_high;
    if (is_cons_firm){ price_high = good_price_current >= pPublic_Info_Board->Get_Consumer_Good_Price_Level();
    } else {price_high = good_price_current >= pPublic_Info_Board->Get_Capital_Good_Price_Level();}
    
    bool inventory_high = inventory >= desired_inventory; 
    float p = Uniform_Dist_Float(0.0,0.5); // Random production adjustment
    float q =  Uniform_Dist_Float(0.0,0.5); // Random price adjustment


    // Case a: Inventory low, Price high - > Maintain price, increase prod
    if (!inventory_high && price_high){
        //production_planned*= (1.0+q);        
    } // Case b: Inventory low, Price low - > Increase Price and production
    else if( !inventory_high && !price_high){
        good_price_current *= (1.0+p);
        //production_planned*= (1.0+q);
    } // Case c: Inventory high, Price high - > Reduce price, maintain prod
    else if (inventory_high && price_high){
        good_price_current *= (1.0-p);
    } // Case d:Inventory high, Price low -> Increase price, maintain prod
    else{
        good_price_current *= (1.0+p);}

    // below eq is from jamel paper - overrides above quantity adjustments
    production_planned = average_sale_quantity - (inventory - desired_inventory)/inventory_reaction_factor;
}


/* Adjust wage offers based on labor need and average wages in the market
TODO: Improve this as it is a bit too simplistic, maybe use JAMEL
*/
void Firm_Agent::Adjust_Wage_Offers()
{
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


/* Determine the labor force needed to meet the production targets
The target is = minimum(#workers needed to operate machines needed to meet production target, #workers needed to operate current machines)
TODO: Recheck equation
*/
void Firm_Agent::Determine_Labor_Need(){
    int employee_count_desired = max(0, min(int(production_planned/cons_productivity*cons_workers_per_machine),working_capital_inventory*cons_workers_per_machine)) ; // Determine the workforce needed to meet production targets
    need_worker = employee_count_desired > employee_count;
    if(employee_count_desired < employee_count){Layoff_Excess_Workers();}
    Compute_Expected_Wage_Bill();
    if (expected_wage_bill_shortfall > 0){Seek_Short_Term_Loan();}
}

/* Function to layoff excess workers based on last in first out principle
If the function is called with no excess workers it does nothing
Remove the last n elements from the ordered vector of employees
*/
void Firm_Agent::Layoff_Excess_Workers(){
    layoff_wage_savings = 0;
    int layoff_count = employee_count - employee_count_desired;
    for (int i=0; i<layoff_count; i++){
        layoff_wage_savings += active_job_list.back()->Get_Wage();
        active_job_list.back()->Update_Status(0); // Household will see they are laid off on next update
        active_job_list.pop_back();
    }
}

/* Compute the expected wage bill for the next period*/
void Firm_Agent::Compute_Expected_Wage_Bill(){
    expected_wage_bill = labor_wage_bill - layoff_wage_savings + employee_count_desired * wage_offer;
    expected_wage_bill_shortfall = min(0, expected_wage_bill - cash_on_hand);
}


/* Function to seek short term unamortized loans from the bank to cover
expected wage bill funding gap
*/
void Firm_Agent::Seek_Short_Term_Loan(){
    Loan* new_loan = pPublic_Info_Board->Seek_Short_Term_Loan(this);
    if (new_loan != nullptr){
        loan_book.push_back(new_loan);
        cash_on_hand += new_loan->Get_Principal_Amount();
    }
}


/* Function to post jobs to the job market and update current postings with new wage offer
 TODO: Remove job offers on the market if we don't need them anymore
*/
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

    // Loop through the posted_job_list and update wage_offer
    for (auto it = posted_job_list.begin(); it != posted_job_list.end(); ++it){
        (*it)->Update_Wage(wage_offer);
    }
}


/* Loop through the firm's posted_job_listings array, 
and move the ones marked as taken to the active_job_list arrays, and update employee counts
*/
void Firm_Agent::Check_For_New_Employees(){
    auto it = posted_job_list.begin();
    while(it !=  posted_job_list.end()) {
        if((*it)->Get_Status() == 1) { 
            active_job_list.push_back(*it);
            employee_count +=1;
            it = posted_job_list.erase(it);
        } else {it++;}
    }
}

/* Function to check sales in the preceeding period, and update inventory, sales figure, etc.*/
void Firm_Agent::Check_Sales()
{
    quantity_sold = production_past -  goods_on_market->Get_Quantity(); // determine how much has been sold
    inventory = goods_on_market->Get_Quantity(); // determine how much is in inventory
    revenue_sales =  quantity_sold * good_price_current;
}


/* Remove certain suppliers from list
*/
void Firm_Agent::Update_Supplier_Networks(){

}

/* Buy enough machines to match full utilization with desired number of employees
TODO: 
- Jamel has a complicated method, for now I will use a simpler one
*/
void Firm_Agent::Make_Investment_Decision(){
    desired_machines = 0;
    if(working_capital_inventory == 0) {
        desired_machines = 1;
    }else{
        desired_machines = employee_count_desired/cons_workers_per_machine - working_capital_inventory;
    }
    int est_cost = pPublic_Info_Board->Get_Cost_For_Desired_Cap_Goods(desired_machines);
    expected_long_term_shortfall =  est_cost - cash_on_hand;
    if (expected_long_term_shortfall > 0){Seek_Long_Term_Loan();}
    expected_long_term_shortfall =  est_cost - cash_on_hand;

    Buy_Machines();
}

void Firm_Agent::Buy_Machines(){
    /* if (desired_machines > 0){
        int machines_bought = pPublic_Info_Board->Buy_Machines(this, desired_machines);
        working_capital_inventory += machines_bought;
        desired_machines -= machines_bought;
    } */
    vector<Capital_Good*> new_capital_goods = pPublic_Info_Board->Buy_Capital_Goods(desired_machines);
    // Calculate the number of machines bought by looping through new_capital_goods and incrementing quantity
    int new_machines_bought = 0;
    float total_price_paid = 0;
    for (auto it = new_capital_goods.begin(); it != new_capital_goods.end(); ++it){
        new_machines_bought += (*it)->Get_Quantity();
        total_price_paid += (*it)->Get_Quantity() * (*it)->Get_Price();
    }
    // Copy all the objects in the new_capital_goods vector to the capital_goods vector
    copy(new_capital_goods.begin(), new_capital_goods.end(), back_inserter(capital_goods));
    // Update the working capital inventory
    working_capital_inventory += new_machines_bought;
}



/* Function to seek long term amortized loans from the bank to cover
expected long term funding gap
*/
void Firm_Agent::Seek_Long_Term_Loan(){
    Loan* new_loan = pPublic_Info_Board->Seek_Long_Term_Loan(this);
    if (new_loan != nullptr){
        loan_book.push_back(new_loan);
        cash_on_hand += new_loan->Get_Principal_Amount();
    }
}









/* TODO: Complete Function below
Seeks loans needed to cover shortfall, returns new funding
*/

int Firm_Agent::Seek_Loans(int shortfall)
{
    return 1;
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
