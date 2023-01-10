#ifndef FIRM_AGENT_HPP
#define FIRM_AGENT_HPP


#include <iostream>


#include "Loan.hpp"
#include "General_Good.hpp"
#include "Job.hpp"
#include "Public_Info_Board.hpp"

// Todo: Move below definitions to the initialization file
#define loan_book_size 100
#define employee_list_size 100
/* TODO:
- Replace the numerical values in Loan and employee list with global constants

*/


class Firm_Agent{

    public:
    
    Firm_Agent() {}; 

    


    Firm_Agent(Firm_Agent&); //Copy Constructor
    ~Firm_Agent(){}; // Destructor


    void Print(); // Print class variables


    // -------- Initializers
    void InitializeEmployees(); // Assign employees in t=0




    // Sending Goods to Market

    // ------- Update methods -------

    // Check sales and update revenue and inventory
    void Check_Sales();

    // Pay liabilities 
    void Pay_Liabilities();

    // Seek Loans if needed to pay liabilities
    int Seek_Loans(int shortfall);


    // Inventory check
    bool Inventory_Above_Desire();

    // Plan the production for the next time step
    void Plan_Production();

    // Update price of goods to be sold in the next timestep
    void Update_Price();

    // Post job offers to employ workers 
    void Post_Jobs();

    // Adjust Wage offer after job search
    void Adjust_Wage_Offers();



    // Getters

    // Setters
    void Set_Public_Info_Board(Public_Info_Board* ptr) {pPublic_Info_Board = ptr;}


    Public_Info_Board* pPublic_Info_Board;

    protected:
    General_Good* goods_on_market;

    // Production and sales figures
    int production_current; // Actual production at t
    int production_planned; // Production plan for t
    int production_past; // Production at t-1
    int quantity_sold; // Sales at t-1

    // Inflows
    int total_income;
    int revenue_sales;
    int new_loan_issuance;
    int subsidies;
    float good_price_current; // good price set for t
    float good_price_past; // good price at t-1

    // Expenditures
    int total_liabilities; //Comprises of evt below
    int labor_wage_bill;
    int capital_costs;
    int tax_payments;
    int debt_principal_payments;
    int debt_interest_payments;
    int dividend_payments;

    // Assets and fianncials 
    int total_assets; // maybe this should be the same as cash in hand?
    int leverage_ratio;
    int cash_on_hand;

    // Dividend characteristics
    float dividend_ratio;
    float dividend_ratio_optimist; // characteristic
    float dividend_ratio_pessimist; // characteristic

    // List of loans taken out
    Loan* loan_book[loan_book_size]; // 

    // Employees
    Job* employee_jobs[employee_list_size]; // Define this globally 

    int employee_count; 
    int wage_offer;
    int employee_count_desired;
    bool need_worker;
    int w_target; //Desired labor capacity utilization
    int w_current; //Current labor capacity utilization


    
    // Inventories
    int inventory;
    int working_capital_inventory;
    float desired_inventory_factor; // a characteristic
    float inventory_factor; 


    // Sentiment
    bool sentiment; // pessimistic, optimistic

    // Bankruptcy
    bool bankrupt;;





};

#endif