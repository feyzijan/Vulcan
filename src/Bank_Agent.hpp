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
    // Constructor
    Bank_Agent(Public_Info_Board* pPublic_Info_Board); 

    // Inflation and Interest Rate Policies
    void Update_Inflation();
    void Update_Interest_Rate();

    // Loan issuance
    Loan* Issue_Short_Term_Loan(Firm_Agent* pFirm);
    Loan* Issue_Long_Term_Loan(Firm_Agent* pFirm);

    float Calculate_Emission_Penalty(Firm_Agent* pFirm);

    // Getters
    float Get_Interest_Rate() {return r_rate;};

    // Printing and debugging
    friend std::ostream& operator<<(std::ostream& os, const Bank_Agent& obj);
    vector<std::pair<string, float>>*  Log_Data();

    protected:
    Public_Info_Board* pPublic_Board;
    queue<float> cons_inflation_history; 
    queue<float> cap_inflation_history; 
    queue<float> interest_rate_history; 

    vector<Loan*> short_term_loan_book; 
    vector<Loan*> long_term_loan_book; 

    // Interest rates 
    float r_rate;
    float r_reaction; // How much the interest rate changes in response to inflation
    float risk_premium; // How much to increase interest rate per leverage ratio above threshold
 
    // Inflation
    float cons_inflation_current; // Inflation (trailing 12m)
    float cons_inflation_previous; // Inflation previous (i.e. last month) (trailing 12m)
    float cons_inflation_target; // Inflation (next 12m target)
    float cons_inflation_past_month; // Inflation Month on Month

    // Manufacturer inflation
    float cap_inflation_current; // Inflation (trailing 12m)
    float cap_inflation_previous; // Inflation previous (trailing 12m)
    //float cap_inflation_target; // Inflation (next 12m target) - No capital inflation target yet
    float cap_inflation_past_month; // Inflation MoM

    // Repayments
    long long new_principal_repayments;
    long long new_interest_repayments;
    long long total_principal_repayments;
    long long total_interest_repayments;

    // Loan issuance totals
    long long total_loan_issuance_to_date; 
    long long short_term_loan_issuance_to_date;
    long long long_term_loan_issuance_to_date;
    long long total_new_loan_issuance;
    long long new_short_term_loan_issuance;
    long long new_long_term_loan_issuance;
    long long total_outstanding_loans;
    long long outstanding_short_term_loans;
    long long outstanding_long_term_loans;

    // Loan parameters
    int short_term_loan_length;
    int long_term_loan_length;


    // Risky loan evaluation
    float leverage_ratio_lower_threshold;
    float leverage_ratio_upper_threshold;

    int current_date;

};
#endif
