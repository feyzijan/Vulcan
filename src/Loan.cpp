#include "Loan.hpp"

//---- Constructors

Loan::Loan(Firm_Agent* _pborrowing_firm, float _interest_rate, long long _principal_amount,int _duration, bool _is_short_term_loan)
{
    pBorrowing_Firm = _pborrowing_firm;
    interest_rate = _interest_rate;
    if (interest_rate < 0){
        cout << "ERROR: Negative interest rate calculated in Loan creation: interest rate is " << interest_rate << endl;
        interest_rate = 0.02;
    }
    principal_amount = _principal_amount;
    original_issuance_amount = _principal_amount;
    start_date = global_date;
    end_date = start_date + _duration;
    is_short_term_loan = _is_short_term_loan;
    expired = false;
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
    is_short_term_loan = 0;
    expired = true;
}


// --- Calculating Payments


long long Loan::Calculate_Interest_Repayment() const {

    long long payment;

    if (principal_amount > 0){ // long term loan with remaining balance
        payment = static_cast<long long>(principal_amount/12.0);
        payment = static_cast<long long>(payment * this->interest_rate);
        if( payment < 0){
            cout << "ERROR: Negative interest payment calculated: payment is " << payment << " interest rate is: " << interest_rate << endl;
            payment = 0;
        }
    } else {
        payment = 0;
    }

    return payment;
}


/* Function called by firmsto calculate principal to be paid on a loan
*/
long long Loan::Calculate_Principal_Repayment() const
{
    if ((is_short_term_loan == 1) && (end_date == global_date)) // short term loan, not amortized
    {
        return principal_amount;
    } else if (is_short_term_loan==0){
        long long payment = static_cast<long long>(principal_amount / (end_date - start_date) * 1.001); // round up by .1% to counteract int rounding
        return payment; 
    } else { // Short term loan, not end date yet
    return 0;
    } 
}
