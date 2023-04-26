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
    for(int i=1;i<=12;i++){
        cons_inflation_previous *= bank_inflation_target_monthly; // preset Global param
        cons_inflation_history.push(bank_inflation_target_monthly);
    }

    cons_inflation_current = cons_inflation_previous;

    // Manufacturer inflation - start at 0 inflation
    cap_inflation_previous = 1.0;
    cap_inflation_past_month = 0;
    for(int i=1;i<=12;i++){
        cap_inflation_history.push(cap_inflation_previous);
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

    // Solvency
    capital_ratio = 1.0; // Unsure how to Initialize this
    target_capital_ratio = bank_target_capital_ratio;

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

    float inflation_overshoot = cons_inflation_current - cons_inflation_target;

    // Set interest rate proportional to inflation overshoot
    r_rate = max( float(r_reaction* inflation_overshoot), float(0.0)); 

    // Update historical records
    interest_rate_history.push(r_rate);

    /* Alternative interest rate rule with output target:
    r_rate = max(r_target + a*(cons_inflation_current - cons_inflation_target) + b*(output_current - output_target),0)
    */
}


// Loan issuance

/* Issue short term loans at the risk free rate, without any checks
Function receives firm pointer, accesses the funding gap data, and issues a loan
Updates own records to indicate the loan has been issued
*/
Loan* Bank_Agent::Issue_Short_Term_Loan(Firm_Agent* pFirm){

    // Gather data to issue loan, give a little extra then is required to smooth things over
    float extra_funding = 1.01;
    int short_term_funding_gap = pFirm->Get_Short_Term_Funding_Gap();
    
    if (short_term_funding_gap <= 0){
        cout << "Error in Bank_Agent::Issue_Short_Term_Loan() - Firm has no short term funding gap" << endl;
    }

    int loan_amount = short_term_funding_gap * extra_funding;

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
    float extra_funding = 1.01;
    int long_term_funding_gap = pFirm->Get_Long_Term_Funding_Gap(); 

    if (long_term_funding_gap <= 0){
        cout << "Error in Bank_Agent::Issue_Long_Term_Loan() - long_term_funding_gap <= 0" << endl;
    }

    float leverage_ratio = pFirm->Get_Leverage_Ratio();
    if (leverage_ratio < 0){
        cout << "Error in Bank_Agent::Issue_Long_Term_Loan() - leverage_ratio < 0" << endl;
    }

    if(leverage_ratio < leverage_ratio_upper_threshold){
        // Create Loan with new risky rate
        float excess_leverage = leverage_ratio - leverage_ratio_lower_threshold;
        float loan_rate = r_rate + risk_premium*excess_leverage;
        int loan_amount = long_term_funding_gap * extra_funding;
        
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


// ------- Printing and Logging Methods

/* Function to print bank parameters
*/


/* Function to print trailing 12m inflation
*/
void Bank_Agent::Print_Inflation_History(){
    queue<float> temp;
    temp = cons_inflation_history;
    cout << "Inflation History T12M: " << endl;
    while(!temp.empty()){
        cout << temp.front() << " , ";
        temp.pop();
    }
}

/* Function to print last 12 interest rates
*/
void Bank_Agent::Print_Interest_Rate_History(){
    queue<float> temp;
    temp = interest_rate_history;
    cout << "Interest Rate History T12M: " << endl;
    while(!temp.empty()){
        cout << temp.front() << " , ";
        temp.pop();
    }
}


/* Print all bank parameters for debugging purposes
*/
void Bank_Agent::Print(){
    cout << "Bank at address: " << this << endl;

    // Interest rate
    cout << "Interest Rate: " << r_rate << " Interest rate reaction: " << r_reaction << endl;
    Print_Interest_Rate_History();
    cout << endl;
    
    // Inflation
    cout << "Inflation rate current: " << cons_inflation_current << " previous: " << cons_inflation_previous  << " past_month: "<< 
    cons_inflation_past_month << " target: " << cons_inflation_target << endl;
    Print_Inflation_History();
    cout << endl;

    // Loan issuance totals
    cout << "Total loan issuance to date: " << total_loan_issuance_to_date << " new loan issuance: " << total_new_loan_issuance << " outstanding loans: " << total_outstanding_loans << endl;
    // Repayments
    cout << "Total principal repayments: " << total_principal_repayments << " total interest repayments: " << total_interest_repayments << endl;
    // Loan parameters
    cout << "Short term loan length: " << short_term_loan_length << " long term loan length: " << long_term_loan_length << endl;
    // Solvency
    cout << "Capital ratio: " << capital_ratio << " target capital ratio: " << target_capital_ratio << endl;
    // Loan books
    cout << "Short term loan book: " << endl;
    for(int i = 0; i < short_term_loan_book.size(); i++){
        cout << "Loan " << i << " : " << endl;
        short_term_loan_book[i]->Print();
    }
    cout << "Long term loan book: " << endl;
    for(int i = 0; i < long_term_loan_book.size(); i++){
        cout << "Loan " << i << " : " << endl;
        long_term_loan_book[i]->Print();
    }
}


/* String stream operator overload*/
std::ostream& operator<<(std::ostream& os, const Bank_Agent& obj) {
    os << "r_rate: " << obj.r_rate << std::endl;
    os << "r_reaction: " << obj.r_reaction << std::endl;
    os << "risk_premium: " << obj.risk_premium << std::endl;
    os << "cons_inflation_current: " << obj.cons_inflation_current << std::endl;
    os << "cons_inflation_previous: " << obj.cons_inflation_previous << std::endl;
    os << "cons_inflation_target: " << obj.cons_inflation_target << std::endl;
    os << "cons_inflation_past_month: " << obj.cons_inflation_past_month << std::endl;
    os << "cap_inflation_current: " << obj.cap_inflation_current << std::endl;
    os << "cap_inflation_previous: " << obj.cap_inflation_previous << std::endl;
    os << "cap_inflation_past_month: " << obj.cap_inflation_past_month << std::endl;
    os << "new_principal_repayments: " << obj.new_principal_repayments << std::endl;
    os << "new_interest_repayments: " << obj.new_interest_repayments << std::endl;
    os << "total_principal_repayments: " << obj.total_principal_repayments << std::endl;
    os << "total_interest_repayments: " << obj.total_interest_repayments << std::endl;
    os << "total_loan_issuance_to_date: " << obj.total_loan_issuance_to_date << std::endl;
    os << "short_term_loan_issuance_to_date: " << obj.short_term_loan_issuance_to_date << std::endl;
    os << "long_term_loan_issuance_to_date: " << obj.long_term_loan_issuance_to_date << std::endl;
    os << "total_new_loan_issuance: " << obj.total_new_loan_issuance << std::endl;
    os << "new_short_term_loan_issuance: " << obj.new_short_term_loan_issuance << std::endl;
    os << "new_long_term_loan_issuance: " << obj.new_long_term_loan_issuance << std::endl;
    os << "total_outstanding_loans: " << obj.total_outstanding_loans << std::endl;
    os << "outstanding_short_term_loans: " << obj.outstanding_short_term_loans << std::endl;
    os << "outstanding_long_term_loans: " << obj.outstanding_long_term_loans << std::endl;
    os << "short_term_loan_length: " << obj.short_term_loan_length << std::endl;
    os << "long_term_loan_length: " << obj.long_term_loan_length << std::endl;
    os << "capital_ratio: " << obj.capital_ratio << std::endl;
    os << "target_capital_ratio: " << obj.target_capital_ratio << std::endl;
    os << "leverage_ratio_lower_threshold: " << obj.leverage_ratio_lower_threshold << std::endl;
    os << "leverage_ratio_upper_threshold: " << obj.leverage_ratio_upper_threshold << std::endl;
    os << "date: " << obj.current_date << std::endl;
    return os;
}

/* Log data function */
vector<pair<string, float>>* Bank_Agent::Log_Data() {
        current_date = global_date;
        auto result = new std::vector<std::pair<std::string, float>>();

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
