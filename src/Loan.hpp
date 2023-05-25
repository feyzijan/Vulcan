#ifndef LOAN_HPP
#define LOAN_HPP

class Firm_Agent; 

//#include "Firm_Agent.hpp"
#include "Initialization_Parameters.hpp"
#include <iostream>
using namespace std;

class Loan {

    public:
    // Constructors and Destructors
    Loan(Firm_Agent* pborrowing_firm, float interest_rate, int principal_amount,
    int duration,bool short_term_loan);
    Loan(Loan&);
    ~Loan();


    // Calculating Payments 
    long long Calculate_Interest_Repayment() const {return principal_amount * interest_rate/12.0;}
    long long Calculate_Principal_Repayment() const;
    
    // Deducting Payments
    void Deduct_Principal_Repayment(int principal_repayment) {principal_amount -= principal_repayment;}

    // Cleaning Loan ( Bankrupt Firm)
    void Clean_Loan();

    // Getters
    float Get_Interest_Rate() const { return interest_rate;}
    int Get_Principal_Amount() const {return principal_amount;}
    int Get_Start_Date() const {return start_date;}
    int Get_End_Date() const {return end_date;}
    Firm_Agent* Get_Borrowing_Firm() const {return pBorrowing_Firm; }

    // Setters
    void Set_Borrowing_Firm_To_Null() {pBorrowing_Firm = nullptr;}


    protected:
    Firm_Agent* pBorrowing_Firm;
    float interest_rate;
    long long principal_amount;
    int start_date;
    int end_date;
    bool loan_type; // 1 = short term, 0 = long term
    bool expired;
};

#endif