#include "Bank_Agent.hpp"


//----------Constructor  ------ 

/* Initialize the bank agent with a public board pointer
Initialize the inflation and interest rate wih preset global parameters
Initialize everything else to zero
*/
Bank_Agent::Bank_Agent(Public_Info_Board* pPublic_Info_Board){

    this->pPublic_Board = pPublic_Info_Board;

    // Interest rate 
    r_rate = bank_init_interest_rate; // preset Global param
    risk_premium = bank_risk_premium; // preset Global param
    r_reaction = bank_inflation_reaction; // preset Global param

    // Inflation
    cons_inflation_target = bank_inflation_target; // preset Global param
    cons_inflation_past_month = bank_inflation_target_monthly; // preset Global param
    cons_inflation_previous = 1.0;

    // Initialize cons_inflation_history
    for(int i = 0; i < 12; i++){
        cons_inflation_previous *= bank_inflation_target_monthly; // preset Global param
        cons_inflation_history.push(bank_inflation_target_monthly);
    }

    cons_inflation_current = cons_inflation_previous;

    // Manufacturer inflation - start  off same as consumer inflation
    float cap_inflation_target = bank_inflation_target; // not actually used
    cap_inflation_past_month = bank_inflation_target_monthly; // preset Global param
    cap_inflation_previous = 1.0;

    for(int i = 0; i < 12;i++){
        cap_inflation_previous *= bank_inflation_target_monthly; // preset Global param
        cap_inflation_history.push(bank_inflation_target_monthly);
    }
    
    // Repayments
    new_principal_repayments = 0;
    new_interest_repayments = 0;
    total_principal_repayments = 0;
    total_interest_repayments = 0;

    // Loan issuance totals
    total_loan_issuance_to_date = 0;
    short_term_loan_issuance_to_date = 0;
    long_term_loan_issuance_to_date = 0;
    total_new_loan_issuance = 0;
    new_short_term_loan_issuance = 0;
    new_long_term_loan_issuance = 0;
    total_outstanding_loans = 0;
    outstanding_short_term_loans = 0;
    outstanding_long_term_loans = 0;

    // Loan parameters
    short_term_loan_length = bank_short_term_loan_length;
    long_term_loan_length = bank_long_term_loan_length;

    // Risky loan evaluation
    leverage_ratio_lower_threshold = bank_leverage_ratio_lower_threshold;
    leverage_ratio_upper_threshold = bank_leverage_ratio_upper_threshold;

    current_date = 0;
}


// --------- Inflation and Interest Rate Policies

/* Function to update consumer and capital price levels and inflation rate data
    First make public board update its price and inflation records
    Then get the latest inflation figures from the public board
*/
void Bank_Agent::Update_Inflation(){
    // Set current to previous
    cons_inflation_previous = cons_inflation_current;
    cap_inflation_previous = cap_inflation_current;
    // Make public board update stuff
    pPublic_Board->Update_Consumer_Price_Level();
    pPublic_Board->Update_Capital_Price_Level();
    // Get the updated data
    cons_inflation_past_month = pPublic_Board->Get_Consumer_Inflation();
    cap_inflation_past_month = pPublic_Board->Get_Capital_Inflation();
    // Update inflation to match trailing 12m
    cons_inflation_current = cons_inflation_previous / cons_inflation_history.front() * cons_inflation_past_month;
    cap_inflation_current = cap_inflation_previous / cap_inflation_history.front() * cap_inflation_past_month;

    if(cons_inflation_current < 0){
        cout << "ERROR: Bank_Agent::Update_Inflation() - cons_inflation_current < 0" << endl;
    }

    // Update inflation_histories
    cons_inflation_history.pop();
    cons_inflation_history.push(cons_inflation_past_month);

    cap_inflation_history.pop();
    cap_inflation_history.push(cap_inflation_past_month);
}


/* Function to update interest rate based on new inflation data
 To be called after calling Update_Inflation_Rate()
 Use a simple taylor rule from the Jamel Paper
*/
void Bank_Agent::Update_Interest_Rate(){

    float inflation_overshoot = max(cons_inflation_current - cons_inflation_target, float(0.0));

    float r_current = r_rate;

    // Set interest rate proportional to inflation overshoot
    r_rate = max( float(r_reaction* inflation_overshoot), float(0.01)); // minimum interest rate of 1%

    // Impose maximum increase limit
    if (r_rate > r_current + bank_max_interest_rate_change){
        r_rate = r_current + bank_max_interest_rate_change;
    }
    // Check for max interest rate limit
    r_rate = min(r_rate, bank_max_interest_rate) ; // maximum interest rate of 40%

    // Update historical records
    interest_rate_history.push(r_rate);
}


// Loan issuance

/* Issue short term loans at the risk free rate, without any checks
Function receives firm pointer, accesses the funding gap data, and issues a loan
Updates own records to indicate the loan has been issued
*/
Loan* Bank_Agent::Issue_Short_Term_Loan(Firm_Agent* pFirm){

    // Gather data to issue loan, give a little extra then is required to smooth things over
    float extra_funding = 0.01;
    long long short_term_funding_gap = pFirm->Get_Short_Term_Funding_Gap();
    
    if (short_term_funding_gap <= 0){
        cout << "ERROR: Bank_Agent::Issue_Short_Term_Loan() - Firm has no short term funding gap " << short_term_funding_gap << ", firm #" << pFirm << endl;
    }

    long long loan_amount = short_term_funding_gap + short_term_funding_gap * extra_funding;
    if (loan_amount < 0){
        cout << "ERROR: Bank_Agent::Issue_Short_Term_Loan() - loan_amount < 0 - firm #" << pFirm << endl;
        cout << "Firm has short term funding gap "  << short_term_funding_gap<< endl;
    }

    // Issue the loan
    Loan* new_loan = new Loan(pFirm,r_rate, loan_amount, short_term_loan_length,1);
    
    // Update own records
    total_loan_issuance_to_date += loan_amount;
    short_term_loan_issuance_to_date += loan_amount;
    total_new_loan_issuance += loan_amount;
    new_short_term_loan_issuance += loan_amount;
    total_outstanding_loans += loan_amount;
    outstanding_short_term_loans += loan_amount;
    short_term_loan_book.push_back(new_loan);

    // return the loan
    return new_loan;
}


/* Issue long term loans at the risk free rate + risk premium
Function receives firm pointer, accesses the funding gap data wand risk data,
and issues a loan, or not, and returns a null pointer
Updates own records to indicate the loan has been issued
*/

Loan* Bank_Agent::Issue_Long_Term_Loan(Firm_Agent* pFirm){

    // Gather data to issue loan, give a little extra to smooth things over
    float extra_funding = 0.01;
    long long long_term_funding_gap = pFirm->Get_Long_Term_Funding_Gap(); 

    if (long_term_funding_gap == 0){
        cout << "ERROR: Bank_Agent::Issue_Long_Term_Loan() - long_term_funding_gap <= 0,  firm #" << pFirm  << endl;
    }

    double leverage_ratio = pFirm->Get_Leverage_Ratio();
    if (leverage_ratio < 0.0){
        cout << "ERROR: Bank_Agent::Issue_Long_Term_Loan() - leverage_ratio < 0 , firm #" << pFirm  << endl;
    }

    if(leverage_ratio < leverage_ratio_upper_threshold){
        // Create Loan with new risky rate

        float emission_penalty;
        if (pFirm->Get_Cons_Firm_Status()){
            emission_penalty = Calculate_Emission_Penalty(pFirm);
        } else {
            emission_penalty = 0;
        }
        float risk_penalty = Calculate_Leverage_Penalty(leverage_ratio);
        
        float loan_rate = r_rate + risk_penalty + emission_penalty;
        if (loan_rate < 0){
            cout << "ERROR: Bank_Agent::Issue_Long_Term_Loan() - negative loan_rate is " << loan_rate << endl;
        }

        long long loan_amount = long_term_funding_gap + long_term_funding_gap * extra_funding;

        if (loan_amount == 0){
            cout << "ERROR: Bank_Agent::Issue_Long_Term_Loan() - loan_amount < 0 - firm # " << pFirm << "Firm has long term funding gap "  << long_term_funding_gap<< endl;
        }
        
        Loan* new_loan = new Loan(pFirm,loan_rate, loan_amount , long_term_loan_length,0);
        
        // Update own records
        total_loan_issuance_to_date += loan_amount;
        long_term_loan_issuance_to_date += loan_amount;
        total_new_loan_issuance += loan_amount;
        new_long_term_loan_issuance += loan_amount;
        total_outstanding_loans += loan_amount;
        outstanding_long_term_loans += loan_amount;
        long_term_loan_book.push_back(new_loan);
        return new_loan;
        } else { return nullptr;} // Don't issue loan if firm is too leveraged

}


/* Function to calculate how much premium to charge in loand for a firm's emission
Either look at the firm's total emissions, or the firm's emissions per unit of output based on user selection
Linearly interpolate between the firms emissions and the bank's lower and upper thresholds
and impose the necessary penalty
*/

float Bank_Agent::Calculate_Emission_Penalty(Firm_Agent *pFirm){
    if(bank_unit_emission_penalty){
        float firm_emission = pFirm->Get_Unit_Emissions();
        if(firm_emission <= bank_unit_emission_lower_thr){
            return 0;
        } else if (firm_emission >= bank_unit_emission_upper_thr){
            return bank_emission_penalty_max;
        } else {
            return bank_emission_penalty_max * (firm_emission - bank_unit_emission_lower_thr) / (bank_unit_emission_upper_thr - bank_unit_emission_lower_thr);
        }
    } else {
        long long firm_emission = pFirm->Get_Total_Emissions();
        if(firm_emission <= bank_total_emission_lower_thr){
            return 0;
        } else if (firm_emission >= bank_total_emission_upper_thr){
            return bank_emission_penalty_max;
        } else {
            return bank_emission_penalty_max * (firm_emission - bank_total_emission_lower_thr) / (bank_total_emission_upper_thr - bank_total_emission_lower_thr);
        }
    }
}

/*
*/
float Bank_Agent::Calculate_Leverage_Penalty(float leverage_ratio){
    if(leverage_ratio <= leverage_ratio_lower_threshold){
        return 0;
    } else if (leverage_ratio >= leverage_ratio_upper_threshold){
        return  risk_premium;
    } else {
        return risk_premium * (leverage_ratio - leverage_ratio_lower_threshold) / (leverage_ratio_upper_threshold - leverage_ratio_lower_threshold);
    }

}


/* Loop through the loan list
- if the loan is expired, erase it from the list and delete the object
- if the loan is not expired, calculate interest and principal payments, and add them appropriately
*/
void Bank_Agent::Check_Loans(){
    new_interest_repayments = 0;
    new_principal_repayments = 0;
    auto it = long_term_loan_book.begin();
    while(it != long_term_loan_book.end()){
        if ( (*it)->Get_Bankruptcy_Status()){ // firm is bankrupt, no repayments
            delete *it; // delete the loan object
            it = long_term_loan_book.erase(it); // delete the pointer from the vector

        } else if ((*it)->Get_Expiration_Status()  && !(*it)->Get_Bankruptcy_Status()){   // Firm has finished repaying
            new_interest_repayments += (*it)->Calculate_Interest_Repayment();
            new_principal_repayments += (*it)->Calculate_Principal_Repayment();
            total_outstanding_loans -= (*it)->Get_Principal_Amount();
            outstanding_long_term_loans -= (*it)->Get_Principal_Amount();
            delete *it; // delete the loan object
            it = long_term_loan_book.erase(it); // delete the pointer from the vector

        }  else { // Firm has not finished repaying
            new_interest_repayments += (*it)->Calculate_Interest_Repayment();
            new_principal_repayments += (*it)->Calculate_Principal_Repayment();
            it++;
        }
    }

    it = short_term_loan_book.begin();
    while (it != short_term_loan_book.end()){
        if ( (*it)->Get_Bankruptcy_Status()){ // firm is bankrupt, no repayments
            delete *it; // delete the loan object
            it = short_term_loan_book.erase(it); // delete the pointer from the vector

        } else if ((*it)->Get_Expiration_Status()  && !(*it)->Get_Bankruptcy_Status()){   // Firm has finished repaying
            new_interest_repayments += (*it)->Calculate_Interest_Repayment();
            new_principal_repayments += (*it)->Calculate_Principal_Repayment();
            total_outstanding_loans -= (*it)->Get_Principal_Amount();
            outstanding_short_term_loans -= (*it)->Get_Principal_Amount();
            delete *it; // delete the loan object
            it = short_term_loan_book.erase(it); // delete the pointer from the vector

        }  else { // Firm has not finished repaying
            new_interest_repayments += (*it)->Calculate_Interest_Repayment();
            new_principal_repayments += (*it)->Calculate_Principal_Repayment();
            it++;
        }
    }

    // Tally up total figures
    total_interest_repayments += new_interest_repayments;
    total_principal_repayments += new_principal_repayments;
}



// ------- Printing and Logging Methods

/* String stream operator overload*/
std::ostream& operator<<(std::ostream& os, const Bank_Agent& obj) {
    os << "r_rate " << obj.r_rate << std::endl;
    //os << "r_reaction " << obj.r_reaction << std::endl;
    //os << "risk_premium " << obj.risk_premium << std::endl;
    //os << "cons_inflation_target " << obj.cons_inflation_target << std::endl;
    os << "cons_inflation_current " << obj.cons_inflation_current << std::endl;
    //os << "cons_inflation_previous " << obj.cons_inflation_previous << std::endl;
    //os << "cons_inflation_past_month " << obj.cons_inflation_past_month << std::endl;
    //os << "cap_inflation_current " << obj.cap_inflation_current << std::endl;
    //os << "cap_inflation_previous " << obj.cap_inflation_previous << std::endl;
    //os << "cap_inflation_past_month " << obj.cap_inflation_past_month << std::endl;
    os << "new_principal_repayments " << obj.new_principal_repayments << std::endl;
    os << "new_interest_repayments " << obj.new_interest_repayments << std::endl;
    os << "total_principal_repayments " << obj.total_principal_repayments << std::endl;
    os << "total_interest_repayments " << obj.total_interest_repayments << std::endl;
    os << "total_loan_issuance_to_date " << obj.total_loan_issuance_to_date << std::endl;
    os << "short_term_loan_issuance_to_date " << obj.short_term_loan_issuance_to_date << std::endl;
    os << "long_term_loan_issuance_to_date " << obj.long_term_loan_issuance_to_date << std::endl;
    os << "total_new_loan_issuance " << obj.total_new_loan_issuance << std::endl;
    os << "new_short_term_loan_issuance " << obj.new_short_term_loan_issuance << std::endl;
    os << "new_long_term_loan_issuance " << obj.new_long_term_loan_issuance << std::endl;
    os << "total_outstanding_loans " << obj.total_outstanding_loans << std::endl;
    os << "outstanding_short_term_loans " << obj.outstanding_short_term_loans << std::endl;
    os << "outstanding_long_term_loans " << obj.outstanding_long_term_loans << std::endl;
    //os << "short_term_loan_length " << obj.short_term_loan_length << std::endl;
    //os << "long_term_loan_length " << obj.long_term_loan_length << std::endl;
    //os << "leverage_ratio_lower_threshold " << obj.leverage_ratio_lower_threshold << std::endl;
    //os << "leverage_ratio_upper_threshold " << obj.leverage_ratio_upper_threshold << std::endl;
    os << "date " << obj.current_date << std::endl;
    return os;
}

/* Log data function */
vector<pair<string, float> >* Bank_Agent::Log_Data() {
        current_date = global_date;
        auto result = new vector<std::pair<string, float> >();

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
