#ifndef BANK_AGENT_HPP
#define BANK_AGENT_HPP

#include "Public_Info_Board.hpp"
#include "Initialization_Parameters.hpp"
#include "Loan.hpp"

#include <queue>
#include <iostream>
#include <vector>

using namespace std;
class Bank_Agent{

    public:

    Bank_Agent(); 
    Bank_Agent(Bank_Agent&); 
    ~Bank_Agent();




    // Inflation and Interest Rate Policies
    void Update_Interest_Rate();
    void Update_Inflation_Rate();
    


    // Printing and debugging
    void Print_Inflation_History();


    // Loan issuance
    Loan* Issue_Short_Term_Loan();
    Loan* Issue_Long_Term_Loan();




    protected:
    Public_Info_Board* pPublic_Board;
    
    queue<float> inflation_history; // Array of past inflation

    vector<Loan*> short_term_loan_book; 
    vector<Loan*> long_term_loan_book; 


    // Interest rate 
    int r_rate;
    float r_reaction; // Reaction to inflation rate overshoots

    // Inflation
    int inflation_current; // Inflation (trailing 12m)
    int inflation_previous; // Inflation previous (trailing 12m)
    int inflation_target; // Inflation (next 12m target)
    int inflation_past_month; // Inflation MoM




    // Repayments
    int principal_repayments;
    int interest_repayments;


    // Loan issuance totals
    int total_loan_issuance_to_date; 
    int new_loan_issuance;
    int outstanding_loans;

    // Loan parameters
    int risk_premium; //risk premium on doubtful debt
    int short_term_loan_length;
    int long_term_loan_length;


    // Solvency
    int capital_ratio;




};
#endif
