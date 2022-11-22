#include <iostream>

class Household_Agent{

    public:
    Household_Agent(int initial_savings); //Constructor

    Household_Agent(Household_Agent&); //Copy constructor
    
    ~Household_Agent(); // Destructor


    //Household variables

    private:
    int total_savings;
    int total_consumption_expenditure;
    int tax_payment;
    int savings_deposit;

    int wage;
    int unemployment_benefit;
    int government_transfers;
    int savings_interest_income;
    int dividend_income;

    bool unemployed;
    bool business_owner;

    int reservation_wage;



};