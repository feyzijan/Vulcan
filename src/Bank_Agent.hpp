#ifndef BANK_AGENT_HPP
#define BANK_AGENT_HPP


class Public_Info_Board;
#include "Public_Info_Board.hpp"
#include "Initialization_Parameters.hpp"
#include "Loan.hpp"
#include "Firm_Agent.hpp"


#include <queue>
#include <iostream>
#include <vector>

using namespace std;
class Bank_Agent{

    public:
    // Constructors and Destructors
    Bank_Agent(Public_Info_Board* pPublic_Info_Board); 
    Bank_Agent(Bank_Agent&); 
    ~Bank_Agent();

    // Inflation and Interest Rate Policies
    void Update_Inflation_Rate();
    void Update_Interest_Rate();

    void Update_Manufacturer_Inflation_Rate();

    // Loan issuance
    Loan* Issue_Short_Term_Loan(Firm_Agent* pFirm);
    Loan* Issue_Long_Term_Loan(Firm_Agent* pFirm);

    // Getters
    float Get_Inflation_Rate() {return inflation_current;};
    float Get_Manufacturer_Inflation_Rate() {return cap_inflation_current;};
    float Get_Interest_Rate() {return r_rate;};

    // Printing and debugging
    void Print();
    void Print_Inflation_History();
    void Print_Interest_Rate_History(); // To Implement
    

    protected:
    Public_Info_Board* pPublic_Board;
    
    queue<float> inflation_history; // Array of past inflation
    queue<float> cap_inflation_history; // Array of past manufacturer inflation
    queue<float> interest_rate_history; // Array of past interest rates

    vector<Loan*> short_term_loan_book; 
    vector<Loan*> long_term_loan_book; 

    // Interest rate 
    float r_rate;
    float r_reaction;
    float risk_premium; //risk premium on doubtful debt - per leverage ratio above threshold
 
    // Inflation
    float inflation_current; // Inflation (trailing 12m)
    float inflation_previous; // Inflation previous (trailing 12m)
    float inflation_target; // Inflation (next 12m target)
    float inflation_past_month; // Inflation MoM

    // Manufacturer inflation
    float cap_inflation_current; // Inflation (trailing 12m)
    float cap_inflation_previous; // Inflation previous (trailing 12m)
    float cap_inflation_past_month; // Inflation MoM


    // Repayments
    int new_principal_repayments;
    int new_interest_repayments;
    int total_principal_repayments;
    int total_interest_repayments;

    // Loan issuance totals
    int total_loan_issuance_to_date; 
    int new_loan_issuance;
    int outstanding_loans;

    // Loan parameters
    int short_term_loan_length;
    int long_term_loan_length;

    // Solvency
    float capital_ratio;
    float target_capital_ratio;

    // Risky loan evaluation
    float leverage_ratio_lower_threshold;
    float leverage_ratio_upper_threshold;

};
#endif
