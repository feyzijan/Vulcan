#ifndef LOAN_HPP
#define LOAN_HPP

class Firm_Agent; 

#include "Initialization_Parameters.hpp"
#include <iostream>
using namespace std;

class Loan {

    public:
    // Constructors and Destructors
    Loan(Firm_Agent* _pborrowing_firm, float _interest_rate, long long _principal_amount,
    int _duration, bool _is_short_term_loan);
    Loan(Loan&);
    ~Loan();


    // Calculating Payments 
    long long Calculate_Interest_Repayment() const;
    long long Calculate_Principal_Repayment() const;
    
    // Deducting Payments
    void Deduct_Principal_Repayment(long long principal_repayment) {principal_amount -= principal_repayment;}

    // Cleaning Loan ( Bankrupt Firm or fully repaid loan)
    void Clean_Loan(bool is_bankrupt);

    // Getters
    float Get_Interest_Rate() const { return interest_rate;}
    long long Get_Principal_Amount() const {return principal_amount;}
    int Get_Start_Date() const {return start_date;}
    int Get_End_Date() const {return end_date;}
    Firm_Agent* Get_Borrowing_Firm() const {return pBorrowing_Firm; }
    bool Get_Expiration_Status() const {return expired;}
    bool Get_Bankruptcy_Status() const {return bankrupt_firm;}

    // Setters
    void Set_Borrowing_Firm_To_Null() {pBorrowing_Firm = nullptr;}


    protected:
    Firm_Agent* pBorrowing_Firm;
    float interest_rate;
    long long principal_amount;
    long long original_issuance_amount;
    int start_date;
    int end_date;
    bool is_short_term_loan; // 1 = short term, 0 = long term
    bool expired;
    bool bankrupt_firm;
};

#endif