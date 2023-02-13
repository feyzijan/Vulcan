#include "Bank_Agent.hpp"


//----------Constructors and Destructors ------------------

/* Initialize the bank agent with a public board pointer
Initialize the inflation and interest rate wih preset global parameters
Initialize everything else to zero
*/
Bank_Agent::Bank_Agent(Public_Info_Board* pPublic_Info_Board){

    this->pPublic_Board = pPublic_Info_Board;

    // Interest rate 
    r_rate = bank_initial_interest_rate; // preset Global param
    risk_premium = bank_risk_premium; // preset Global param
    r_reaction = bank_inflation_reaction; // preset Global param

    // Inflation
    inflation_target = bank_inflation_target;
    inflation_past_month = bank_inflation_target_monthly;
    inflation_previous = 1.0;

    for(int i=1;i<=12;i++){
        inflation_previous *= bank_inflation_target_monthly; // preset Global param
        inflation_history.push(bank_inflation_target_monthly);
    }

    inflation_current = inflation_previous;
    
    // Repayments
    new_principal_repayments = 0;
    new_interest_repayments = 0;
    total_principal_repayments = 0;
    total_interest_repayments = 0;

    // Loan issuance totals
    total_loan_issuance_to_date = 0; 
    new_loan_issuance = 0;
    outstanding_loans = 0;

    // Loan parameters
    short_term_loan_length = bank_short_term_loan_length;
    long_term_loan_length = bank_long_term_loan_length;

    // Solvency
    capital_ratio = 1.0; // Unsure how to Initialize this
    target_capital_ratio = bank_target_capital_ratio;

}

/* Destructor*/
Bank_Agent::~Bank_Agent(){}
/* Copy Constructor*/
Bank_Agent::Bank_Agent(Bank_Agent&){}

// --------- Inflation and Interest Rate Policies


/* Function to update price level and inflation rate data
Gets the latest inflation figure from the public board
*/
void Bank_Agent::Update_Inflation_Rate(){
    
    inflation_previous = inflation_current;
    inflation_past_month = pPublic_Board->Calculate_Inflation();
    // Update inflation to match trailing 12m
    inflation_current = inflation_previous / inflation_history.front() * inflation_past_month;
    // Update inflation_history
    inflation_history.pop();
    inflation_history.push(inflation_past_month);
}


/* Function to update interest rate based on new inflation data
 To be called after calling Update_Inflation_Rate()
 Use a simple taylor rule from the Jamel Paper
*/
void Bank_Agent::Update_Interest_Rate(){

    float inflation_overshoot = inflation_current - inflation_target;

    // Set interest rate proportional to inflation overshoot
    r_rate = max( float(r_reaction* inflation_overshoot), float(0.0)); 

    // Update historical records
    interest_rate_history.push(r_rate);


    /* Alternative interest rate rule with output target:
    r_rate = max(r_target + a*(inflation_current - inflation_target) + b*(output_current - output_target),0)
    */
}


// Loan issuance

/* Issue short term loans at the risk free rate, without any checks
Function receives firm pointer, accesses the funding gap data, and issues a loan
Updates own records to indicate the loan has been issued
*/
Loan* Bank_Agent::Issue_Short_Term_Loan(Firm_Agent* pFirm){

    // Create new loan
    int short_term_funding_gap = pFirm->Get_Short_Term_Funding_Gap();
    int current_date = pPublic_Board->Get_Current_Date();
    Loan* new_loan = new Loan(pFirm,r_rate,short_term_funding_gap, short_term_loan_length,1);
    // Update own records
    total_loan_issuance_to_date += short_term_funding_gap;
    new_loan_issuance += short_term_funding_gap;
    outstanding_loans += short_term_funding_gap;
    short_term_loan_book.push_back(new_loan);

    return new_loan;
}

/* Issue long term loans at the risk free rate + risk premium
Function receives firm pointer, accesses the funding gap data wnd risk data,
and issues a loan, or not, and returns a null pointer
Updates own records to indicate the loan has been issued
TODO: Write procedures for rejecting loans
*/

Loan* Bank_Agent::Issue_Long_Term_Loan(Firm_Agent* pFirm){

    int long_term_funding_gap = pFirm->Get_Long_Term_Funding_Gap();
    float leverage_ratio = pFirm->Get_Leverage_Ratio();

    float loan_rate = r_rate + risk_premium*leverage_ratio;

    bool issue = true;

    if(issue){
        int current_date = pPublic_Board->Get_Current_Date();
        Loan* new_loan = new Loan(pFirm,loan_rate,long_term_funding_gap, long_term_loan_length,0);
        // Update own records
        total_loan_issuance_to_date += long_term_funding_gap;
        new_loan_issuance += long_term_funding_gap;
        outstanding_loans += long_term_funding_gap;
        long_term_loan_book.push_back(new_loan);

        return new_loan;
    }else{
        return nullptr;
    }

}


// ------- Printing and Logging Methods

/* Function to print bank parameters
*/


/* Function to print trailing 12m inflation
*/
void Bank_Agent::Print_Inflation_History(){
    queue<float> temp;
    temp = inflation_history;
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
    cout << "Inflation rate current: " << inflation_current << " previous: " << inflation_previous  << " past_month: "<< 
    inflation_past_month << " target: " << inflation_target << endl;
    Print_Inflation_History();
    cout << endl;

    // Loan issuance totals
    cout << "Total loan issuance to date: " << total_loan_issuance_to_date << " new loan issuance: " << new_loan_issuance << " outstanding loans: " << outstanding_loans << endl;
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