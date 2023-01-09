#ifndef LOAN_HPP
#define LOAN_HPP

class Firm_Agent; 

//#include "Firm_Agent.hpp"

class Loan {

    public:
    Loan(Firm_Agent* pborrowing_firm, float interest_rate, int principal_amount, int start_date, int end_date);
    Loan(Loan&);
    ~Loan();


    // Function to calculate how much payment is needed now
    int Calculate_Interest_Repayment() const;
    int Calculate_Principal_Repayment() const;
    
    // Function to deduct payments from loan
    void Deduct_Principal_Repayment(int principal_repayment);

    //Getters
    float Get_Interest_Rate() const { return interest_rate;}
    int Get_Principal_Amount() const {return principal_amount;}
    int Get_Start_Date() const {return start_date;}
    int Get_End_Date() const {return end_date;}
    Firm_Agent* Get_Borrowing_Firm() const {return pBorrowing_Firm; }



    protected:
    float interest_rate;
    int principal_amount;
    int start_date;
    int end_date;
    Firm_Agent* pBorrowing_Firm;





};

#endif