#include "Loan.hpp"

/*
*
*
*/

int Loan::Calculate_Interest_Repayment() const
{
    return principal_amount * interest_rate; // Will update this


}

/*
*
*
*/
int Loan::Calculate_Principal_Repayment() const
{
    return principal_amount * (end_date - start_date);
}

/*
*
*
*/

void Loan::Deduct_Principal_Repayment(int principal_repayment)
{
    principal_amount -= principal_amount;
}



