#include "Firm_Agent.hpp"



/* Create Firm agent with given characteristics and starting values
*/
Firm_Agent::Firm_Agent(float float_vals[4], int int_vals[6])
{
    dividend_ratio_optimist = float_vals[0];
    dividend_ratio_pessimist =  float_vals[1];
    desired_inventory_factor = float_vals[2];
    good_price_current = float_vals[3];

    total_assets = int_vals[0];
    employee_count_desired = int_vals[1];
    working_capital_inventory = int_vals[2];
    //inventory = int_vals[3]; // override this
    inventory = 0;
    wage_offer = int_vals[4];
    //production_current= int_vals[5]; // this may be useles
    production_current=  0 ; // set in subclass constructor

    need_worker = 1;
    sentiment = 1;
    bankrupt = 0;
    inventory_factor = 0;
    cash_on_hand = total_assets; // unsure how these two differed

    
    // Production and sales figures
    production_planned = production_current; // assume they executed their plan perfectly
    production_past = 0; 
    quantity_sold = 0;

    // Inflows
    revenue_sales = production_current * good_price_current;
    total_income = revenue_sales;
    new_loan_issuance =0; 
    subsidies = 0;
    good_price_past = firm_cons_init_good_price;
    average_profit = revenue_sales;
    average_sale_quantity = 0;
    
    // Loan Parameters
    short_term_funding_gap = 0;
    long_term_funding_gap = 0;

    // Expenditures
    total_liabilities = 0;
    labor_wage_bill =0;
    capital_costs = 0;
    tax_payments =0; 
    debt_principal_payments = 0;
    debt_interest_payments = 0;
    dividend_payments = wage_offer; // initialize this to non-zero as this will be paid in t=1
    production_costs = 0;

    expected_wage_bill = 0;
    layoff_wage_savings = 0;

    outstanding_debt_total = 0;

    // Assets and fianncials 
    leverage_ratio = 0; // correctly set
    
    // Dividend characteristics
    dividend_ratio = dividend_ratio_optimist;

    // Employees
    employee_count = 0; // correctly set
    n_active_job_postings = 0;
    w_target = 0;
    labor_utilization = 0.0;

    // Inventories
    desired_inventory = 0.0;
    inventory_reaction_factor = 1; // TODO Initialise this randomly
    machine_utilization = 0.0;
    desired_machines = 0;
    pPublic_Info_Board = nullptr;
    capital_goods_current_value = firm_cap_init_good_price;

    // Initialize capital good inventory
    initial_capital_goods = new Capital_Good(nullptr,firm_cap_init_good_price,working_capital_inventory,firm_cap_machine_lifespan);
    //cout << " Created initial capital good " << endl;
    capital_goods_list.push_back(initial_capital_goods);
    //cout << "Passed capital good into list" << endl;; 

    current_date = 0;
}

//------------------------------------------
/* Destructor For firm agents -
  Make sure all workers are laid off, all posted jobs are cancelled
*/
Firm_Agent::~Firm_Agent() {
    /* Fire all employees
    Loop through the active jobs list, update status to -1, and remove from list
    Employees will see they are fired when they check the job status, hence job object must not be deleted
    */
    for (auto it = active_job_list.begin(); it != active_job_list.end(); ++it){
        (*it)->Update_Status(-1);
    }
    active_job_list.clear();

    /* Delete Posted jobs */
    // Approach 1: Loop through the posted jobs list, update status to -3, and remove from list
    /* for (auto it = posted_job_list.begin(); it != posted_job_list.end(); ++it){
        (*it)->Update_Status(-3); // Job market will remove these on next update
    } */

    // Approach 2: Delete all objects in the posted_job_list 
    // TODO: Check this does not cause errors in the job market
    for (auto it = posted_job_list.begin(); it != posted_job_list.end(); ++it){
        delete *it;
    }

    // Loans
    /* // Loop through all loans in the loan book and set the pointers to zero
    for (auto it = loan_book.begin(); it != loan_book.end(); ++it){
        (*it)->Set_Borrowing_Firm_To_Null();
    } */

    // Delete all the objects in the loan_book
    // TODO: Check this does not cause errors in the bank agent
    for (auto it = loan_book.begin(); it != loan_book.end(); ++it){
        delete *it;
    }

    posted_job_list.clear();
}



// ----------- Initialization methods t = 1

/* Function to fill past average profit queue with initial profits
*/
void Firm_Agent::Update_Average_Profits_T1(){
    for(int i=1; i<=12; i++){
        past_profits.push(revenue_sales);
}
    average_profit = revenue_sales;
    cash_on_hand += revenue_sales;
}

/* Function to fill past average sale quantity queue with initial profits
*/
void Firm_Agent::Update_Average_Sales_T1(){
    for(int i=1; i<=12; i++){
        past_sale_quantities.push(quantity_sold);
    }
    average_sale_quantity = quantity_sold;
}

//--------------------------------------------------------------


// ------- Main Loop Methods in order --

/* Function to depreciate the value of each capital in the inventory
As it depreciates each capital object, check if it has fully depreciated, and if so remove the capital
TODO: Check below loop works properly once I update i
*/
void Firm_Agent::Depreciate_Capital(){
    capital_goods_current_value = 0;
    auto it = capital_goods_list.begin();

    while(it !=  capital_goods_list.end()) {
        (*it)->Depreciate(); 
        capital_goods_current_value += (*it)->Get_Value();
        if((*it)->Check_Depreciation() == true) { // Check if capital good has fully depreciated
            working_capital_inventory -= (*it)->Get_Quantity();
            if (working_capital_inventory < 0) {
                cout << "ERROR: Firm_Agent::Depreciate_Capital() - working_capital_inventory < 0 at firm # " << this << endl;
                working_capital_inventory = 0;
            } 
            it = capital_goods_list.erase(it);
        } else {it++;}
    }
}


/* Go through the active_job_list, check if the employee has quit ( Get_Status = -2), if so remove them 
from the list, and update employee count
*/
void Firm_Agent::Check_Employees_Quitting(){
    int temp = 0;
    auto it = active_job_list.begin();
    while(it !=  active_job_list.end()) {
        if((*it)->Get_Status() == -2) { 
            temp ++;
            it = active_job_list.erase(it);
            employee_count -=1;
        } else {it++;}
    }
    // Public Board is already updated by households when they quit
}


/* Function to lay off active employees with expired contracts
Loop through the list of active jobs, remove ones that have expired
The households are notified by
*/
void Firm_Agent::Cancel_Expired_Contracts(){
    int temp = 0; // keep track of # expired contracts
    auto it = active_job_list.begin();
    while(it !=  active_job_list.end()) {
        if((*it)->Get_Expiry_Status() == 1) { 
            temp ++;
            (*it)->Update_Status(-1); // Let household know it has been laid off
            it = active_job_list.erase(it);
            employee_count -=1;
        } else {it++;}
    }
    pPublic_Info_Board->Update_Contract_Expiries(temp);
}


/*  Function to randomly alter some firm parameters, such as targeted leverage, markup
    TODO: Read randomness parameters from Global Params
    Add more characteristics to change */
void Firm_Agent::Random_Experimentation(){
    desired_inventory_factor *= Uniform_Dist_Float(1.0-firm_cons_rand_desired_inventory_factor_change
    ,1.0 + firm_cons_rand_desired_inventory_factor_change);
    dividend_ratio_optimist *= Uniform_Dist_Float(1.0-firm_cons_rand_dividend_change, 1.0 + firm_cons_rand_dividend_change);
    dividend_ratio_pessimist *= Uniform_Dist_Float(1.0-firm_cons_rand_dividend_change, 1.0 + firm_cons_rand_dividend_change);
}

/* Function to calculate how many goods have been sold
    TODO: Check if this is correct, not sure what the inventory value is at this point
    it should be the inventory at the end of the last period*/
void Firm_Agent::Check_Sales(){
    quantity_sold = inventory -  goods_on_market->Get_Quantity(); // Originally the amount on market was equal to the inventory
    inventory -= quantity_sold;
    revenue_sales = quantity_sold * good_price_current; 

    if (revenue_sales < 0 || revenue_sales <0){ // DEBUG Lines
        cout << "ERROR: Firm Agent.Check_Sales(): Sales: " << quantity_sold << " and price:" << good_price_current << endl << " and revenue " << revenue_sales << "at firm # " << this <<  endl;
    }

    inventory_factor = float(inventory) / float(production_current);
    desired_inventory = desired_inventory_factor * production_current;
}


/* Function to update sentiment based on past sales
Will be overridden by base classes, which will update the public board 
*/
void Firm_Agent::Update_Sentiment(){
    if (quantity_sold >= average_sale_quantity){
        sentiment = 1;
    } else { sentiment = 0; }
}


/* Function to update the firm's average profit
Remove the element from 12m ago and add the most recent data*/
void Firm_Agent::Update_Average_Profit(){
    average_profit += (revenue_sales - past_profits.front())/12;
    past_profits.pop();
    past_profits.push(revenue_sales);
    cash_on_hand += revenue_sales;
}

/* Function to update the firm's average quantity sold
Remove the element from 12m ago and add the most recent data*/
void Firm_Agent::Update_Average_Sales(){
    average_sale_quantity += (quantity_sold - past_sale_quantities.front())/12;
    past_sale_quantities.pop();
    past_sale_quantities.push(quantity_sold);
}


/* Pay dividends to firm owner- formula taken from Jamel*/
int Firm_Agent::Pay_Dividend(){ 
    return dividend_payments; 
}


/* Function to update new price and quantity based on past sales and price level
Updates good_price_current and production_planned variables
There are many different ways to do this
I follow EQ 38 from the general paper for pricing and Jamel for quantity setting 
with some variation
TODO: Update random variation in price and quantity (p,q) to use global params
*/



/* Adjust wage offers based on labor need and average wages in the market
TODO: Improve this as it is a bit too simplistic, maybe use JAMEL
 - Use global params for uniform dist
*/
void Firm_Agent::Adjust_Wage_Offers()
{
    float n_uniform = Uniform_Dist_Float(0.0,0.5); //Update this to take bounds from initialization params
    int average_wage_market = pPublic_Info_Board->Get_Average_Wage();
    
    bool wage_high = wage_offer >= average_wage_market;

    if (wage_high && need_worker){
        wage_offer *= (1-n_uniform);
    } else if(wage_high && !need_worker){
        //wage_offer *= (1-n_uniform);
    } else if(!wage_high && need_worker){
        wage_offer *= (1+n_uniform);
    } else{ // (!wage_high && !need_worker)
        wage_offer *= (1+n_uniform);
    }

    wage_offer = max(wage_offer, pPublic_Info_Board->Get_Minimum_Wage()); // Make sure it is not below minimum wage

    // Loop through posted_job_list and call Update_Wage(wage_offer)
    for (auto it = posted_job_list.begin(); it != posted_job_list.end(); ++it){
        (*it)->Update_Wage(wage_offer);
    }
}


/* Determine the labor force needed to meet the production targets
The target is = minimum(#workers needed to operate machines needed to meet production target, #workers needed to operate current machines)
TODO: Recheck equation
*/
void Firm_Agent::Determine_Labor_Need(){

    // Determine the workforce needed to meet production targets
    int employees_to_meet_production = production_planned/ (firm_cons_productivity*firm_cons_workers_per_machine);
    int employees_to_operate_current_machines = working_capital_inventory/firm_cons_workers_per_machine;

    // Determine Employee demand
    //employee_count_desired = max(0, min(employees_to_meet_production, employees_to_operate_current_machines)) ;
    employee_count_desired = max(0, employees_to_meet_production); 
    int employee_demand = employee_count_desired - employee_count; // let this be negative for now
    
    // Update public records    
    pPublic_Info_Board->Update_Employee_Demand(employee_demand);

    need_worker = employee_demand > 0;
    n_active_job_postings = posted_job_list.size();
    
    // We have too many job postings - remove some
    if (n_active_job_postings >  employee_demand){
        Remove_Job_Postings();
    }

    // Layoff excess employees and update expected wage bill
    if(employee_demand < 0){
        Layoff_Excess_Workers(); // this will compute expected_wage_bill
    } else{ 
        // Compute expected wage bill ( this is computed in Layoff_Excess_Workers() as well)
        // This will be the wage bill if firm can hire everyone it wants to
        expected_wage_bill = labor_wage_bill + (employee_demand) * wage_offer;
    }

    // Compute the short term funding gap - positive if there is a funding gap
    short_term_funding_gap = max(expected_wage_bill-cash_on_hand,0);

    // If there is a short term funding gap, seek a loan
    if (short_term_funding_gap > 0){
        Seek_Short_Term_Loan(); 
    }

    // If more job postings are needed and there is no short term funding gap, post jobs
    if((short_term_funding_gap <= 0) & (n_active_job_postings <  max(0, employee_demand)) ){
        // Update public records
        pPublic_Info_Board->Update_New_Job_Postings(max(0,employee_demand) -  n_active_job_postings);
        Post_Jobs();
    }      
}

/* Function to remove job postings from the market
Called in Determine_Labour_Need if (n_active_job_postings >  employee_demand){
*/
void Firm_Agent::Remove_Job_Postings(){

    int postings_needed = max(0, employee_count_desired - employee_count);
    int postings_to_remove = max(0,n_active_job_postings - postings_needed);

    // Update public records
    pPublic_Info_Board->Update_Removed_Job_Postings(postings_to_remove);
    
    // Remove job postings from the market
    for (int i=0; i<postings_to_remove; i++){
        posted_job_list.back()->Update_Status(-3); // Job market will remove these on next update
        posted_job_list.pop_back();
        n_active_job_postings -=1;
    }
}


/* Function to layoff excess workers based on last in first out principle
Called in the Determine_Labour_Need method if(employee_demand < 0)
Remove the last n elements from the ordered vector of employees
Calculate expected wage bill after the layoffs
*/
void Firm_Agent::Layoff_Excess_Workers(){
    layoff_wage_savings = 0;
    int layoff_count = employee_count - employee_count_desired;

    // check for errors
    if (active_job_list.size() == 0){
        cout << "ERROR: Firm_Agent::Layoff_Excess_Workers() - active_job_list.size() == 0 at firm # " << this << endl;
        return;
    } else if ( active_job_list.size() != employee_count){
        cout << "ERROR: Firm_Agent::Layoff_Excess_Workers() - active_job_list.size() != employee_count at firm # " << this << endl;
        return;
    } else if ( layoff_count > active_job_list.size() ){
        cout << "ERROR: Firm_Agent::Layoff_Excess_Workers() - layoff_count > active_job_list.size() at firm # " << this << endl;
        return;
    } else if ( layoff_count < 0 ){
        cout << "ERROR: Firm_Agent::Layoff_Excess_Workers() - layoff_count < 0 at firm # " << this << endl;
        return;
    }

    // Fire employees and calc how much you save on wage bills
    for (int i=0; i<layoff_count; i++){
        layoff_wage_savings += active_job_list.back()->Get_Wage();
        active_job_list.back()->Update_Status(-1); // Household will see they are laid off on next update
        active_job_list.pop_back();
    }
    employee_count -= layoff_count;
    expected_wage_bill = labor_wage_bill - layoff_wage_savings;

    // Update public records
    pPublic_Info_Board->Update_Employee_Firings(layoff_count);
}


/* Function to post jobs to the job market and update current postings with new wage offer
 Called in Determine_New_Labour_need method if((short_term_funding_gap <= 0) & (n_active_job_postings <  max(0, employee_demand))
*/
void Firm_Agent::Post_Jobs(){
    
    int new_postings =  employee_count_desired - employee_count - n_active_job_postings ;
    
    for(int i=0; i< new_postings;i++){
        Job* job = new Job(this,nullptr,wage_offer,0); // Get actual date from public board
        pPublic_Info_Board->Post_Job_To_Market(job);
        posted_job_list.push_back(job);
    }
    n_active_job_postings += new_postings;
}


/* Loop through the firm's posted_job_listings array and move the ones marked 
as taken( status =1) to the active_job_list arrays, and update employee counts
*/
void Firm_Agent::Check_For_New_Employees(){
    int temp = 0;
    auto it = posted_job_list.begin();
    while(it !=  posted_job_list.end()) {
        if((*it)->Get_Status() == 1) { 
            active_job_list.push_back(*it);
            employee_count +=1;
            labor_wage_bill += (*it)->Get_Wage();
            it = posted_job_list.erase(it);
            temp ++;
        } else {it++;}
    }
    pPublic_Info_Board->Update_Employee_Hires(temp); // Tell public board how many ppl have been hired
    need_worker = employee_count < employee_count_desired;
}



/* Buy enough machines to match full utilization with desired number of employees
TODO: 
- Jamel has a complicated method, for now I will use a simpler one
*/
void Firm_Agent::Make_Investment_Decision(){
    desired_machines = max(0,employee_count_desired/firm_cons_workers_per_machine - working_capital_inventory);

    // Check if there is enough money to buy the goods, and if not take a loan
    if (desired_machines > 0){
        // Check how much it would cost to buy that many machines in the market right now
        int estimated_cost = pPublic_Info_Board->Get_Cost_For_Desired_Cap_Goods(desired_machines);
        long_term_funding_gap =  max(estimated_cost - cash_on_hand,0); // Funding gap must be positive
        if (long_term_funding_gap> 0){
            Seek_Long_Term_Loan();
        }
    }

    // temporary override
    //desired_machines = Uniform_Dist_Int(forced_machine_purchases_min,forced_machine_purchases_max);
    
    pPublic_Info_Board->Update_Machine_Orders_Planned(desired_machines);
}


/* Function to produce goods based on plans and capacity
*/
void Firm_Agent::Produce_Goods(){
    
    labor_utilization = min(float(working_capital_inventory*workers_per_machine) / (float)employee_count , float(1.0));
    machine_utilization = min(float(employee_count/workers_per_machine)/ (float)working_capital_inventory , float(1.0));

    // Check for erroneous values - debugging
    if ( labor_utilization < 0 || labor_utilization > 1){
        cout << "ERROR: Firm_Agent::Produce_Goods(): Labor or machine utilization is negative or > 1 at firm # " << this<< endl;
        labor_utilization = 0;
    } else if ( machine_utilization < 0 || machine_utilization > 1){
        cout << "ERROR: Firm_Agent::Produce_Goods(): Labor or machine utilization is negative or > 1 at firm # " << this << endl;
        machine_utilization = 0;
    }

    // Calculate the production

    int production_max = working_capital_inventory * output_per_machine;
    
    production_current = min(int(production_max*labor_utilization), production_planned);

    if ( production_current < 0 ){
        cout << "ERROR: Produce_Goods(): Production current is negative : p_current = " << production_current << "at firm # " << this << endl;
    } else if( production_max < 0){
        cout << "ERROR: Produce_Goods(): Production max is negative : p_max = " << production_max << " working_capital_inventory: " << 
        working_capital_inventory << " output_per_machine" << output_per_machine <<  "at firm # " << this <<  endl;
        production_max = 0;
    }

    // Update the inventory
    inventory += production_current;
    inventory_factor = float(inventory) / float(average_sale_quantity);
    production_costs = production_current * unit_good_cost;
}



/* Function to buy capital goods
*/
void Firm_Agent::Buy_Capital_Goods(){
    int n_new_machines_bought = 0;
    int total_price_paid = 0;
    int average_price = 0;
    capital_costs = 0;

    if (desired_machines > 0){ // Buy machines from the market - returns array: [quantity, total_price]
        int* arr = pPublic_Info_Board->Buy_Capital_Goods(desired_machines);
        n_new_machines_bought = arr[0];
        total_price_paid = arr[1];
        delete [] arr;
        

        // Create new capital good with given quantity and average price
        if (n_new_machines_bought > 0 || total_price_paid > 0) {
            average_price = total_price_paid/n_new_machines_bought;
            Capital_Good* new_capital_good = new Capital_Good(nullptr,average_price, n_new_machines_bought, firm_cap_machine_lifespan);
            capital_goods_list.push_back(new_capital_good);
            working_capital_inventory += n_new_machines_bought;
            capital_costs = total_price_paid;
        } else if (n_new_machines_bought < 0) {
            cout << "ERROR: Firm_Agent::Buy_Capital_Goods(): negative number of machines bought n = " << n_new_machines_bought << "at firm # " << this <<  endl;
            n_new_machines_bought = 0;
        }
        if (total_price_paid < 0){
            cout << "ERROR: Firm_Agent::Buy_Capital_Goods(): negative price paid =  " << total_price_paid << "at firm # " << this << endl;
            total_price_paid = 0;
        }
    }

    // Check if demand was not satisfied
    if (n_new_machines_bought < desired_machines) {
        cout << "Firm_Agent::Buy_Capital_Goods() - Capital good demand not satisfied - only bought " << n_new_machines_bought << " out of " << desired_machines << endl;
    }

    // Update public records
    pPublic_Info_Board->Update_Machine_Spending(total_price_paid);
    pPublic_Info_Board->Update_Machine_Orders(n_new_machines_bought);
}



/* Function to seek short term unamortized loans from the bank to cover
expected wage bill funding gap
*/
void Firm_Agent::Seek_Short_Term_Loan(){
    Loan* new_loan = pPublic_Info_Board->Seek_Short_Term_Loan(this);

    if (new_loan != nullptr){
        // Update records if a loan has been issued
        loan_book.push_back(new_loan);
        int principal = new_loan->Get_Principal_Amount();
        cash_on_hand += principal;
        new_loan_issuance += principal;
        short_term_funding_gap = 0;
        if (principal <0){
            cout << "ERROR: Firm_Agent::Seek_Short_Term_Loan() - principal < 0 at firm # " << this << endl;
        }
    } else{
        // This is an error becuase firms should always get a short term loan ( for now)
        cout << "ERROR: Firm_Agent::Seek_Short_Term_Loan() - new_loan == nullptr,  at firm # " << this << endl;
    }
}




/* Function to seek long term amortized loans from the bank to cover
expected long term funding gap
*/
void Firm_Agent::Seek_Long_Term_Loan(){
    Update_Leverage_Ratio();

    Loan* new_loan = pPublic_Info_Board->Seek_Long_Term_Loan(this);
    if (new_loan != nullptr){
        int principal = new_loan->Get_Principal_Amount();
        loan_book.push_back(new_loan); // Add the new loan to the loan book
        cash_on_hand += principal;
        new_loan_issuance += principal;
        long_term_funding_gap = 0;
        if(principal < 0){
            cout << "ERROR: Firm_Agent::Seek_Long_Term_Loan() - principal < 0 at firm # "<< this << endl;
        }
    } else{
        cout << " Firm_Agent::Seek_Long_Term_Loan() - Loan rejected" << endl;
    }
}



/* Update leverage ratio
*/
void Firm_Agent::Update_Leverage_Ratio(){
    outstanding_debt_total = 0;
    // Loop through the loan book and add up the principal amounts
    for (int i = 0; i < loan_book.size(); i++){
        int temp = loan_book[i]->Get_Principal_Amount();
        if (temp < 0){
            cout << "ERROR: Firm_Agent::Update_Leverage_Ratio(), negative loan principal at firm # " <<this << endl;
            temp = 0;
        }
        outstanding_debt_total += temp;
    }

    // Calculate leverage ratio : how many years of profits it would take to pay off all debt
    leverage_ratio = float(outstanding_debt_total)/ float(average_profit*12);
    if (leverage_ratio < 0)
    {
        cout << "ERROR: Firm_Agent::Update_Leverage_Ratio(), negative leverage ratio at firm # " << this << endl;
        cout << "Firm has outstanding debt: " << outstanding_debt_total << " and average profit*12: " << average_profit << endl;
        leverage_ratio = 0;
    }
        

}


/* Function to go through loan list and delete loans that have been paid off
*/
void Firm_Agent::Update_Loan_List(){
    auto it = loan_book.begin();
    while(it !=  loan_book.end()) {
        if((*it)->Get_Principal_Amount() <= 0) { 
            delete *it; // delete the loan object
            it = loan_book.erase(it); // delete the pointer from the vector
        } else {it++;}
    }
}



/* Method for the firm to avoid bankruptcy by having a fire sale
*/
bool Firm_Agent::Avoid_Bankruptcy(){
    if( capital_goods_current_value > long_term_funding_gap){
        cout << " Firm has enough money to sell all assets to cover costs " << endl;
        cash_on_hand += capital_goods_current_value;
        long_term_funding_gap = max(total_liabilities - cash_on_hand,0);
        
        if (long_term_funding_gap <0){
            cout << "ERROR: Firm_Agent::Avoid_Bankruptcy() - long_term_funding_gap < 0 despite avoiding bankruptcy at firm # " << this << endl;
        }
        
        // Delete(sell) all capital goods, but leave with one just because
        capital_goods_list.clear();
        capital_goods_current_value = 0;
        working_capital_inventory = 1;

        // Layoff all workers but one ( they are still paid for the preceeding period)
        int layoff_count = employee_count - 1;
        for (int i=0; i<layoff_count; i++){
            active_job_list.back()->Update_Status(-1); // Household will see they are laid off on next update
            active_job_list.pop_back();
        }
        employee_count = 1;
        pPublic_Info_Board->Update_Employee_Firings(layoff_count);
        return 1;
    } else {
        // layoff all workers and go bankrupt
        int layoff_count = employee_count;

        for (int i=0; i<layoff_count; i++){
            active_job_list.back()->Update_Status(-1); // Household will see they are laid off on next update
            active_job_list.pop_back();
        }
        employee_count = 0;
        pPublic_Info_Board->Update_Employee_Firings(layoff_count);

        return 0;
    }
}



/* Function to pay liabilities and seek loans or go bankrupt if necessary
TODO: *** CHECK if any of the below bills has already been deducted from cash on hand
*/
void Firm_Agent::Pay_Liabilities(){

    total_liabilities = 0;

    // ----Loans -----
    // Make loan repayments and tally up payments
    debt_principal_payments = 0;
    debt_interest_payments = 0;
    for (Loan* loan_ptr : loan_book){
        int current_principal_payment = loan_ptr->Calculate_Principal_Repayment();
        loan_ptr->Deduct_Principal_Repayment(current_principal_payment);
        debt_principal_payments += current_principal_payment;
        debt_interest_payments += loan_ptr->Calculate_Interest_Repayment(); // No need to deduct this
    }
    // Note: here I am assuming the firm has already made the payments for simplicity, in reality it hasn't but it will have to do avoid bankruptcy
    Update_Loan_List(); // Delete loans that have been paid off
    Update_Leverage_Ratio(); 
    // Note that newly issued loans' principals have already been added to cash on hand

    //------ Wages ------
    // Calculate wage bill 
    labor_wage_bill = 0;
    for (auto i = active_job_list.begin(); i != active_job_list.end(); ++i){ 
    labor_wage_bill += (*i)->Get_Wage();}

    // ------ Other bills
    /* The below costs have not been deducted from the cash on hand, but it is assumed the firm paid for them
    // capital_costs; // calculated in Buy_Capital_Goods()
    // production_costs; // calculated in Produce_Goods() in subclass - this
    */

    // Tally up liabilities
    total_liabilities = labor_wage_bill + debt_principal_payments + debt_interest_payments + capital_costs + production_costs;

    // Tally up income
    total_income = revenue_sales + subsidies;
    cash_on_hand += total_income;

    // check if the firm has a structural deficit
    long_term_funding_gap = max(total_liabilities - cash_on_hand,0);

    if (long_term_funding_gap > 0){
        // Need financing to avoid bankruptcy
        Seek_Long_Term_Loan();
        if (long_term_funding_gap > 0){ // Bank did not give loan
            cout << "Firm Agent at address: " << this << " is about to go bankrupt" << endl;
            if(Avoid_Bankruptcy()){
                cout << "Firm Agent at address: " << this << " avoided bankruptcy" << endl;
                bankrupt = false;
            } else{
                cout << "Firm Agent at address: " << this << " went bankrupt" << endl;
                bankrupt = true;
            }
        } else { // Successfully took a loan to cover shortfall
            bankrupt = false;
        }

    } else {
        // Pay bills
        cash_on_hand -= total_liabilities;
        total_liabilities = 0;

        // Pay dividends and taxes
        int excess_profits = max(0,total_income - total_liabilities); // Calculate excess profits
        
        tax_payments = excess_profits * firm_tax_rate; // Calculate taxes
        excess_profits -= tax_payments; // Deduct taxes from excess profits

        dividend_payments = excess_profits * dividend_ratio; // Decide dividends
        excess_profits -= dividend_payments; // Deduct dividends from excess profits

        cash_on_hand -= dividend_payments + tax_payments; // Deduct dividend and tax payments from cash on hand, which includes the original excess profits
    }

    // Reset parameters before next time step
    new_loan_issuance = 0;

}



//-------------------------------------

/* String stream opearator for printing
*/

std::ostream& operator<<(std::ostream& os, const Firm_Agent& obj) {
   /*  os << "pPublic_Info_Board: " << obj.pPublic_Info_Board << std::endl;
    os << "goods_on_market " << obj.goods_on_market << std::endl;
    os << "initial_capital_goods " << obj.initial_capital_goods << std::endl;
    os << "capital_goods_list " << obj.capital_goods_list.size() << " items" << std::endl;
    os << "loan_book " << obj.loan_book.size() << " loans" << std::endl;
    os << "past_profits " << obj.past_profits.size() << " items" << std::endl;
    os << "past_sale_quantities " << obj.past_sale_quantities.size() << " items" << std::endl;
    os << "active_job_list " << obj.active_job_list.size() << " jobs" << std::endl;
    os << "posted_job_list " << obj.posted_job_list.size() << " jobs" << std::endl; */
    os << "production_current " << obj.production_current << std::endl;
    os << "production_planned " << obj.production_planned << std::endl;
    os << "production_past " << obj.production_past << std::endl;
    os << "quantity_sold " << obj.quantity_sold << std::endl;
    os << "total_income " << obj.total_income << std::endl;
    os << "revenue_sales " << obj.revenue_sales << std::endl;
    os << "new_loan_issuance " << obj.new_loan_issuance << std::endl;
    os << "subsidies " << obj.subsidies << std::endl;
    os << "good_price_current " << obj.good_price_current << std::endl;
    os << "good_price_past " << obj.good_price_past << std::endl;
    os << "average_profit " << obj.average_profit << std::endl;
    os << "average_sale_quantity " << obj.average_sale_quantity << std::endl;
    os << "short_term_funding_gap " << obj.short_term_funding_gap << std::endl;
    os << "long_term_funding_gap " << obj.long_term_funding_gap << std::endl;
    os << "total_liabilities " << obj.total_liabilities << std::endl;
    os << "labor_wage_bill " << obj.labor_wage_bill << std::endl;
    os << "capital_costs " << obj.capital_costs << std::endl;
    os << "tax_payments " << obj.tax_payments << std::endl;
    os << "debt_principal_payments " << obj.debt_principal_payments << std::endl;
    os << "debt_interest_payments " << obj.debt_interest_payments << std::endl;
    os << "dividend_payments " << obj.dividend_payments << std::endl;
    os << "production_costs " << obj.production_costs << std::endl;
    os << "expected_wage_bill " << obj.expected_wage_bill << std::endl;
    os << "layoff_wage_savings " << obj.layoff_wage_savings << std::endl;
    os << "outstanding_debt_total " << obj.outstanding_debt_total << std::endl;
    os << "Total_assets " << obj.total_assets << std::endl;
    os << "Leverage_ratio " << obj.leverage_ratio << std::endl;
    os << "dash_on_hand " << obj.cash_on_hand << std::endl;
    os << "dividend_ratio " << obj.dividend_ratio << std::endl;
    os << "dividend_ratio_optimistic " << obj.dividend_ratio_optimist << std::endl;
    os << "dividend_ratio_pessimistic " << obj.dividend_ratio_pessimist << std::endl;
    os << "n_employees " << obj.employee_count << std::endl;
    os << "wage_offer " << obj.wage_offer << std::endl;
    os << "desired_empl_count " << obj.employee_count_desired << std::endl;
    os << "active_job_postings " << obj.n_active_job_postings << std::endl;
    os << "need_worker " << obj.need_worker << std::endl;
    os << "desired_labor_capacity_utilization " << obj.w_target << std::endl;
    os << "labor_utilization " << obj.labor_utilization << std::endl;
    os << "inventory " << obj.inventory << std::endl;
    os << "working_capital_inventory " << obj.working_capital_inventory << std::endl;
    os << "desired_inventory_factor " << obj.desired_inventory_factor << std::endl;
    os << "desired_inventory " << obj.desired_inventory << std::endl;
    os << "inventory_factor " << obj.inventory_factor << std::endl;
    os << "inventory_reaction_factor " << obj.inventory_reaction_factor << std::endl;
    os << "machine_utilization " << obj.machine_utilization << std::endl;
    os << "desired_machines " << obj.desired_machines << std::endl;
    os << "sentiment " << obj.sentiment << std::endl;
    os << "bankrupt " << obj.bankrupt << std::endl;
    os << "is_cons_firm " << obj.is_cons_firm << std::endl;
    os << "date " << obj.current_date << std::endl;
    return os;
}

/* Log method to be used for outputting data to csv

*/

vector<std::pair<string, float>>*  Firm_Agent::Log_Data() {
    current_date = global_date;

    auto result = new vector<std::pair<string, float>>();
        // Get the names and values of all member variables
        std::stringstream ss;
        ss << *this;
        string line;
        while (std::getline(ss, line)) {
            string name;
            float value;
            std::stringstream(line) >> name >> value;
            result->emplace_back(name, value);
        }
        return result;
}

//--------------------------------------------------------------
