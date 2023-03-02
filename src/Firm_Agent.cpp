#include "Firm_Agent.hpp"

using namespace std;
// Constructors

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
    production_current= 0; // set in subclass constructor

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
    good_price_past = init_good_price_past;
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
    dividend_payments = 0;
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

    // Initialize capital good inventory
    initial_capital_goods = new Capital_Good(nullptr,init_capital_good_price,working_capital_inventory,machine_lifespan);
    //cout << " Created initial capital good " << endl;
    capital_goods_list.push_back(initial_capital_goods);
    //cout << "Passed capital good into list" << endl;; 

    current_date = 0;
}

//------------------------------------------

// ----------- Initialization methods t = 1

/* Function to fill past average profit queue with initial profits
*/
void Firm_Agent::Update_Average_Profits_T1(){
    for(int i=1; i<=12; i++){
        past_profits.push(revenue_sales);
    }
    average_profit = revenue_sales;
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
*/
void Firm_Agent::Depreciate_Capital(){
    for (auto i = capital_goods_list.begin(); i !=  capital_goods_list.end(); ++i){
        (*i)->Depreciate();
    }
    
}


/* Function to lay off active employees with expired contracts
*/
void Firm_Agent::Cancel_Expired_Contracts(){
    int temp = 0;
    auto it = active_job_list.begin();
    while(it !=  active_job_list.end()) {
        if((*it)->Get_Expiry_Status() == 1) { 
            temp ++;
            it = active_job_list.erase(it);
            employee_count -=1;
        } else {it++;}
    }
    pPublic_Info_Board->Update_Contract_Expiries(temp);
}

/*  Function to randomly alter some firm parameters, such as targeted leverage, markup
    TODO: Read from Global Params */
void Firm_Agent::Random_Experimentation(){
    desired_inventory_factor *= Uniform_Dist_Float(0.8,1.2);
    dividend_ratio_optimist *= Uniform_Dist_Float(0.8,1.2);
    dividend_ratio_pessimist *= Uniform_Dist_Float(0.8,1.2);

}

/* Function to calculate how many goods have been sold
    TODO: Check if this is correct, not sure what the inventory value is at this point
    it should be the inventory at the end of the last period*/
void Firm_Agent::Check_Sales(){
    quantity_sold = inventory -  goods_on_market->Get_Quantity(); // determine how much has been sold
    inventory -= quantity_sold;
    revenue_sales = quantity_sold * good_price_current; // unsure if this gives float or int
    inventory_factor = float(inventory) / float(production_current);
    desired_inventory = desired_inventory_factor * production_current;

    if (inventory != goods_on_market->Get_Quantity()){
        cout << "Error - Firm Agent: Inventory and goods on market do not match" << endl;
    }
}


/* Function to update sentiment based on past sales
Will be overridden by base classes
*/
void Firm_Agent::Update_Sentiment(){
    if (quantity_sold > average_sale_quantity){
        sentiment = 1;
    } else if (quantity_sold < average_sale_quantity){
        sentiment = 0;
    } else {
        sentiment = 0;
    }
}


/* Function to update the firm's average profit*/
void Firm_Agent::Update_Average_Profit(){
    average_profit += (revenue_sales - past_profits.front())/12;
    past_profits.pop();
    past_profits.push(revenue_sales);
}

/* Function to update the firm's average quantity sold*/
void Firm_Agent::Update_Average_Sales(){
    average_sale_quantity += (quantity_sold - past_sale_quantities.front())/12;
    past_sale_quantities.pop();
    past_sale_quantities.push(quantity_sold);
}


/* Pay dividends to firm owner- formula taken from Jamel*/
int Firm_Agent::Pay_Dividends(){ 
    return dividend_payments; 
}


/* Function to update new price and quantity based on past sales and price level
Updates good_price_current and production_planned variables
Follows EQ 38 from the general paper for pricing and Jamel for quantity setting
Note: I have not implemented the quantity adjustment in eq 38, but may do so 
TODO: Update random variation in price and quantity
 - Make random adjustments take global parameters as limits
*/
void Firm_Agent::Determine_New_Production()
{
    bool price_high;
    if (is_cons_firm){
        price_high = good_price_current >= pPublic_Info_Board->Get_Consumer_Good_Price_Level();
    } else {
        price_high = good_price_current >= pPublic_Info_Board->Get_Capital_Good_Price_Level();
    }
    
    good_price_past = good_price_current; // store current price incase we want to see the change
    production_past = production_current;

    bool inventory_high = inventory >= desired_inventory; 
    float p = Uniform_Dist_Float(0.0,0.5); // Random production adjustment
    float q =  Uniform_Dist_Float(0.0,0.5); // Random price adjustment

    // Case a: Inventory low, Price high - > Maintain price, increase prod
    if (!inventory_high && price_high){
        production_planned*= (1.0+q);        
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
    production_planned = max(production_planned,0); // maybe instead of 0 pick production_past/10 or smt
}


/* Adjust wage offers based on labor need and average wages in the market
TODO: Improve this as it is a bit too simplistic, maybe use JAMEL
 - Use global params for uniform dist
*/
void Firm_Agent::Adjust_Wage_Offers()
{
    float n_uniform = Uniform_Dist_Float(0.0,0.5); //Update this to take bounds from initialization params
    int average_wage = pPublic_Info_Board->Get_Average_Wage();
    
    bool wage_high = wage_offer >= average_wage;

    if (wage_high && need_worker){
        wage_offer *= (1-n_uniform);
    } else if(wage_high && !need_worker){
        //wage_offer *= (1-n_uniform);
    } else if(!wage_high && need_worker){
        wage_offer *= (1+n_uniform);
    } else{ // (!wage_high && !need_worker)
        wage_offer *= (1+n_uniform);
    }

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

    // EQ to determine employee targets **Revise
    employee_count_desired = max(0, min(int(production_planned/cons_productivity*cons_workers_per_machine),working_capital_inventory*cons_workers_per_machine)) ; // Determine the workforce needed to meet production targets
    int employee_demand = employee_count_desired - employee_count;
    
    // Update public records    
    pPublic_Info_Board->Update_Employee_Demand(min(employee_demand,0));

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
        expected_wage_bill = labor_wage_bill + (employee_count_desired - employee_count) * wage_offer;
    }
    short_term_funding_gap = expected_wage_bill-cash_on_hand;

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
*/
void Firm_Agent::Remove_Job_Postings(){

    int postings_needed = max(0, employee_count_desired - employee_count);
    int postings_to_remove = max(0,n_active_job_postings - postings_needed);

    // Update public records
    pPublic_Info_Board->Update_Removed_Job_Postings(postings_to_remove);
    
    // Remove job postings from the market
    for (int i=0; i<postings_to_remove; i++){
        posted_job_list.back()->Update_Status(-1); // Job market will remove these on next update
        posted_job_list.pop_back();
        n_active_job_postings -=1;
    }
}


/* Function to layoff excess workers based on last in first out principle
If the function is called with no excess workers it does nothing
Remove the last n elements from the ordered vector of employees
Also remove active job postings from the market
*/
void Firm_Agent::Layoff_Excess_Workers(){
    layoff_wage_savings = 0;
    int layoff_count = employee_count - employee_count_desired;

    // check for errors
    if (active_job_list.size() == 0){
        return;
    } else if ( active_job_list.size() != employee_count){
        return;
    } else if ( layoff_count > active_job_list.size() ){
        return;
    } else if ( layoff_count < 0 ){
        return;
    }

    // Fire employees and calc how much you save on wage bills
    for (int i=0; i<layoff_count; i++){
        layoff_wage_savings += active_job_list.back()->Get_Wage();
        active_job_list.back()->Update_Status(0); // Household will see they are laid off on next update
        active_job_list.pop_back();
    }
    employee_count -= layoff_count;
    expected_wage_bill = labor_wage_bill - layoff_wage_savings;

    // Update public records
    pPublic_Info_Board->Update_Employee_Firings(layoff_count);
}



/* Function to seek short term unamortized loans from the bank to cover
expected wage bill funding gap
*/
void Firm_Agent::Seek_Short_Term_Loan(){
    Loan* new_loan = pPublic_Info_Board->Seek_Short_Term_Loan(this);

    if (new_loan != nullptr){
        // Update records if a loan has been issued
        loan_book.push_back(new_loan);
        cash_on_hand += new_loan->Get_Principal_Amount();
        new_loan_issuance = new_loan->Get_Principal_Amount();
        short_term_funding_gap = expected_wage_bill-cash_on_hand;

    }
}


/* Function to post jobs to the job market and update current postings with new wage offer
 TODO: Remove job offers on the market if we don't need them anymore
*/
void Firm_Agent::Post_Jobs(){
    using namespace std;
    int new_postings =  employee_count_desired - employee_count - n_active_job_postings ;
    //cout << "Employee count desired " << employee_count_desired << " Current employees " << employee_count << endl;
    //cout << "Firm " << this << " posting " << new_postings << " job offers" << endl;
    for(int i=0; i< new_postings;i++){
        //test_global_var_2 +=1;
        Job* job = new Job(this,nullptr,wage_offer,0); // Get actual date from public board
        //cout << "\n Firm Posting job with address " <<  job <<" and wage " << wage_offer <<endl;
        pPublic_Info_Board->Post_Job_To_Market(job);
        posted_job_list.push_back(job);
    }
    n_active_job_postings += new_postings;

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
    int temp = 0;
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
    desired_machines = 0;
    if(working_capital_inventory == 0) {
        desired_machines = 1;
    }else{
        desired_machines = min(0,employee_count_desired/cons_workers_per_machine - working_capital_inventory);
    }
    if (desired_machines >0){
        int estimated_cost = pPublic_Info_Board->Get_Cost_For_Desired_Cap_Goods(desired_machines);
        long_term_funding_gap =  estimated_cost - cash_on_hand;
        if (long_term_funding_gap> 0){Seek_Long_Term_Loan();}
        long_term_funding_gap =  estimated_cost - cash_on_hand;
    }
    // temporary override
    desired_machines = Uniform_Dist_Int(0,5);
    test_global_var += desired_machines;
}

void Firm_Agent::Buy_Capital_Goods(){
    /* if (desired_machines > 0){
        int machines_bought = pPublic_Info_Board->Buy_Machines(this, desired_machines);
        working_capital_inventory += machines_bought;
        desired_machines -= machines_bought;
    } */
    vector<Capital_Good*>* new_capital_goods = pPublic_Info_Board->Buy_Capital_Goods(desired_machines);
    // Calculate the number of machines bought by looping through new_capital_goods and incrementing quantity
    
    int new_machines_bought = 0;
    float total_price_paid = 0;

    if (new_capital_goods->empty() == false){
        for (auto cap_good : *new_capital_goods){
            new_machines_bought += cap_good->Get_Quantity();
            total_price_paid += cap_good->Get_Quantity() * cap_good->Get_Price();
        }
    }

    // Copy all the objects in the new_capital_goods vector to the capital_goods vector
    capital_goods_list.insert(capital_goods_list.end(), new_capital_goods->begin(), new_capital_goods->end());
    delete new_capital_goods;
    // Update the working capital inventory
    working_capital_inventory += new_machines_bought;
    capital_costs = total_price_paid;

    pPublic_Info_Board->Update_Machine_spending(total_price_paid);
    pPublic_Info_Board->Update_Machine_orders(new_machines_bought);
}



/* Function to seek long term amortized loans from the bank to cover
expected long term funding gap
*/
void Firm_Agent::Seek_Long_Term_Loan(){
    Loan* new_loan = pPublic_Info_Board->Seek_Long_Term_Loan(this);
    if (new_loan != nullptr){
        loan_book.push_back(new_loan);
        cash_on_hand += new_loan->Get_Principal_Amount();
        new_loan_issuance = new_loan->Get_Principal_Amount();
    }
}




/* Update leverage ratio
*/
void Firm_Agent::Update_Leverage_Ratio(){
    outstanding_debt_total = 0;
    // Loop through the loan book and add up the principal amounts
    for (Loan* loan_ptr : loan_book){
        outstanding_debt_total += loan_ptr->Get_Principal_Amount();
    }
    // Calculate leverage ratio
    leverage_ratio = float(outstanding_debt_total)/ float(average_profit);


}



/* Function to pay liabilities and seek loans or go bankrupt if necessary

*/
void Firm_Agent::Pay_Liabilities(){

    total_liabilities = 0;

    // Calculate debt bill
    debt_principal_payments = 0;
    debt_interest_payments = 0;
    for (Loan* loan_ptr : loan_book){
        debt_principal_payments += loan_ptr->Calculate_Principal_Repayment();
        debt_interest_payments += loan_ptr->Calculate_Interest_Repayment();
    }

    // Calculate wage bill 
    labor_wage_bill = 0;
    for (auto i = active_job_list.begin(); i != active_job_list.end(); ++i){ 
    labor_wage_bill += (*i)->Get_Wage();}

    // Other bills
    // capital_costs; // calculated in Buy_Capital_Goods()
    // dividend_payments; // calculated in Pay_Dividends()
    // production_costs; // calculated in Produce_Goods() in subclass

    // Tally up liabilities
    total_liabilities = labor_wage_bill + debt_principal_payments + debt_interest_payments + capital_costs + production_costs;

    // Tally up income
    total_income = revenue_sales + subsidies;
    cash_on_hand += total_income; // new_loan_issuance already added when loans were taken

    // Update leverage ratio
    Update_Leverage_Ratio();

    if (cash_on_hand < total_liabilities){
        // Need financing to avoid bankruptcy
        long_term_funding_gap = cash_on_hand - total_liabilities;
        Seek_Long_Term_Loan();
        bankrupt = true;
        // what now?

    } else {
        // Pay bills
        cash_on_hand -= total_liabilities;
        // Pay dividends and taxes
        int excess_profits = max(0,total_income - total_liabilities);
        dividend_payments = excess_profits * dividend_ratio;
        excess_profits -= dividend_payments;
        tax_payments = excess_profits * firm_tax_rate;
        cash_on_hand -= dividend_payments + tax_payments;
        Pay_Dividends();
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
    vec->push_back(labor_utilization);
    vec->push_back(inventory);
    vec->push_back(working_capital_inventory);
    vec->push_back(desired_inventory_factor);
    vec->push_back(inventory_factor);
    vec->push_back(sentiment);
    vec->push_back(bankrupt);
    vec->push_back(is_cons_firm);

    vec->push_back(average_profit);
    vec->push_back(average_sale_quantity);
    vec->push_back(short_term_funding_gap);
    vec->push_back(long_term_funding_gap);
    vec->push_back(expected_wage_bill);
    vec->push_back(layoff_wage_savings);
    vec->push_back(labor_utilization);
    vec->push_back(desired_inventory);
    vec->push_back(inventory_reaction_factor);
    vec->push_back(machine_utilization);
    vec->push_back(desired_machines);
    vec->push_back(production_costs);
    vec->push_back(outstanding_debt_total);

    return vec;
}


//-------------------------------------
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
    cout << "Labor utilization current: " << labor_utilization << " Desired: " << w_target << endl;


    // Inventory 
    cout << "Desired Inventory Factor: " << desired_inventory_factor << " Current inventory: " << inventory << " Current Inv Factor: " 
    << inventory_factor << endl << "Desired Inventory: " << desired_inventory <<  " Capital inventory: " << working_capital_inventory << endl;
    cout << "Inventory reaction factor: " << inventory_reaction_factor << " Desired machines: " << desired_machines << " Machine utilization: " << machine_utilization << endl;

    // Sentiment
    cout << "Positive Sentiment: " << sentiment << " Bankruptcy: " << bankrupt <<endl;
    
    //Production, sales ,and price figures
    cout << "Production - current/actual: " << production_current << " planned: " << production_planned << " past: " << production_past <<endl;
    cout << "Quantity sold: " << quantity_sold << " Current price: " << good_price_current << " Past price: " << good_price_past << endl;
    cout << "Average profit " << average_profit << " Average sale quantity: " << average_sale_quantity << endl;

    //Inflows
    cout << "Total income: " << total_income << " Sales Revenue: " << revenue_sales << " New loans: " << new_loan_issuance  << " subsidies: " << subsidies << endl;
    
    // Loan parameters
    cout << "Short term funding gap: " << short_term_funding_gap << " Long term funding gap: " << long_term_funding_gap << endl;

    //Expenditures
    cout << "Total Liabilities: " << total_liabilities << " Wage bill: " << labor_wage_bill << " Capital costs: " << capital_costs << " Tax: " << tax_payments << endl;
    cout << "Debt principal payments: " << debt_principal_payments << " Interest payments: " << debt_interest_payments << " Dividends: " << dividend_payments << endl;
    cout << "Production costs: " << production_costs <<  " Expected wage bill: " << expected_wage_bill << " Layoff wage savings: " << layoff_wage_savings << endl;

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

/* Print all capital goods owned by the firm
*/
void Firm_Agent::Print_Capital_Goods(){
    cout << "Firm Agent Printing Capital Good Inventory: " << endl;
    for (auto i = capital_goods_list.begin(); i !=  capital_goods_list.end(); ++i){
        (*i)->Print();
    }
}

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
    os << "Total Assets " << obj.total_assets << std::endl;
    os << "Leverage Ratio " << obj.leverage_ratio << std::endl;
    os << "Cash on Hand " << obj.cash_on_hand << std::endl;
    os << "Dividend Ratio " << obj.dividend_ratio << std::endl;
    os << "Optimistic Dividend Ratio " << obj.dividend_ratio_optimist << std::endl;
    os << "Pessimistic Dividend Ratio " << obj.dividend_ratio_pessimist << std::endl;
    os << "Employee Count " << obj.employee_count << std::endl;
    os << "Wage Offer " << obj.wage_offer << std::endl;
    os << "Desired Employee Count " << obj.employee_count_desired << std::endl;
    os << "Active Job Postings " << obj.n_active_job_postings << std::endl;
    os << "Need Worker " << obj.need_worker << std::endl;
    os << "Desired Labor Capacity Utilization " << obj.w_target << std::endl;
    os << "Labor Utilization " << obj.labor_utilization << std::endl;
    os << "Inventory " << obj.inventory << std::endl;
    os << "Working Capital Inventory " << obj.working_capital_inventory << std::endl;
    os << "Desired Inventory Factor " << obj.desired_inventory_factor << std::endl;
    os << "desired_inventory " << obj.desired_inventory << std::endl;
    os << "inventory_factor " << obj.inventory_factor << std::endl;
    os << "inventory_reaction_factor " << obj.inventory_reaction_factor << std::endl;
    os << "machine_utilization " << obj.machine_utilization << std::endl;
    os << "desired_machines " << obj.desired_machines << std::endl;
    os << "sentiment " << obj.sentiment << std::endl;
    os << "bankrupt " << obj.bankrupt << std::endl;
    os << "is_cons_firm " << obj.is_cons_firm << std::endl;
    os << "date " << obj.current_date << std::endl;
}

/* Log method to be used for outputting data to csv

*/

std::vector<std::pair<std::string, float>>*  Firm_Agent::Log_Data() {
    current_date = global_date;

    auto result = new std::vector<std::pair<std::string, float>>();
        // Get the names and values of all member variables
        std::stringstream ss;
        ss << *this;
        std::string line;
        while (std::getline(ss, line)) {
            std::string name;
            float value;
            std::stringstream(line) >> name >> value;
            result->emplace_back(name, value);
        }
        return result;
}



//--------------------------------------------------------------
