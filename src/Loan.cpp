#include "Loan.hpp"

/* Function to calculate interest to be paid on a loan
* This function is called by firms
*/

int Loan::Calculate_Interest_Repayment() const
{
    return principal_amount * interest_rate; // Will update this


}

/* Function to calculate principal to be paid on a loan
* This function is called by firms
*/
int Loan::Calculate_Principal_Repayment() const
{
    if ((loan_type == 1) && (end_date == global_current_date)) // short term loan, not amortized
    {
        return principal_amount;
    } else if (loan_type==0){
        return int(principal_amount * (end_date - start_date));
    }else{
        return 0;
    }
    
}

/*
*
*
*/

void Loan::Deduct_Principal_Repayment(int principal_repayment)
{
    principal_amount -= principal_repayment;
}





