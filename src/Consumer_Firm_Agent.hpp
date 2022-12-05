#ifndef CONSUMER_FIRM_AGENT_HPP
#define CONSUMER_FIRM_AGENT_HPP



#include "Firm_Agent.hpp"
#include "Loan.hpp"

class Consumer_Firm_Agent: public Firm_Agent{

    public:
    
    Consumer_Firm_Agent(); // Constructor
    Consumer_Firm_Agent(Consumer_Firm_Agent&); //Copy Constructor
    ~Consumer_Firm_Agent(); // Destructor

    // Put up Consumer Goods for Sale




    // Check sales and update revenue and inventory
    void Check_Sales();

    // Pay liabilities and if necessary seek loans
    void Pay_Liabilities();

    int Seek_Loans();


    // Plan the production for the next time step
    void Plan_Production();

    // Update price of goods
    void Update_Price();

    // Post job offers to employ workers
    void Post_JobS();

    // Inventory check
    bool Inventory_Above_Desire();

    // Adjust Wage offer
    void Adjust_Wage_Offers();




    protected:

    Consumer_Good* goods_on_market;

    // Production and sales figures
    int production_current;
    int production_planned;
    int production_past;
    int quantity_sold;


    // Expenditures
    int total_liabilities;
    int labor_wage_bill;
    int capital_costs;
    int tax_payments;
    int debt_principal_payments;
    int debt_interest_payments;
    int dividend_payments;


    // List of loans taken out
    Loan* loan_book[100];

    // Employee list
    //Household_Agent* employee_list[1000];



    // Savings
    int cash_savings;




    //Labor
    int wage_offer;
    int worker_count_desired;
    int worker_count_actual;
    bool need_worker;

    int w_target; //Desired labor capacity utilization
    int w_current; //Current labor capacity utilization


    //----Inflows
    int revenue_current;
    int new_loan_issuance;
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

    // price level
    float good_price_current;
    float good_price_past;

    // Dividends
    float dividend_ratio;



    // Sentiment
    bool sentiment; // pessimistic, optimistic


    // Bankruptcy
    bool bankrupt = True;

    // Constants, characteristics
    int desired_inventory_factor; 




};

#endif
