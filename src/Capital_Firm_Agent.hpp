#ifndef PUBLIC_INFO_BOARD_HPP
#define PUBLIC_INFO_BOARD_HPP

#endif

#include "Firm_Agent.hpp"

class Capital_Firm_Agent: public Firm_Agent{

    public:
    
    Capital_Firm_Agent(); // Constructor
    Capital_Firm_Agent(Capital_Firm_Agent&); //Copy Constructor
    ~Capital_Firm_Agent(); // Destructor


    private:
    //----Outflows
    int labor_wage_bill;
    int capital_costs;
    int energy_costs; // may exclude
    int tax_payments;
    int debt_payments;
    int interest_payments;
    int dividend_payments;
    //int research_spending;

    //----Inflows
    int capital_good_revenue;
    int capital_goods_sold; //quantity
    int new_loans;
    int subsidies;
    //int total_carbon_emissions;

    //----State variables
    int consumer_goods_inventory;
    //int carbon_intensity_of_production;
    int capital_goods_inventory;
    int total_assets;
    int total_debts_liabilities;
    int total_employee_count;
    int leverage_ratio;
    //int research_spending_ratio;


    bool sentiment; // pessimistic, optimistic
    



};

