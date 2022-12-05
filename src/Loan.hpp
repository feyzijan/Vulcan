#ifndef LOAN_HPP
#define LAON_HPP


class Loan {

    public:
    Loan(float interest_rate, int principal_amount, int start_date, int end_date);
    Loan(Loan&);
    ~Loan();


    // Function to calculate how much payment is needed now
    int Calculate_Interest_Repayment() const;
    int Calculate_Principal_Repayment() const;

    //Getters
    float Get_Interest_Rate() const { return interest_rate;}
    int Get_Principal_Amount() const {return principal_amount;}
    int Get_Start_Date() const {return start_date;}
    int Get_End_Date() const {return end_date;}

    // Setters
    void Deduct_Payments(int payment);



    protected:
    float interest_rate;
    int principal_amount;
    int start_date;
    int end_date;





};

#endif