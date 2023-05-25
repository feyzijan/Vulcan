#include "Loan.hpp"

//---- Constructors

Loan::Loan(Firm_Agent* pborrowing_firm, float interest_rate, int principal_amount, int duration, bool short_term_loan)
{
    pBorrowing_Firm = pborrowing_firm;
    this->interest_rate = interest_rate;
    this->principal_amount = principal_amount;
    this->start_date = global_date;
    this->end_date = start_date + duration;
    this->loan_type = short_term_loan;
    this->expired = false;
}

Loan::~Loan(){}
Loan::Loan(Loan&){}
//-------------------------------------------

/* Clean loan if firm is bankrupt
*/
void Loan::Clean_Loan(){
    pBorrowing_Firm = nullptr;
    interest_rate = 0;
    principal_amount = 0;
    start_date = 0;
    end_date = 0;
    loan_type = 0;
    expired = true;
}



// --- Calculating Payments


/* Function called by firmsto calculate principal to be paid on a loan
*/
long long Loan::Calculate_Principal_Repayment() const
{
    if ((loan_type == 1) && (end_date == global_date)) // short term loan, not amortized
    {
        return principal_amount;
    } else if (loan_type==0){
        return static_cast<long long>(principal_amount * (end_date - start_date) * 1.001); // round up by .1% to counteract int rounding 
    } else {
    return 0;} 
}
