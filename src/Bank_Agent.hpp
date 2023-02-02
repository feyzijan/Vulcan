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

    // Loan issuance
    Loan* Issue_Short_Term_Loan(Firm_Agent* pFirm);
    Loan* Issue_Long_Term_Loan(Firm_Agent* pFirm);


    // Printing and debugging
    void Print();
    void Print_Inflation_History();
    void Print_Interest_Rate_History(); // To Implement
    


    



    protected:
    Public_Info_Board* pPublic_Board;
    
    queue<float> inflation_history; // Array of past inflation
    vector<float> interest_rate_history; // Array of past interest rates

    vector<Loan*> short_term_loan_book; 
    vector<Loan*> long_term_loan_book; 


    // Interest rate 
    float r_rate;
    float r_reaction;
    float risk_premium; //risk premium on doubtful debt
 
    // Inflation
    float inflation_current; // Inflation (trailing 12m)
    float inflation_previous; // Inflation previous (trailing 12m)
    float inflation_target; // Inflation (next 12m target)
    float inflation_past_month; // Inflation MoM


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


};
#endif
